#pragma once

// based on https://github.com/bditt/WarThunder-Offset-Dumper
namespace update
{
	const std::string expectedVersion;

    inline bool parse_offsets( const std::string& filename = "offsets" )
    {
        std::ifstream file( filename );
        if ( !file.is_open( ) )
            return false;
        
        std::string line;
        std::unordered_map< std::string, uintptr_t > offset_map;
        
        // skip version
        if ( !std::getline( file, line ) )
        {
            std::cerr << "Empty offsets file" << std::endl;
            return false;
        }

        while ( std::getline( file, line ) )
        {
            if ( line.find( "failed" ) != std::string::npos )
            {
                std::cerr << "Warning: " << line << std::endl;
                continue;
            }

            size_t colon_pos = line.find( ':' );
            if ( colon_pos == std::string::npos )
                continue;

            std::string offset_name = line.substr( 0, colon_pos );
            
            size_t hex_pos = line.find( "0x", colon_pos );
            if ( hex_pos == std::string::npos )
                continue;

            std::string hex_value = line.substr( hex_pos + 2 );
            
            std::stringstream ss;
            ss << std::hex << hex_value;
            
            uintptr_t value;
            if ( ss >> value )
                offset_map[ offset_name ] = value;
            
        }

        file.close( );

        // parse
        if ( offset_map.find( "c_game" ) != offset_map.end( ) ) 
            offsets::cgame_offset = offset_map[ "c_game" ];

        if ( offset_map.find( "c_local" ) != offset_map.end( ) ) 
            offsets::localplayer_offset = offset_map[ "c_local" ];

        return true;
    }

    inline auto update( std::string version ) -> void
    {
        std::ofstream outFile( "offsets", std::ios::trunc );
        if ( outFile.is_open( ) )
        {
            // version
            outFile << version << std::endl;
            
            // c_game
            auto c_game = TargetProcess->FindSignature( "90 96 e8 ? ? ? ? 00 40", baseAddr, baseAddr + baseSize);
            if ( c_game < 0x100000 )
                outFile << "get c_game failed!" << std::endl;
            else
                outFile << "c_game: 0x" << std::hex << c_game - baseAddr << std::dec << std::endl;

            // c_local
            auto c_local = TargetProcess->FindSignature( "E0 ? 7F ? C0 01 ? 00 00", baseAddr, baseAddr + baseSize );
            if ( c_local < 0x100000 )
                outFile << "get c_local failed!" << std::endl;
            else
                outFile << "c_local: 0x" << std::hex << c_local - baseAddr << std::dec << std::endl;

            outFile.close( );
        }
    }

    inline auto run( ) -> bool
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