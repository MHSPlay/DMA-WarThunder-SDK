#pragma once

#include "offsets.hpp"
#include "datatypes\vector2.hpp"
#include "datatypes\vector3.hpp"
#include "datatypes\matrix.hpp"

#define OFFSETS_WITH_BA(type, offset) \
    TargetProcess->Read< type >(this->base_address + (offset));

#define OFFSETS(type, offset) \
    TargetProcess->Read< type >((offset));

// classes
#include "classes\ballistic.hpp"
#include "classes\camera.hpp"
#include "classes\game.hpp"
#include "classes\movement.hpp"
#include "classes\info.hpp"
#include "classes\units.hpp"
#include "classes\entity.hpp"

enum GuiState : std::uint8_t {
	NONE = 0,
	MENU = 1,
	ALIVE = 2,
	DEAD = 3,
	SPEC = 6,
	SPAWN_MENU = 8,
	LOADING = 10
};

namespace sdk
{
	inline int screen_width = GetSystemMetrics( SM_CXSCREEN );
	inline int screen_height = GetSystemMetrics( SM_CYSCREEN );

	inline c_game* cGame = new c_game;
	inline c_entity* cLocalPlayer = new c_entity;

	inline auto init( ) -> bool 
	{
		if ( !cGame->init( ) )
			return false;

		if ( !cLocalPlayer->init( ) )
			return false;

		if ( !cGame->ballistics->init( cGame->get_base( ) ) )
			return false;

		if ( !cGame->camera->init( cGame->get_base( ) ) )
			return false;

		return true;
	}

}