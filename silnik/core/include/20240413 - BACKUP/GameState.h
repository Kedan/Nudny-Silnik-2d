#ifndef NUDNY_SILNIK_GAME_STATE_H
#define NUDNY_SILNIK_GAME_STATE_H

#include "App.h"

namespace n2d {
	class GameContext;
	class IGameState {
		public:
			virtual bool Load() 	= 0;
			virtual void Enter() 	= 0;
			virtual void Exit() 	= 0;
		protected:
			virtual void Register( App& ) = 0;
	}; // class GameState
}; // namespace n2d

#endif
