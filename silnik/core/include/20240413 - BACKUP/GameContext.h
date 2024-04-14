#ifndef NUDNY_SILNIK_GAME_CONTEXT_H
#define NUDNY_SILNIK_GAME_CONTEXT_H

#include "GameState.h"

namespace n2d {
	class GameContext { 
		protected:
			GameState* 		mp_state;
		public:
			GameContext(){};
			void Register( App& );
			void Events( sf::Event& );
	}; // class GameContext;
}; // namespace n2d

#endif
