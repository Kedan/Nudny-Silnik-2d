#ifndef NUDNY_ANIMATION_H
#define NUDNY_ANIMATION_H

#include <tileson/tileson.h>
#include <Interfaces.h>

namespace n2d {
	
	class Frame {
		public:
			float 		duration;
			glm::vec4	draw_rect;

			Frame( float t_duration, glm::vec4 t_draw_rect ) : duration( t_duration ), draw_rect( t_draw_rect ) {};
			Frame& operator=( const Frame& ); 
	}; // class Frame

	class FrameAnimation : public Animated {
		protected:
			bool	m_pause;
			bool	m_play;
			float	m_elapsed_time;
			int	m_current_frame = 0;
		public:
			bool	loop = false;
			float	speed = 1.0f;

			void Play();
			void Stop();
			void Pause();

	}; // class FrameAnimation

	class SpriteAnimation : public FrameAnimation {
		public:
			float			m_duration;
			sf::Sprite*		mp_sprite;
			std::vector<Frame>	m_frames;
		public:
			SpriteAnimation();
			SpriteAnimation( sf::Sprite& );
			void	SetSprite( sf::Sprite& );
			void 	AddFrame( float, glm::vec4 );
			void 	Animate( float t_dt );
			void 	ClearAnimation();
			void 	Load( tson::Animation&, tson::Tileset&  );
			int	CountFrames();
			float	GetDuration();
			void	NextFrame();
			void	PrevFrame();
			bool	IsTimeElapsed();
			SpriteAnimation& operator=(const SpriteAnimation& );
	}; // class Animation
}; // namespace n2d

#endif 
