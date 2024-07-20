#ifndef NUDNY_SILNIK_2D_GAME_STATE_CINAMETIC_H
#define NUDNY_SILNIK_2D_GAME_STATE_CINAMETIC_H

#include <nudny/silnik/Core.h>
#include <nudny/silnik/Utils.h>

namespace nudny {
	class GameStateCinematic : public GameState {
		public:
			void Draw( sf::RenderWindow& );
			void Draw( sf::RenderWindow&, sf::Transform& );
			void Update( sf::Time& );
			void Events( sf::Event& );
			void Enter( App& );
			void Exit( App& );

			void Load( json t_config );	
	}; // class
}; // namespace 

#endif
