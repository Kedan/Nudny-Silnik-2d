#ifndef NUDNY_ANIMATION_H
#define NUDNY_ANIMATION_H

#include <tileson/tileson.h>
#include <Interfaces.h>
#include <Tool.h>

namespace n2d {
	
	/**
	 * Signle frame class. Used in frame animations
	 */	
	class Frame {
		public:
			/** Frame duration in seconds */
			float 		duration;

			/** 
			 * Drawind rect, texture coordinates [ x, y, width, height ].
			 * tson::DrawingRect equivalent, but in more universal format.
			 */
			glm::vec4	draw_rect;
			
			/**
			 * Default constructor
			 */
			Frame( float t_duration, glm::vec4 t_draw_rect ) : duration( t_duration ), draw_rect( t_draw_rect ) {};

			/** 
			 * Equality operator overloaded
			 */
			Frame& operator=( const Frame& ); 
	}; // class Frame

	/**
	 * Frame based animation class
	 */
	class FrameAnimation : public Animated {
		protected:
			bool	m_pause;
			bool	m_play;
			float	m_elapsed_time;
			int	m_current_frame = 0;
		public:
			bool	loop = false;
			float	speed = 1.0f;

			/** See n2d::Animated::Play */
			void Play();

			/** See n2d::Animated::Stop */
			void Stop();

			/** See n2d::Animated::Pause */
			void Pause();

	}; // class FrameAnimation

	/**
	 * Animation used by n2d::Sprite
	 */
	class SpriteAnimation : public FrameAnimation {
		public:
			float			m_duration;
			sf::Sprite*		mp_sprite;
			std::vector<Frame>	m_frames;
		public:
			/**
			 * Default constructor
			 */
			SpriteAnimation();

			/**
			 * Constructor with n2d::Sprite reference passed
			 */
			SpriteAnimation( sf::Sprite& );

			/**
			 * Set n2d::Sprite reference 
			 */
			void	SetSprite( sf::Sprite& );

			/**
			 * Adding single frame to animation
			 * @param	- frame duration
			 * @param	- drawing rectangle / texture coordinates.
			 */
			void 	AddFrame( float, glm::vec4 );

			/**
			 * Runs the animation. 
			 * Update() method equivalent
			 * @param	- time tick in seconds
			 */
			void 	Animate( float t_dt );

			/**
			 * Clear all frames
			 */
			void 	ClearAnimation();

			/**
			 * Load animation based on tson::Animation data.
			 * @param	- tson::Animation json data
			 * @param	- tson::Tileset json data
			 * @param	- IMPORTANT! Map grid size. Tileson get bad value if map uses tilesets with different tile sizes.
			 */
			void 	Load( tson::Animation&, tson::Tileset&, glm::vec2 );
			//void	Load( tson::Animation&, Tileset&, glm::vec2 );

			/**
			 * Return number of frames
			 */
			int	CountFrames();

			/**
			 * Return total animation duration in seconds
			 */
			float	GetDuration();

			/**
			 * Move animation to next frame
			 */
			void	NextFrame();

			/** 
			 * Move animation to previous frame
			 */
			void	PrevFrame();

			/**
			 * Return true if current frame time duration is passed.
			 */
			bool	IsTimeElapsed();

			/**
			 * Equal operator overload
			 */
			SpriteAnimation& operator=(const SpriteAnimation& );
	}; // class Animation
}; // namespace n2d

#endif 
