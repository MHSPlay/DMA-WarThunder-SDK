#pragma once

namespace esp 
{

	inline auto Think( ) -> void 
	{
        uintptr_t cGame = TargetProcess->Read< uintptr_t >( baseAddr + offsets::cgame_offset );
        uintptr_t cCamera = TargetProcess->Read< uintptr_t >( cGame + offsets::cgame_offsets::camera_offset );
        ViewMatrix_t matrix = TargetProcess->Read< ViewMatrix_t >( cCamera + offsets::cgame_offsets::camera_offsets::camera_matrix_offset );

		for ( uintptr_t unit : misc::units )
		{
            vec3_t unitPosition = TargetProcess->Read< vec3_t >( unit + 0xAE8 );
			if ( unitPosition.empty( ) )
				continue;

            vec2_t screenPosition;
			if ( !g_render->world_to_screen( unitPosition, screenPosition, matrix ) )
				continue;

            uintptr_t local = TargetProcess->Read< uintptr_t >( baseAddr + offsets::localplayer_offset );
            uintptr_t localUnit = TargetProcess->Read< uintptr_t >( local + offsets::localplayer::localunit_offset ) - 1;
            vec3_t localPosition = TargetProcess->Read< vec3_t >( localUnit + 0xAE8 );

            // return correctly. 225.0F = 225m = 0.22km 
            int distance = localPosition.dist_to( unitPosition );
            if ( distance >= 1400 )
                continue;

			// 3d box
            {
                vec3_t bbmin = TargetProcess->Read< vec3_t >( unit + offsets::unit_offsets::bbmin_offset );
                vec3_t bbmax = TargetProcess->Read< vec3_t >( unit + offsets::unit_offsets::bbmax_offset );

                std::vector<vec3_t> worldCorners = {
                    vec3_t( unitPosition.x + bbmin.x, unitPosition.y + bbmin.y, unitPosition.z + bbmin.z ), // 0
                    vec3_t( unitPosition.x + bbmax.x, unitPosition.y + bbmin.y, unitPosition.z + bbmin.z ), // 1
                    vec3_t( unitPosition.x + bbmin.x, unitPosition.y + bbmax.y, unitPosition.z + bbmin.z ), // 2
                    vec3_t( unitPosition.x + bbmax.x, unitPosition.y + bbmax.y, unitPosition.z + bbmin.z ), // 3
                    vec3_t( unitPosition.x + bbmin.x, unitPosition.y + bbmin.y, unitPosition.z + bbmax.z ), // 4
                    vec3_t( unitPosition.x + bbmax.x, unitPosition.y + bbmin.y, unitPosition.z + bbmax.z ), // 5
                    vec3_t( unitPosition.x + bbmin.x, unitPosition.y + bbmax.y, unitPosition.z + bbmax.z ), // 6
                    vec3_t( unitPosition.x + bbmax.x, unitPosition.y + bbmax.y, unitPosition.z + bbmax.z )  // 7
                };

                std::vector< vec2_t > screenCorners( 8 );
                bool canDraw = true;

                for ( int i = 0; i < 8; i++ )
                {
                    if ( !g_render->world_to_screen( worldCorners[ i ], screenCorners[ i ], matrix ) )
                    {
                        canDraw = false;
                        break;
                    }
                }

                if ( canDraw )
                {
                    ImU32 color = IM_COL32( 255, 0, 0, 255 );
                    float thickness = 1.0f;

                    g_render->line( screenCorners[ 0 ].x, screenCorners[ 0 ].y, screenCorners[ 1 ].x, screenCorners[ 1 ].y, color, thickness);
                    g_render->line( screenCorners[ 1 ].x, screenCorners[ 1 ].y, screenCorners[ 3 ].x, screenCorners[ 3 ].y, color, thickness);
                    g_render->line( screenCorners[ 3 ].x, screenCorners[ 3 ].y, screenCorners[ 2 ].x, screenCorners[ 2 ].y, color, thickness);
                    g_render->line( screenCorners[ 2 ].x, screenCorners[ 2 ].y, screenCorners[ 0 ].x, screenCorners[ 0 ].y, color, thickness);

                    g_render->line( screenCorners[ 4 ].x, screenCorners[ 4 ].y, screenCorners[ 5 ].x, screenCorners[ 5 ].y, color, thickness);
                    g_render->line( screenCorners[ 5 ].x, screenCorners[ 5 ].y, screenCorners[ 7 ].x, screenCorners[ 7 ].y, color, thickness);
                    g_render->line( screenCorners[ 7 ].x, screenCorners[ 7 ].y, screenCorners[ 6 ].x, screenCorners[ 6 ].y, color, thickness);
                    g_render->line( screenCorners[ 6 ].x, screenCorners[ 6 ].y, screenCorners[ 4 ].x, screenCorners[ 4 ].y, color, thickness);

                    g_render->line( screenCorners[ 0 ].x, screenCorners[ 0 ].y, screenCorners[ 4 ].x, screenCorners[ 4 ].y, color, thickness);
                    g_render->line( screenCorners[ 1 ].x, screenCorners[ 1 ].y, screenCorners[ 5 ].x, screenCorners[ 5 ].y, color, thickness);
                    g_render->line( screenCorners[ 2 ].x, screenCorners[ 2 ].y, screenCorners[ 6 ].x, screenCorners[ 6 ].y, color, thickness);
                    g_render->line( screenCorners[ 3 ].x, screenCorners[ 3 ].y, screenCorners[ 7 ].x, screenCorners[ 7 ].y, color, thickness);
                }
            }

            // cross
            {
            
                float centerX = GetSystemMetrics( SM_CXSCREEN ) / 2.0f;
                float centerY = GetSystemMetrics( SM_CYSCREEN ) / 2.0f;

                ImU32 color = IM_COL32( 0, 255, 0, 255 );
                ImU32 outline = IM_COL32( 0, 0, 0, 255 );

                int size = 10;
                int gap = 1;
                float thickness = 1.0f;
                float outlineThickness = 3.0f;

                g_render->line( centerX - size, centerY, centerX - gap, centerY, outline, outlineThickness );
                g_render->line( centerX + gap, centerY, centerX + size, centerY, outline, outlineThickness );
                g_render->line( centerX, centerY - size, centerX, centerY - gap, outline, outlineThickness );
                g_render->line( centerX, centerY + gap, centerX, centerY + size, outline, outlineThickness );

                g_render->line( centerX - size, centerY, centerX - gap, centerY, color, thickness );
                g_render->line( centerX + gap, centerY, centerX + size, centerY, color, thickness );
                g_render->line( centerX, centerY - size, centerX, centerY - gap, color, thickness );
                g_render->line( centerX, centerY + gap, centerX, centerY + size, color, thickness );

            }

		}

	}

}