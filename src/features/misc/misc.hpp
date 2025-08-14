#pragma once

namespace misc
{
	inline std::vector< uintptr_t > units;

	inline auto UpdateEntityList( ) -> void 
	{
		uintptr_t local = TargetProcess->Read< uintptr_t >( baseAddr + offsets::localplayer_offset );
		uintptr_t cGame = TargetProcess->Read< uintptr_t >( baseAddr + offsets::cgame_offset );
		if ( !local || !cGame )
		{
			LOG( "offsets outdated...\n" );
			return;
		}

		uint8_t localGuiState = TargetProcess->Read< uint8_t >( local + offsets::localplayer::guiState_offset );
		if ( localGuiState != 2 && localGuiState != 6 )
			return;

		uintptr_t localUnit = TargetProcess->Read< uintptr_t >( local + offsets::localplayer::localunit_offset ) - 1;
		uintptr_t unitList3 = TargetProcess->Read< uintptr_t >( cGame + 0x340 );
		uint16_t unitCount3 = TargetProcess->Read< uint16_t >( cGame + 0x350 );

		uint8_t localTeam = TargetProcess->Read< uint8_t >( localUnit + offsets::unit_offsets::unitArmyNo_offset );

		units.clear( );
		for ( int i = 0; i < static_cast< int >( unitCount3 ); ++i )
		{
			uintptr_t unitAddr = TargetProcess->Read< uintptr_t >( unitList3 + ( i * sizeof( uintptr_t ) ) );

			if ( !unitAddr )
				continue;

			if ( unitAddr == localUnit )
				continue;

			auto IsAlive = [ & ]( ) -> bool
			{
				uint16_t unitState = TargetProcess->Read< uint16_t >( unitAddr + offsets::unit_offsets::unitState_offset );

				if ( unitState >= 2 )
					return false;

				return true;
			};

			if ( !IsAlive( ) )
				continue;

			uint8_t unitTeam = TargetProcess->Read< uint8_t >( unitAddr + offsets::unit_offsets::unitArmyNo_offset );
			if ( unitTeam == localTeam )
				continue;

			units.push_back( unitAddr );

		}

	}

}