#pragma once

class c_entity {
public:
	auto init( ) -> bool {
		this->base_address = TargetProcess->Read< uintptr_t >( baseAddr + offsets::localplayer_offset );
		return this->base_address != 0;
	}

public:

    auto getGuiState( ) -> uint8_t {
		return TargetProcess->Read< uint8_t >( this->base_address + offsets::localplayer::guiState_offset );
	}

	auto getLocalUnit( ) -> c_unit {
		uintptr_t addr = TargetProcess->Read< uintptr_t >( this->base_address + offsets::localplayer::localunit_offset );
		return c_unit( addr - 1 );
	}

private:
    uintptr_t base_address;
};
