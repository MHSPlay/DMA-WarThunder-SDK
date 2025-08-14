#pragma once

namespace GUI
{

	inline auto OnRender( ) -> void
	{
	
		ImGui::SetNextWindowSize( ImVec2( 350, 350 ), ImGuiCond_Once );
		ImGui::Begin( "SDK - https://github.com/MHSPlay", nullptr );
		{
			
			ImGui::Text( "Hello World!" );

		}
		ImGui::End( );
	}

}