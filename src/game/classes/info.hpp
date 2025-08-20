#pragma once

class c_info {
public:
	c_info( const std::uintptr_t base_address = 0 ) : base_address( base_address ) { }

public:

	auto getUnitType( ) -> std::string {
		return TargetProcess->ReadString( this->base_address + 0x38 ); // todo: fix
	}

	bool isPlane( ) {
		static const std::unordered_set< std::string > planeTypes = { "exp_bomber", "exp_assault", "exp_fighter" };
		return planeTypes.find( getUnitType( ) ) != planeTypes.end( );
	}


private:
	uintptr_t base_address;
};

