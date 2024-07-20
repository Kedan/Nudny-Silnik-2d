#ifndef NUDNY_SILNIK_2D_GAME_STATE_PLAY_SIDESCROLL_H
#define NUDNY_SILNIK_2D_GAME_STATE_PLAY_SIDESCROLL_H

#include <GameStatePlay.h>

namespace nudny {
	class GameStatePlaySidescroll : public GameStatePlay {
		protected:
			void 		Init();
			void		Step() {
				m_world.Step( m_time_step, m_velocity_iterations, m_position_iterations );
			}
			b2World& 	GetWorld() {
				return m_world;
			}
		protected:
			float		m_time_step		= 1.0f / 60.0f;
			int 		m_velocity_iterations 	= 6;
			int 		m_position_iterations 	= 2;
			b2World		m_world = b2World( b2Vec2(0,9.81f) );

	};
}; // namespace

#endif
