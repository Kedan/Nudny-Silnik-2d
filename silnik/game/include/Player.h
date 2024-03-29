#ifndef NUDNY_PLAYER_H
#define NUDNY_PLAYER_H

#include "ActorInterfaces.h"
#include "Actor.h"
#include "PlayerState.h"

namespace n2d {
	class Player :  public Actor {
		protected:
			PlayerState* 	m_state;
		public:
			
			bool toggle_crouch;
			
			Player();
			void Draw( sf::RenderWindow& );
			void Draw( sf::RenderWindow&, sf::Transform& );
			void Update( float );
			void Events( sf::Event& );
			void KeyPress( sf::Event& );
			void KeyRelease( sf::Event& );	
	}; // class Player
}; // namespace n2d;

#endif
