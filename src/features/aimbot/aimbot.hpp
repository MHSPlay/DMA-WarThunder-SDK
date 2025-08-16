#pragma once
#include <corecrt_math_defines.h>

namespace aimbot
{
    constexpr double GRAVITY = -9.8;

    struct BallisticsData
    {
        float mass = 0.0f;
        float caliber = 0.0f;
        float velocity = 0.0f;
    };

    inline BallisticsData ballisticsData;

    inline auto GetBallisticsInfo( ) -> void
    {
        ballisticsData.mass = sdk::cGame->ballistics->getMass( );
        ballisticsData.caliber = sdk::cGame->ballistics->getCaliber( );
        ballisticsData.velocity = sdk::cGame->ballistics->getVelocity( );
    }

    inline float GetDragConstant(float altitude)
    {
        constexpr float max_alt = 18300.0f;
        constexpr float alt_mult = 1.225f;
        constexpr float coefficients[] = {
            2.2871901e-19f, 5.8355603e-14f,
            0.00000000353118f, 0.000095938703f
        };

        const float clamped_alt = std::fmin(altitude, max_alt);
        const float poly = ((((coefficients[0] * clamped_alt - coefficients[1])
            * clamped_alt + coefficients[2])
            * clamped_alt - coefficients[3]) * clamped_alt + 1.0f);

        return alt_mult * (max_alt / std::fmax(altitude, max_alt)) * poly;
    }

    inline double CalculateBallisticCoefficient(float altitude)
    {
        const float dragConstant = GetDragConstant(altitude);
        const float crossSectionArea = static_cast<float>(M_PI) * std::pow(ballisticsData.caliber * 0.5f, 2.0f);
        return ballisticsData.mass / (dragConstant * crossSectionArea);
    }

    inline auto SolveTime(double dist2D, double deltaZ, double velocity, float altitude) -> double
    {
        const double bc = CalculateBallisticCoefficient(altitude);
        const double a = 0.25 * GRAVITY * GRAVITY;
        const double b = -(deltaZ * GRAVITY + velocity * velocity);
        const double c = dist2D * dist2D + deltaZ * deltaZ;

        const double discriminant = b * b - 4 * a * c;
        if (discriminant < 0)
            return -1.0;

        const double sqrt_discr = std::sqrt(discriminant);
        const double inv_2a = 1.0 / (2 * a);

        double x1 = (-b + sqrt_discr) * inv_2a;
        double x2 = (-b - sqrt_discr) * inv_2a;

        double t_solution = -1.0;
        if (x1 >= 0)
            t_solution = std::sqrt(x1);
        if (x2 >= 0)
        {
            const double t2 = std::sqrt(x2);
            if (t_solution > 0)
                t_solution = min(t_solution, t2);
            else
                t_solution = t2;
        }

        if (t_solution > 0) {
            const double drag_correction = dist2D / (2 * bc * velocity);
            t_solution *= (1 + drag_correction);
        }

        return t_solution;
    }

    inline double CalculateVerticalDrop(double flightTime, double initialVelocity, const vec3_t& startPos, const vec3_t& endPos )
    {
        double timestep = 1.0 / 96.0;
        const double gravity = -9.8;

        const float ballisticCoeff = CalculateBallisticCoefficient( startPos.y );
        const vec3_t direction = (endPos - startPos).normalized();

        vec3_t bulletPos = startPos;
        vec3_t bulletVel = direction * initialVelocity;

        double elapsed = 0.0;
        while (elapsed < flightTime)
        {
            if (elapsed + timestep > flightTime)
                timestep = flightTime - elapsed;

            const float delta_speed = ballisticCoeff * timestep * bulletVel.length( );
            float velocityMult = 1.0f;

            if (std::abs(delta_speed - 1.0f) > 0.001f && delta_speed < 0.99f) 
                velocityMult = 1.0f / (1.0f + delta_speed);
            
            bulletVel.x *= velocityMult;
            bulletVel.y = bulletVel.y * velocityMult + gravity * timestep;
            bulletVel.z *= velocityMult;

            bulletPos += bulletVel * timestep;
            elapsed += timestep;
        }

        const double expectedHeight = startPos.y + direction.y * initialVelocity * flightTime;
        return expectedHeight - bulletPos.y;
    }

    inline auto Think() -> void
    {
        const auto camera_matrix = sdk::cGame->camera->getCameraMatrix( );

        std::vector< c_unit > units = misc::unitsList;
		for ( c_unit& unit : units )
		{
            vec3_t unitPosition = unit.getPosition( );
			if ( unitPosition.empty( ) )
				continue;

            vec3_t localPosition = sdk::cLocalPlayer->getLocalUnit( ).getPosition( );

            float horizontalDist = std::sqrt(
                ( unitPosition.x - localPosition.x ) * ( unitPosition.x - localPosition.x ) +
                ( unitPosition.z - localPosition.z ) * ( unitPosition.z - localPosition.z )
            );

            float distanceFactor = horizontalDist / 150.0f;
            float extraOffset = distanceFactor * 0.1425f;

            unitPosition.y += 1.0f + extraOffset;

            int distance = localPosition.dist_to( unitPosition );
            if ( distance >= 1400 )
                continue;

            GetBallisticsInfo( );

            vec3_t targetVelocity = unit.getMovement( ).velocity( );

            double dist2D = localPosition.dist_to( unitPosition );
            double deltaZ = unitPosition.z - localPosition.z;

            double t = SolveTime( dist2D, deltaZ, ballisticsData.velocity, localPosition.y );
            if ( t <= 0 )
                continue;

            vec3_t predictedPos = unitPosition;
            for ( int i = 0; i < 3; ++i )
            {
                predictedPos = unitPosition + targetVelocity * t;
                dist2D = localPosition.dist_to( predictedPos );
                deltaZ = predictedPos.z - localPosition.z;

                double newT = SolveTime( dist2D, deltaZ, ballisticsData.velocity, localPosition.y );
                if ( newT <= 0 )
                    break;

                t = newT;
            }

            double verticalDrop = CalculateVerticalDrop( t, ballisticsData.velocity, localPosition, predictedPos );

            vec3_t aimPoint = predictedPos;
            aimPoint.y += verticalDrop;

            vec2_t screen;
            if ( !g_render->world_to_screen( aimPoint, screen, camera_matrix ) )
                continue;

            g_render->rect( screen.x - 2, screen.y - 2, 4, 4, IM_COL32( 255, 255, 0, 150 ), 4.0f );

            vec2_t unitScreen;
            if ( g_render->world_to_screen( unitPosition, unitScreen, camera_matrix ) )
                g_render->line( unitScreen.x, unitScreen.y, screen.x, screen.y, IM_COL32( 255, 0, 0, 200 ), 2.0f );
            
        }
    }
}