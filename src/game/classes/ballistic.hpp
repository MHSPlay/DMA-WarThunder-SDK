#pragma once

class c_ballistic {
public:
	auto init( uintptr_t cGame ) -> bool {
		this->base_address = TargetProcess->Read< uintptr_t >( cGame + offsets::cgame_offsets::ballistics_offset );
		return this->base_address != 0;
	}

public:

	auto getVelocity( ) -> float {
		return TargetProcess->Read< float >( this->base_address + offsets::cgame_offsets::ballistic_offsets::velocity );
	}

	auto getMass( ) -> float {
		return TargetProcess->Read< float >( this->base_address + offsets::cgame_offsets::ballistic_offsets::mass );
	}

	auto getCaliber( ) -> float {
		return TargetProcess->Read< float >( this->base_address + offsets::cgame_offsets::ballistic_offsets::caliber );
	}
	
	auto getLength( ) -> float {
		return TargetProcess->Read< float >( this->base_address + offsets::cgame_offsets::ballistic_offsets::length );
	}

	auto getImpactPoint( ) -> vec3_t {
		return TargetProcess->Read< vec3_t >( this->base_address + offsets::cgame_offsets::ballistic_offsets::bullet_impact_point );
	}

	auto getMaxDistance( ) -> float {
		return TargetProcess->Read< float >( this->base_address + offsets::cgame_offsets::ballistic_offsets::max_dist );
	}

	auto getBombImpactPoint() -> vec3_t {
		return TargetProcess->Read< vec3_t >(this->base_address + offsets::cgame_offsets::ballistic_offsets::bomb_impact_point);
	}


private:
	uintptr_t base_address;
};
