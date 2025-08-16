#pragma once

class c_movement_ground {
public:
	c_movement_ground( const std::uintptr_t base_address = 0 ) : base_address( base_address ) { }

public:

	auto velocity( ) -> vec3_t {
		return TargetProcess->Read< vec3_t >( this->base_address + offsets::unit_offsets::ground_velocity_offset );
	}

private:
	uintptr_t base_address;
};

