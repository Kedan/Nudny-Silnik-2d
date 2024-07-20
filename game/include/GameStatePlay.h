#ifndef NUNDY_SILNIK_2D_GAME_STATE_PLAY_H
#define NUNDY_SILNIK_2D_GAME_STATE_PLAY_H

#include <Queue.h>
#include <GameState.h>

namespace nudny {
	class GameStatePlay : public GameState {
		protected:
			void 	Init();
			void	InitPhysics();
		public:
			void Simulate();
			void Draw( sf::RenderWindow& );
			void Draw( sf::RenderWindow&, sf::Transform& );
			void Update( sf::Time& );
			void Events( sf::Event& );
		protected:
			Queue	m_queue;
			float	m_time_step		= 1.0f / 60.0f;
			
			b2Vec2	m_gravity		= b2Vec2( 0, -9.81f );
			int 	m_velocity_iterations 	= 6;
			int 	m_position_iterations 	= 2;
			b2World	m_world 		= b2World( b2Vec2(0,-9.81f) );
	};
}; // namespace

#endif
