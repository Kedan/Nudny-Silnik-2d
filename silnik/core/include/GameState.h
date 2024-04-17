#ifndef NUDNY_SILNIK_GAME_STATE_H
#define NUDNY_SILNIK_GAME_STATE_H

namespace n2d {
	class App;
	/**
	 * Game state class. Interface. Abstract class. The game may be in many different states, i.e.: in menu, play cinematic, loading level, waiting for connection etc.
	 * Every game/state MUST inherits from n2d::GameState. 
	 * 
	 */
	class GameState {
		public:
			/**
			 * Method called right after game state is created. When you implement this, remember it should do some things:
			 * load resources, maps, create objects and all nesesery thing game need to run. IT MUST put alla drawable, updatable and interactive objects 
			 * into n2d::App lists!... Well, actuallu it doesnt have to. It's not like it's gonna crash, or something. But if you dont fill those lists - 
			 * all you see on screen, will be deep, beautyfull and mysterious, 24-bit blackness...
			 * @param n2d::App instance reference
			 */
			virtual void 		Enter( App& ) 			= 0;

			/**
			 * Method that is called right before destructor is called.
			 * If you want to do some stuff ( like free resources, or play some custom animation ) when game/state is ending - do it here.
			 * DO NOT remove drawable, updatable, interactive objects from n2d:App lists. n2d::App do it for you automatically.
			 * @param n2d::App instance reference
			 */
			virtual void		Exit( App& ) 			= 0;

			/**
			 * Method that check if game/state should change.
			 * @param n2d::App	- reference
			 * @param sf::Event 	- reference ( passed in n2d::App::Run() method in main loop)
			 * @return	- pointer to new GameState if state should change. nullptr if state stays the same.
			 */
			virtual GameState*	Dispatch( App&, sf::Event& ) 	= 0;
	}; // class GameState
}; // namespace n2d

#endif
