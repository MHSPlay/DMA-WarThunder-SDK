#pragma once
#include <corecrt_math_defines.h>

namespace aimbot
{
    constexpr double GRAVITY = -9.8;
    constexpr double TIMESTEP = 1.f / 96.f;

    struct BallisticsData 
    {
        float mass = 0.0f;
        float caliber = 0.0f;
        float velocity = 0.0f;
        float dragCoefficient = 0.0f;
        float ballisticCoeff = 0.0f;
        float length = 0.0f;
    
        void GetBallisticCoeff( )
        {
            if ( mass > 0 && caliber > 0 )
                ballisticCoeff = -1.0f * ( dragCoefficient * static_cast< float >( M_PI ) * 0.5f * std::pow( caliber * 0.5f, 2.0f ) * length ) / mass;

        }
    };

    inline BallisticsData ballisticsData;

    inline float GetDragConstant( float LocalPosY )
    {
	    const auto max_alt = 18300.0f;
	    const auto alt_mult = 1.225f;
	    const auto clamped_alt = fmin(LocalPosY, max_alt);
	    const auto unk_1 = 2.2871901e-19f, unk_2 = 5.8355603e-14f,
		    unk_3 = 0.00000000353118f, unk_4 = 0.000095938703f;
 
 
	    return alt_mult *
		    ((max_alt / std::fmax(LocalPosY, max_alt)) *
			    ((((((unk_1 * clamped_alt) - unk_2) * clamped_alt) + unk_3) *
				    clamped_alt) -
				    unk_4) *
			    clamped_alt +
			    1.0f);
    }

    inline auto GetBallisticsInfo( ) -> void 
    {
        uintptr_t cGame = TargetProcess->Read< uintptr_t >( baseAddr + offsets::cgame_offset );
        if ( !cGame ) 
            return;

        uintptr_t ballistics = TargetProcess->Read< uintptr_t >( cGame + offsets::cgame_offsets::ballistics_offset );
        if ( !ballistics ) 
            return;
    
        ballisticsData.mass = TargetProcess->Read< float >( ballistics + offsets::cgame_offsets::ballistic_offsets::mass );
        ballisticsData.length = TargetProcess->Read< float >( ballistics + offsets::cgame_offsets::ballistic_offsets::length );
        ballisticsData.caliber = TargetProcess->Read< float >( ballistics + offsets::cgame_offsets::ballistic_offsets::caliber );
        ballisticsData.velocity = TargetProcess->Read< float >( ballistics + offsets::cgame_offsets::ballistic_offsets::velocity );

        ballisticsData.GetBallisticCoeff( );
    }

    inline bool didHit( const vec3_t& bulletPosition, const vec3_t& targetPosition, float targetRadius )
    {
        return bulletPosition.dist_to( targetPosition ) <= targetRadius;
    }

    inline void ApplyDrag(float ballisticCoeff, vec3_t& bulletVel, vec3_t& bulletPos)
    {
        float delta_speed = (ballisticCoeff * TIMESTEP) * bulletVel.length();
        float velocityMult = 1.0f;

        if (delta_speed < 1.0f || delta_speed > 1.0f)
            velocityMult = (delta_speed / (1.0f - delta_speed)) + 1.0f;

        vec3_t dragged_vel
        {
            bulletVel.x * velocityMult,
            (float)(GRAVITY * TIMESTEP) + (velocityMult * bulletVel.y),
            0
        };

        bulletVel = dragged_vel;

        vec3_t new_pos
        {
            (dragged_vel.x * (float)TIMESTEP) + bulletPos.x,
            (dragged_vel.y * (float)TIMESTEP) + bulletPos.y,
            0
        };

        bulletPos = new_pos;
    }

