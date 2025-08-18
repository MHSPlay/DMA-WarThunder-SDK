#pragma once

namespace esp 
{

    inline std::array< vec3_t, 8 > calculate_bbox_corners( const vec3_t& position, const vec3_t& bbmin, const vec3_t& bbmax ) 
    {
        return 
        { {
            { position.x + bbmin.x, position.y + bbmin.y, position.z + bbmin.z }, // 0
            { position.x + bbmax.x, position.y + bbmin.y, position.z + bbmin.z }, // 1
            { position.x + bbmin.x, position.y + bbmax.y, position.z + bbmin.z }, // 2
            { position.x + bbmax.x, position.y + bbmax.y, position.z + bbmin.z }, // 3
            { position.x + bbmin.x, position.y + bbmin.y, position.z + bbmax.z }, // 4
            { position.x + bbmax.x, position.y + bbmin.y, position.z + bbmax.z }, // 5
            { position.x + bbmin.x, position.y + bbmax.y, position.z + bbmax.z }, // 6
            { position.x + bbmax.x, position.y + bbmax.y, position.z + bbmax.z }  // 7
        } };
    }

    inline void draw_wireframe_box( const std::array< vec2_t, 8 >& corners, ImU32 color, float thickness ) {

        g_render->line( corners[ 0 ].x, corners[ 0 ].y, corners[ 1 ].x, corners[ 1 ].y, color, thickness );
        g_render->line( corners[ 1 ].x, corners[ 1 ].y, corners[ 3 ].x, corners[ 3 ].y, color, thickness );
        g_render->line( corners[ 3 ].x, corners[ 3 ].y, corners[ 2 ].x, corners[ 2 ].y, color, thickness );
        g_render->line( corners[ 2 ].x, corners[ 2 ].y, corners[ 0 ].x, corners[ 0 ].y, color, thickness );

        g_render->line( corners[ 4 ].x, corners[ 4 ].y, corners[ 5 ].x, corners[ 5 ].y, color, thickness );
        g_render->line( corners[ 5 ].x, corners[ 5 ].y, corners[ 7 ].x, corners[ 7 ].y, color, thickness );
        g_render->line( corners[ 7 ].x, corners[ 7 ].y, corners[ 6 ].x, corners[ 6 ].y, color, thickness );
        g_render->line( corners[ 6 ].x, corners[ 6 ].y, corners[ 4 ].x, corners[ 4 ].y, color, thickness );

        g_render->line( corners[ 0 ].x, corners[ 0 ].y, corners[ 4 ].x, corners[ 4 ].y, color, thickness );
        g_render->line( corners[ 1 ].x, corners[ 1 ].y, corners[ 5 ].x, corners[ 5 ].y, color, thickness );
        g_render->line( corners[ 2 ].x, corners[ 2 ].y, corners[ 6 ].x, corners[ 6 ].y, color, thickness );
        g_render->line( corners[ 3 ].x, corners[ 3 ].y, corners[ 7 ].x, corners[ 7 ].y, color, thickness );
    }

    inline void draw_crosshair( ) {
        static float centerX = sdk::screen_width / 2.0f;
        static float centerY = sdk::screen_height / 2.0f;

        ImU32 color = IM_COL32( 0, 255, 0, 255 );

        int size = 10;
        int gap = 1;
        float thickness = 1.0f;
        float outlineThickness = 3.0f;

        g_render->line( centerX - size, centerY, centerX - gap, centerY, color, thickness );
        g_render->line( centerX + gap, centerY, centerX + size, centerY, color, thickness );
        g_render->line( centerX, centerY - size, centerX, centerY - gap, color, thickness );
        g_render->line( centerX, centerY + gap, centerX, centerY + size, color, thickness );
    }

    inline auto run( ) -> void 
	{
        // once
        const auto camera_matrix = sdk::cGame->camera->getCameraMatrix( );

        draw_crosshair( );

        // iter once player
        std::vector< c_unit > units = misc::unitsList;
		for ( c_unit& unit : units )
		{
            vec3_t unit_position = unit.getPosition( );
			if ( unit_position.empty( ) )
				continue;

            vec2_t screen_position;
			if ( !g_render->world_to_screen( unit_position, screen_position, camera_matrix ) )
				continue;

            const vec3_t local_position = sdk::cLocalPlayer->getLocalUnit( ).getPosition( );
            const int distance = static_cast< int >( local_position.dist_to( unit_position ) );
            if ( distance >= 1400 )
                continue;

            const vec3_t bbmin = unit.getBBMin( );
            const vec3_t bbmax = unit.getBBMax( );
            const auto world_corners = calculate_bbox_corners( unit_position, bbmin, bbmax );

            std::array< vec2_t, 8 > screen_corners;
            bool all_corners_visible = true;

            for ( size_t i = 0; i < world_corners.size( ); ++i ) 
            {
                if ( !g_render->world_to_screen( world_corners[ i ], screen_corners[ i ], camera_matrix ) )
                {
                    all_corners_visible = false;
                    break;
                }
            }

            float box_bottom_y = 0.0f;
            float box_right_x = 0.0f;
            if ( all_corners_visible ) 
            {
                draw_wireframe_box( screen_corners, IM_COL32( 255, 0, 0, 255 ), 1.0f);

                box_bottom_y = screen_corners[ 0 ].y;
                box_right_x = screen_corners[0].x;
                for ( size_t i = 1; i < screen_corners.size( ); ++i ) 
                {
                    box_bottom_y = max( box_bottom_y, screen_corners[ i ].y );
                    box_right_x = max( box_right_x, screen_corners[ i ].x );
                }

            }

            if ( box_bottom_y > 0.0f ) 
            {

                char distance_text[ 16 ];
                snprintf( distance_text, sizeof( distance_text ), "%dm", distance );

                const vec2_t text_position = {
                    screen_position.x,
                    box_bottom_y + 5.0f
                };

                g_render->text( text_position, IM_COL32( 255, 255, 255, 255 ), 0, distance_text, g_render->fonts( ).m_esp );

                uint8_t reload_time = unit.getReloadTime( );
                char reload_text[ 16 ];
                constexpr float stat = ( 10.f / 16 );
                float progress = stat * reload_time * 0.1f;

                snprintf( reload_text, sizeof( reload_text ), "%.1fs", /*static_cast< int >*/( progress ) );

                const vec2_t reload_pos = {
                    screen_position.x,
                    box_bottom_y + 20.0f
                };
            
                g_render->text( reload_pos, IM_COL32( 0, 200, 255, 255 ), 0, reload_text, g_render->fonts( ).m_esp );
            }

            aimbot::run( unit, unit_position, local_position, camera_matrix );

		}


	}



}