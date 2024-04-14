#ifndef NUDNY_SILNIK_GAME_STATE_FACTORY_H
#define NUDNY_SILNIK_GAME_STATE_FACTORY_H

#include "GameState.h"

namespace n2d {
	class GameStateFactory {
		protected:
			json	m_scenario;
		public:
			inline void 		SetScenario( json t_scenario) {
				m_scenario = t_scenario;
			}
			virtual GameState* 	CreateFromScenario( int ) 	= 0;
			virtual GameState* 	Create( int )			= 0;
	}; // class GameStateFactory;
}; // namespace n2d

#endif
