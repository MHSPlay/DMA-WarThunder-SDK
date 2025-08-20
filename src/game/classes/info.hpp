#pragma once

class c_info {
public:
	c_info( const std::uintptr_t base_address = 0 ) : base_address( base_address ) { }

public:

	auto getVehicleName( ) -> std::string {
		uintptr_t addr = TargetProcess->Read< uintptr_t >( this->base_address + 0x28 );
		return TargetProcess->ReadString( addr );
	}

	auto getUnitType( ) -> std::string {
		uintptr_t addr = TargetProcess->Read< uintptr_t >( this->base_address + 0x38 );
		return TargetProcess->ReadString( addr );
	}

	bool isPlane( ) {
		static const std::unordered_set< std::string > planeTypes = { "exp_bomber", "exp_assault", "exp_fighter" };
		return planeTypes.find( getUnitType( ) ) != planeTypes.end( );
	}


private:
	uintptr_t base_address;
};

