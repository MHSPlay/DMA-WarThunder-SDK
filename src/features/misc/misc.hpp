#pragma once

namespace misc
{
	inline std::vector< c_unit > unitsList;

	inline auto is_valid_enemy( c_unit unit ) -> bool
	{
		if ( unit.getUnitState( ) >= 1 ) 
			return false;
		
		const uint8_t unit_team = unit.getTeam( );
		if ( unit_team == 0 || unit_team == sdk::cLocalPlayer->getLocalUnit( ).getTeam( ) )
			return false;
		
		return true;
	}

	inline auto UpdateEntityList( ) -> void 
	{
		std::vector< c_unit > temp_units;

		// Our local is updated every game.
		sdk::cLocalPlayer->init( );

		if ( sdk::cLocalPlayer->getGuiState( ) != GuiState::ALIVE && sdk::cLocalPlayer->getGuiState( ) != GuiState::SPEC )
			return;

		VMMDLL_SCATTER_HANDLE hScatter = TargetProcess->CreateScatterHandle( );
		if ( !hScatter )
			return;

		const int unit_count = sdk::cGame->getUnitCount( );
		const uintptr_t unit_list_base = sdk::cGame->getUnitList( );
		auto scatter_unit = [ & ]( VMMDLL_SCATTER_HANDLE handle, uint32_t count ) -> std::vector< c_unit >
		{
			std::vector< std::uintptr_t > pointers( count );
			std::vector< c_unit > result;
			result.reserve( count );

			for (size_t i = 0; i < count; i++)
				TargetProcess->AddScatterReadRequest( handle, unit_list_base + 0x8 * i, &pointers[ i ], sizeof( std::uintptr_t ) );
			
			TargetProcess->ExecuteReadScatter( handle );

			for ( size_t i = 0; i < count; i++ )
				result.emplace_back( c_unit( pointers.at( i ) ) );

			TargetProcess->CloseScatterHandle( hScatter );
			return result;
		};

		std::vector< c_unit > units = scatter_unit( hScatter, unit_count );
		for ( c_unit unit : units ) 
		{
			if ( is_valid_enemy( unit ) )
				temp_units.emplace_back( unit );

		}

		unitsList = temp_units;
		temp_units.clear( );

	}

}