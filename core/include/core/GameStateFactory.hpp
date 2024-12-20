#ifndef NUDNY_SLINIK_2D_CORE_GAME_STATE_FACTORY_HPP
#define NUDNY_SLINIK_2D_CORE_GAME_STATE_FACTORY_HPP

#include <core/GameState.hpp>

namespace ns {
	class GameStateFactory {
		public:
			virtual std::unique_ptr<GameState> create(int) const = 0;
	};
};

#endif
