#pragma once

namespace core 
{

	inline auto Thread( ) 
	{

        if ( !TargetProcess->Init( "aces.exe" ) )
        {
            LOG( "Failed to initialize process.\n" );
            return FALSE;
        }

        baseAddr = TargetProcess->GetBaseAddress( "aces.exe" );
        baseSize = TargetProcess->GetBaseSize( "aces.exe" );

        if ( !update::run( ) )
        {
            LOG( "Failed to update sdk.\n" );
            return FALSE;
        }

        if ( !sdk::init( ) )
        {
            LOG( "Failed to initialize sdk.\n" );
            return FALSE;
        }

		std::thread( [ & ]( ) 
        {
        
            while ( true ) 
            {

                misc::UpdateEntityList( );

                std::this_thread::sleep_for( std::chrono::milliseconds( 300 ) );
            }

        }).detach( );
	
	}

}