    inline float FindLaunchAngle(vec3_t bullet_pos, vec3_t target_pos, float velocity, float target_radius, float ballisticCoeff, bool& success)
    {
        float xzDist = vec3_t(bullet_pos.x, 0, bullet_pos.z).dist_to(vec3_t(target_pos.x, 0, target_pos.z));

        bullet_pos = vec3_t(0, bullet_pos.y, 0);
        target_pos = vec3_t(xzDist, target_pos.y, 0);

        float low = -(M_PI / 4), high = M_PI / 2;
        float distance = target_pos.dist_to(bullet_pos);
        float time = (distance / velocity) * 1.1f;

        while (high - low > 0.000005f)
        {
            float mid = (low + high) * 0.5f;
            float launch_angle = mid;

            vec3_t bullet_velocity{
                velocity * std::cos(launch_angle),
                velocity * std::sin(launch_angle),
                0.0f
            };

            vec3_t bullet_pos_temp = bullet_pos;

            for (float elapsed_time = 0; elapsed_time < time; elapsed_time += (float)TIMESTEP)
            {
                ApplyDrag(ballisticCoeff, bullet_velocity, bullet_pos_temp);

                if (didHit(bullet_pos_temp, target_pos, target_radius))
                {
                    success = true;
                    return mid;
                }
            }

            if (bullet_pos_temp.y > target_pos.y)
                high = mid;
            else
                low = mid;
        }

        return (low + high) * 0.5f;
    }

    inline auto Think() -> void
    {
        uintptr_t cGame = TargetProcess->Read< uintptr_t >(baseAddr + offsets::cgame_offset);
        uintptr_t cCamera = TargetProcess->Read< uintptr_t >(cGame + offsets::cgame_offsets::camera_offset);
        ViewMatrix_t matrix = TargetProcess->Read< ViewMatrix_t >(cCamera + offsets::cgame_offsets::camera_offsets::camera_matrix_offset);

        uintptr_t local = TargetProcess->Read< uintptr_t >(baseAddr + offsets::localplayer_offset);
        uintptr_t localUnit = TargetProcess->Read< uintptr_t >(local + offsets::localplayer::localunit_offset) - 1;
        vec3_t localPosition = TargetProcess->Read< vec3_t >(localUnit + 0xAE8);

        for (uintptr_t unit : misc::units)
        {
            vec3_t unitPosition = TargetProcess->Read< vec3_t >(unit + 0xAE8);
            if (unitPosition.empty())
                continue;

            float distance = localPosition.dist_to(unitPosition);
            if (distance >= 1400)
                continue;

            ballisticsData.dragCoefficient = GetDragConstant(localPosition.y);
            GetBallisticsInfo();

            bool success = false;
            float launchAngle = FindLaunchAngle(localPosition, unitPosition, ballisticsData.velocity, 3.0f, ballisticsData.ballisticCoeff, success);
            if (!success)
                continue;

            // Вычисляем направление к цели
            vec3_t targetDirection = unitPosition - localPosition;
            float horizontalDistance = sqrtf(targetDirection.x * targetDirection.x + targetDirection.z * targetDirection.z);
            
            // Нормализуем горизонтальное направление
            vec3_t horizontalDir = vec3_t(targetDirection.x, 0, targetDirection.z);
            if (horizontalDistance > 0.001f) {
                horizontalDir.x /= horizontalDistance;
                horizontalDir.z /= horizontalDistance;
            }
            
            // Создаем вектор направления прицеливания с учетом угла возвышения
            vec3_t aimDirection;
            aimDirection.x = horizontalDir.x * cosf(launchAngle);
            aimDirection.y = sinf(launchAngle);
            aimDirection.z = horizontalDir.z * cosf(launchAngle);
            
            // Создаем точку прицеливания на некотором расстоянии от игрока
            float aimDistance = 50.0f; // Расстояние для визуализации точки прицеливания
            vec3_t aimPosition = localPosition + (aimDirection * aimDistance);

            vec2_t screen;
            if (!g_render->world_to_screen(aimPosition, screen, matrix))
                continue;

            ImU32 rectColor = IM_COL32(0, 255, 0, 200);    // Зеленый прямоугольник
            ImU32 centerColor = IM_COL32(255, 0, 0, 255);   // Красная точка в центре

            // Рисуем прямоугольник для позиции стрельбы
            g_render->rect(
                screen.x - 8,
                screen.y - 8,
                16,
                16,
                rectColor,
                2.0f
            );
            
            // Добавляем маленькую точку в центре для точности
            g_render->rect(
                screen.x - 1,
                screen.y - 1,
                2,
                2,
                centerColor,
                1.0f
            );
        }
    }
	
}