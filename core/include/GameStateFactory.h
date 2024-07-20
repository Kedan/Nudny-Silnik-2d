#ifndef NUDNY_SILNIK_2D_CORE_GAME_STATE_FACTORY_H
#define NUDNY_SILNIK_2D_CORE_GAME_STATE_FACTORY_H

#include <memory>
#include "GameState.h"

namespace nudny {
	class GameStateFactory {
		public:
			virtual std::unique_ptr<GameState> 	Create( int t_game_state_type )			= 0;
	}; // class GameStateFactory;
}; // namespace n2d

#endif
