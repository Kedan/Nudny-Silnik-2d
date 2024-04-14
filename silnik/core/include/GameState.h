#ifndef NUDNY_SILNIK_GAME_STATE_H
#define NUDNY_SILNIK_GAME_STATE_H

namespace n2d {
	class App;
	class GameState {
		public:
			virtual void 		Enter( App& ) 			= 0;
			virtual void		 Exit( App& ) 			= 0;
			virtual GameState*	 Dispatch( App&, sf::Event& ) 	= 0;
	}; // class GameState
}; // namespace n2d

#endif
