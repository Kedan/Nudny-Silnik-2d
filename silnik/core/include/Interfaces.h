#ifndef NUDNY_INTERFACE_H
#define NUDNY_INTERFACE_H

#include <chrono>
#include <iostream>
#include <sstream>
#include <glm/glm.hpp>
#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>

/**
 *
 *	n2d is namespace of Nudny Silnik 2D
 *
 */

namespace n2d {
	/**
	 * Interface.
	 * Abstract class.
	 * If something sopose to be visible on screen, should implements Drawable interface.
	 */ 
	class Drawable {
		protected:
			/**
			 * Transformations used in rendering
			 */	
			sf::Transform transform;
		public:
			/**
			 * Drawing method
			 * @param	&t_window	- render window reference
			 */
			virtual void Draw( sf::RenderWindow& t_window ) = 0;
			
			/**
			 * Drawing method
			 * @param	&t_window	- render window reference
			 * @param	&t_transform	- additional transformations reference
			 */
			virtual void Draw( sf::RenderWindow& t_window, sf::Transform& t_transform ) = 0;
	};

	/**
	 * Interface. 
	 * Abstract class.
	 * If something sopose to be change in time, should implements Updatable interface
	 */
	class Updatable {
		public:			
			/**
			 * Update method
			 * @param	t_dt	- time tick, passed in n2d::App::Run() from sf::Clock and sf::Time class
			 */
			virtual void Update( float t_dt ) = 0;
	};
	
	/**
	 * Interface.
	 * Abstract clas.
	 * If something sopose to be initiated by physics system, should implements Creatable interface.
	 */
	class Creatable {
		public:
			/**
			 * Creation method. This method id called whenever object need to be initiaded by Box2D, for physics simulation.
			 * @param	&t_world	- Box2D world reference, that should refere to n2d::App::world
			 */
			virtual void Create( b2World& t_world ) = 0;
	};
	
	/**
	 * Interface.
	 * Abstrac class.
	 * If something sopose to react to event, should implements Interactive interface.
	 */
	class Interactive {
		protected:
			/**
			 * Interactive flag. If set to false, object must not react for events
			 */
			bool m_interactive = true;
		public:
			/**
			 * Return true, is object is "awake"
			 * @return	bool
			 */ 
			inline bool	IsInteractive() {
				return m_interactive;
			};
			/**
			 * Event handling method.
			 * @param	&t_event	- SFML event reference, passed in n2d::App::Run() method 
			 */ 
			virtual void Events( sf::Event& t_event ) = 0;
	};
	
	class Playable 	{
		public:
			/**
			 * Play method.
			 */ 
			virtual void Play() 	= 0;

			/**
			 * Pause method. Freezes animation in current frame.
			 */
			virtual void Pause()	= 0;

			/**
			 * Stop methos. Rewind animation to first frame.
			 */
			virtual void Stop()	= 0;
	};

	/**
	 * Interface.
	 * Abstrac class.
	 * If something sopose to be played animated, should implements Animated interface.
	 */
	class Animated : public Playable {
		public:
			/**
			 * Delete all frames
			 */ 
			virtual void ClearAnimation() 		= 0;

			/**
			 * Runs the animation. Equivalent of Update() method - but Update() should handle chages related with physics.
			 * @param	t_dt	- time tick, passed in n2d::App::Run() from sf::Clock and sf::Time class
			 */
			virtual void Animate( float t_dt ) 	= 0;
	};

	class Audible : public Playable {
		public:
			virtual void SetVolume( float ) = 0;
	};

	/**
	 * Interface.
	 * Abstract class.
	 * Allows to change some physical properties of object ( i.e. position, velocity, etc.. )
	 */
	class Physical {
		public: // virtual setters
			virtual void 		SetPosition( float, float ) 		= 0;
			virtual void 		SetVelocity( float, float ) 		= 0;
			virtual void 		SetRotation( float ) 			= 0;
			virtual void 		SetAngularVelocity( float, float ) 	= 0;
			virtual void 		SetSize( float, float ) 		= 0;
			virtual void 		SetScale( float, float ) 		= 0;

		public: // virtual getters
			virtual glm::vec2 	GetPosition();
	};

	class Colored {
		public:
			virtual void 		SetColor( float, float, float, float ) 	= 0;
			virtual void 		SetAlpha( float ) 			= 0;
			virtual void 		SetVisible( bool ) 			= 0;
		public:
			virtual float 		GetAlpha() 	= 0;
			virtual glm::vec4 	GetColor() 	= 0;
			virtual glm::vec4	GetRGBA() 	= 0;
			virtual glm::vec3	GetRGB()	= 0;
	};

	class Textured {
		public:
			virtual void		SetTexture( sf::Texture& ) 			= 0;
			virtual void		SetTextureCoords( float, float, float, float )	= 0;
			virtual sf::Texture&	GetTexture() 					= 0;
			virtual glm::vec4	GetTextureCoords()				= 0;
	};
}; // namespace n2d

#endif
