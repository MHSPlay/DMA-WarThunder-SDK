#pragma once

enum e_draw_flags { drop_shadow, outline };

class c_render {
public:
    void init( );
    void line( float x1, float y1, float x2, float y2, ImU32 clr, float thickness = 1.0f ) const;
    void rect( float x, float y, float w, float h, ImU32 clr, float rounding = 0.0f ) const;
    void filled_rect( float x, float y, float w, float h, ImU32 color, float rounding, int flags ) const;
    static bool world_to_screen( const vec3_t& in, vec2_t& out, const ViewMatrix_t& matrix );
    void filled_rect_gradient( float x, float y, float w, float h, ImU32 col_upr_left, ImU32 col_upr_right,
                               ImU32 col_bot_right, ImU32 col_bot_left ) const;
    void triangle( float x1, float y1, float x2, float y2, float x3, float y3, ImU32 clr, float thickness ) const;
    void triangle_filled( float x1, float y1, float x2, float y2, float x3, float y3, ImU32 clr ) const;
    void circle( float x1, float y1, float radius, ImU32 col, int segments ) const;
    void circle_filled( float x1, float y1, float radius, ImU32 col, int segments ) const;

    void text( const vec2_t& txt_pos, ImU32 color, int flags,
               const std::string_view& message, ImFont* font ) const;

    template < typename... Args > void text( const float x, const float y, const ImU32 color, const int flags,
                                             const ImFont* font,
                                             const std::string_view& fmt, Args&&... args ) {
        text( vec2_t( x, y ), color, flags, font, std::vformat( fmt, std::make_format_args( args... ) ) );
    }

    auto& draw_list( ) { return m_draw_list; }
    auto& fonts( ) { return m_fonts; }

private:
	ImDrawList* m_draw_list{ };

    struct fonts_t {
        ImFont* m_esp{ };
    } m_fonts{ };

};

inline const std::unique_ptr< c_render > g_render{ new c_render( ) };