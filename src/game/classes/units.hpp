#pragma once

class c_movement_ground;

class c_unit {
public:

	auto get_base( ) -> uintptr_t {
		return this->base_address;
	}

	c_unit( const std::uintptr_t base_address = 0 ) : base_address( base_address ) { }

public:

	auto getBBMax( ) -> vec3_t {
		return TargetProcess->Read< vec3_t >( this->base_address + 0x022C );
	}

	auto getBBMin( ) -> vec3_t {
		return TargetProcess->Read< vec3_t >( this->base_address + 0x0220 );
	}

	auto getMovement( ) -> c_movement_ground {
		uintptr_t addr = TargetProcess->Read< uintptr_t >( this->base_address + offsets::unit_offsets::groundmovement_offset );
		return c_movement_ground( addr );
	}

	auto getPosition( ) -> vec3_t {
		return TargetProcess->Read< vec3_t >( this->base_address + 0xAE8 );
	}

	auto getInvulnerable( ) -> uintptr_t {
		return TargetProcess->Read< uintptr_t >( this->base_address + 0x0C40 );
	}

	auto getUnitState( ) -> uint16_t {
		return TargetProcess->Read< uint16_t >( this->base_address + offsets::unit_offsets::unitState_offset );
	}

	auto getTeam( ) -> uint8_t {
		return TargetProcess->Read< uint8_t >( this->base_address + 0x0DB0 ); // unitArmyNo
	}

private:
	uintptr_t base_address;

};
