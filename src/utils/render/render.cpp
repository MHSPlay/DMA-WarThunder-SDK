#include "..\..\includes.hpp"

void c_render::init( ) {
    ImGui::CreateContext( );

    auto& io = ImGui::GetIO( );
    io.IniFilename = nullptr;
    io.LogFilename = nullptr;
    io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;

    m_fonts.m_esp = io.Fonts->AddFontFromFileTTF( "C:\\Windows\\Fonts\\Verdana.ttf", 16.0f );
    
    ImGui::GetIO( ).Fonts->AddFontDefault( );
}

void c_render::line( const float x1, const float y1, const float x2, const float y2, ImU32 clr, const float thickness ) const {
    m_draw_list->AddLine( ImVec2( x1, y1 ), ImVec2( x2, y2 ), clr, thickness );
}

void c_render::rect( const float x, const float y, const float w, const float h, ImU32 clr, const float rounding ) const {
    m_draw_list->AddRect( ImVec2( x, y ), ImVec2( x + w, y + h ), clr, rounding );
}

void c_render::filled_rect( const float x, const float y, const float w, const float h, ImU32 color, const float rounding, const int flags ) const {
    m_draw_list->AddRectFilled( ImVec2( x, y ), ImVec2( x + w, y + h ), color, rounding, flags );
}

void c_render::filled_rect_gradient( const float x, const float y, const float w, const float h, ImU32 col_upr_left, ImU32 col_upr_right, ImU32 col_bot_right, ImU32 col_bot_left ) const {
    m_draw_list->AddRectFilledMultiColor( ImVec2( x, y ), ImVec2( x + w, y + h ), col_upr_left, col_upr_right, col_bot_right, col_bot_left );
}

void c_render::triangle( const float x1, const float y1, const float x2, const float y2, const float x3, const float y3, ImU32 clr, const float thickness ) const {
    m_draw_list->AddTriangle( ImVec2( x1, y1 ), ImVec2( x2, y2 ), ImVec2( x3, y3 ), clr, thickness );
}

void c_render::triangle_filled( const float x1, const float y1, const float x2, const float y2, const float x3, const float y3, ImU32 clr ) const {
    m_draw_list->AddTriangleFilled( ImVec2( x1, y1 ), ImVec2( x2, y2 ), ImVec2( x3, y3 ), clr );
}

void c_render::circle( const float x1, const float y1, const float radius, ImU32 col, const int segments ) const {
    m_draw_list->AddCircle( ImVec2( x1, y1 ), radius, col, segments );
}

void c_render::circle_filled( const float x1, const float y1, const float radius, ImU32 col, const int segments ) const {
    m_draw_list->AddCircleFilled( ImVec2( x1, y1 ), radius, col, segments );
}

void c_render::text( const vec2_t& txt_pos, ImU32 color, const int flags, const std::string_view& message, ImFont* font ) const {
    m_draw_list->PushTextureID( font->ContainerAtlas->TexID );

    const auto size = font->CalcTextSizeA( font->LegacySize, FLT_MAX, 0.0f, message.data() );
    const auto pos = ImVec2( txt_pos.x - size.x / 2.0f, txt_pos.y );
    auto outline_clr = IM_COL32( 0, 0, 0, static_cast< int >( color * 0.3f ) );

    if ( flags & drop_shadow )
        m_draw_list->AddText( ImVec2( pos.x + 1, pos.y + 1 ), outline_clr, message.data( ) );

    if ( flags & outline ) {
        constexpr std::array< ImVec2, 8 > offsets = {
            { { 1, -1 }, { -1, 1 }, { -1, -1 }, { 1, 1 }, { 0, 1 }, { 0, -1 }, { 1, 0 }, { -1, 0 } }
        };

        for ( const auto& offset : offsets )
            m_draw_list->AddText( pos + offset, outline_clr, message.data( ) );
    }

    m_draw_list->AddText( pos, color, message.data( ) );

}

bool c_render::world_to_screen( const vec3_t& in, vec2_t& out, const ViewMatrix_t& matrix ) {
    const float w = matrix[ 0 ][ 3 ] * in.x + matrix[ 1 ][ 3 ] * in.y + matrix[ 2 ][ 3 ] * in.z + matrix[ 3 ][ 3 ];
 
    if ( w < 0.001f )
        return false;
 
    float x = in.x * matrix[ 0 ][ 0 ] + in.y * matrix[ 1 ][ 0 ] + in.z * matrix[ 2 ][ 0 ] + matrix[ 3 ][ 0 ];
    float y = in.x * matrix[ 0 ][ 1 ] + in.y * matrix[ 1 ][ 1 ] + in.z * matrix[ 2 ][ 1 ] + matrix[ 3 ][ 1 ];
 
    const float inv = 1.f / w;
    float nx = x * inv;
    float ny = y * inv;
 
    const ImVec2 size = ImGui::GetIO( ).DisplaySize;
    out.x = ( size.x * 0.5f * nx ) + ( nx + size.x * 0.5f );
    out.y = -( size.y * 0.5f * ny ) + ( ny + size.y * 0.5f );
 
    return true;

}