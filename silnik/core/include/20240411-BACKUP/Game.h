#ifndef NUDNY_SILNIK_GAME_H
#define NUDNY_SILNIK_GAME_H

#include "JSONLoader.h"
#include "GameState.h"

namespace n2d {
	class Game {
		protected:
			json*			mp_conf;
			std::unique_ptr<Game>	mp_state;
		public:
			Game();
			void Reset();
			void Load( json& t_conf );
			void Draw( sf::RenderWindow& );
			void Update( float );
			void Create( b2World& );
			void Events( sf::Event& );
	};
}; // namespace n2d

#endif
