#pragma once

namespace core 
{

	inline auto Thread( ) -> bool
	{

        if ( !TargetProcess->Init( "aces.exe" ) )
        {
            LOG( "Failed to initialize process.\n" );
            return false;
        }

        baseAddr = TargetProcess->GetBaseAddress( "aces.exe" );
        baseSize = TargetProcess->GetBaseSize( "aces.exe" );

        if ( !update::run( ) )
        {
            LOG( "Failed to update sdk.\n" );
            return false;
        }

        update::parse_offsets( );

        if ( !sdk::init( ) )
        {
            LOG( "Failed to initialize sdk.\n" );
            return false;
        }

		std::thread( [ & ]( ) 
        {
        
            while ( true ) 
            {

                misc::UpdateEntityList( );

                std::this_thread::sleep_for( std::chrono::milliseconds( 300 ) );
            }

        }).detach( );
	    
        return true;
	}

}