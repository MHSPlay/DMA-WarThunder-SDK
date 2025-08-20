#pragma once

// based on https://github.com/bditt/WarThunder-Offset-Dumper
namespace update
{
	const std::string expectedVersion;

    inline auto update( std::string version ) -> void
    {
        std::ofstream outFile( "offsets", std::ios::trunc );
        if ( outFile.is_open( ) )
        {
            // version
            outFile << version << std::endl;
            
            // c_game
            auto c_game = TargetProcess->FindSignature( "3C ? 4E 27 F6 7F ? 00 02", baseAddr, baseAddr + baseSize);
            if ( c_game < 0x100000 )
                outFile << "get c_game failed!" << std::endl;
            else
                outFile << "c_game: 0x" << std::hex << c_game - baseAddr << std::dec << std::endl;

            // c_local
            auto c_local = TargetProcess->FindSignature( "80 E9 ? 4B C0 01 ? 00 00", baseAddr, baseAddr + baseSize );
            if ( c_local < 0x100000 )
                outFile << "get c_local failed!" << std::endl;
            else
                outFile << "c_local: 0x" << std::hex << c_local - baseAddr << std::dec << std::endl;





            outFile.close();
        }
    }

    inline auto run() -> bool
    {
        const std::string current_version = TargetProcess->ReadString( baseAddr + 0x6631350 );

        if ( std::filesystem::exists( "offsets" ) )
        {
            std::string version;
            std::ifstream file( "offsets" );
            if ( file.is_open( ) )
            {
                std::getline( file, version );
                file.close( );
            }

            if ( version != current_version )
                update( current_version );
        }
        else
            update( current_version );
        
        return true;
    }

}