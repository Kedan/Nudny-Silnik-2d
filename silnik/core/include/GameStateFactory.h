#ifndef NUDNY_SILNIK_GAME_STATE_FACTORY_H
#define NUDNY_SILNIK_GAME_STATE_FACTORY_H

#include "GameState.h"

namespace n2d {
	/**
	 * Creates game state objects depending on passed parameter. You need pass it to n2d::App instance. 
	 * n2d::App creates 
	 *
	 */
	class GameStateFactory {
		protected:
			/** 
			 * Sequence of game states in json file.
			 * It doesn't matter whats inside. That depend on you. You may pass anything you want,
			 * but remember you should be able to create some game state object, based on this file, so IMO
			 * it should have at least "type" field, definig game state type. I suggest also attributes like: 
			 * game duration, max score, list of resources, path to game logic script etc...
			 */ 
			json	m_scenario;
		public:
			/**
			 * Set scenerio ( sequence of game states ).
			 * @param t_scenerio - json file
			 */
			inline void 		SetScenario( json t_scenario ) {
				m_scenario = t_scenario;
			}

			/**
			 * Create game state from scenario.
			 * @param t_game_state_id - game state ID (int) in scenario
			 */
			virtual GameState* 	CreateFromScenario( int t_game_state_id ) 	= 0;

			/**
			 * Create game state based on game state TYPE.
			 * @param t_game_state_type - game state type represented by int. You can, and propably will, use your own enum.
			 */
			virtual GameState* 	Create( int t_game_state_type )			= 0;
	}; // class GameStateFactory;
}; // namespace n2d

#endif
