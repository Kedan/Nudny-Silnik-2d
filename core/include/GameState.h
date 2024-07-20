#ifndef NUDNY_SILNIK_2D_CORE_GAME_STATE_H
#define NUDNY_SILNIK_2D_CORE_GAME_STATE_H

#include <memory>
#include <nudny/silnik/Utils.h>
#include <Interfaces.h>
#include <Keyboard.h>

namespace nudny {
	class App;
	class GameState : 
		public Drawable, 
		public Interactive,
		public Updatable {
		public:
			virtual void 				Enter( App& ) 			= 0;
			virtual void				Exit( App& ) 			= 0;
			virtual std::unique_ptr<GameState>	Dispatch( App&, sf::Event& ) 	= 0;
			virtual void 				Load( json t_config )		= 0;

			inline bool IsHeld( sf::Keyboard::Key t_k ) {
				return Keyboard::Instance().IsHeld( t_k );
			}
			inline bool WasPressed( sf::Keyboard::Key t_k ) {
				return Keyboard::Instance().WasPressed( t_k );
			}
			inline bool WasReleased( sf::Keyboard::Key t_k ) {
				return Keyboard::Instance().WasReleased( t_k );
			}

			virtual void Simulate() = 0;
	}; // class GameState
}; // namespace n2d

#endif
