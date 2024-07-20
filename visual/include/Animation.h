#ifndef NUDNY_SILNIK_2D_VISUAL_ANIMATION_H
#define NUDNY_SILNIK_2D_VISUAL_ANIMATION_H

#include <tileson/tileson.h>
#include <Interfaces.h>
#include <Tool.h>

namespace nudny {
	class Frame {
		public:
			float 		duration;
			glm::vec4	draw_rect;
			Frame( float t_duration, glm::vec4 t_draw_rect ) : duration( t_duration ), draw_rect( t_draw_rect ) {};
			Frame& operator=( const Frame& ); 
	}; // class Frame

	class FrameAnimation : public Animated, public Playable {
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
			void Loop( bool );
			bool IsPaused();
			bool IsPlaying();
			bool IsLooped();

	}; // class FrameAnimation

	class SpriteAnimation : public FrameAnimation {
		public:
			float			m_duration;
			sf::Sprite*		mp_sprite;
			std::vector<Frame>	m_frames;
		public:
			SpriteAnimation();
			SpriteAnimation( sf::Sprite& );
			void			SetSprite( sf::Sprite& );
			void 			AddFrame( float, glm::vec4 );
			void 			Animate( sf::Time& t_dt );
			void 			ClearAnimation();
			int			CountFrames();
			float			GetDuration();
			void			NextFrame();
			void			PrevFrame();
			bool			IsTimeElapsed();
			SpriteAnimation&	operator=(const SpriteAnimation& );
	}; // class Animation
}; // namespace nudny

#endif 
