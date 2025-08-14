#pragma once

namespace core 
{

	inline auto Thread( ) 
	{

        if ( !TargetProcess->Init( processName ) )
        {
            LOG( "Failed to initialize process.\n" );
            return FALSE;
        }

        baseAddr = TargetProcess->GetBaseAddress( processName );
        baseSize = TargetProcess->GetBaseSize( processName );

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