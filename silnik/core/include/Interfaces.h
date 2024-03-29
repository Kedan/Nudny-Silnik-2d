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
	 * Constant value to calculate screen, in pixel, coordinates, to Box2D, in meters, coordinates. 
	 */
	const float PIXEL_TO_BOX2D = 0.01f;
	
	/** 
	 * Constant value to calculate Box2D, in meters, coordinates, to screen, in pixels, coordinates. 
	 */
	const float BOX2D_TO_PIXEL = 100.0f;
	
	/** 
	 * This class contains some handy, static methods, used i.e. for type or coordinate systems conversions. 
	 */
	class Tool {
		public:
			/** Convert 2D vector form glm to box2D ( glm::vec2 to b2Vec2 )
			 *	@param v - glm vector to convert
			 *	@param s - coordinates conversion multiplayer 
			 *	@return box2D vector */
			static b2Vec2 g2b( glm::vec2 v, float s = PIXEL_TO_BOX2D ) { 
				return b2Vec2( v.x*s, v.y*s );
			}
			
			/** Convert 2D vector from SFML to box2D ( sf::Vector2f to b2Vec2 )
			 *	@param v - SFML vector
			 *	@param s - coordinates conversion multiplayer 
			 *	@return box2d vector */ 
			static b2Vec2 s2b( sf::Vector2f v, float s = PIXEL_TO_BOX2D ) {
				return b2Vec2( v.x*s, v.y*s );
			}
			
			/** Convert 2D vector from box2D to glm ( b2Vec2 to glm::vec2)
			 *	@param v - box2D vector
			 *	@param s - coordinates conversion multiplayer 
			 *	@return glm vector */ 
			static glm::vec2 b2g( b2Vec2 v, float s = BOX2D_TO_PIXEL ) {
				return glm::vec2( v.x*s, v.y*s );
			}
			
			/** Convert 2D vector from sfml to glm ( sf::Vector2f to glm::vec2)
			 *	@param v - SFML vector
			 *	@return glm vector */ 
			static glm::vec2 s2g( sf::Vector2f v ) {
				return glm::vec2( v.x, v.y );
			}
			
			/** Convert 2D vector from glm to SFML ( glm::vec2 to sf::Vector2f )
			 *	@param v - glm vector
			 *	@return SFML vector */ 
			static sf::Vector2f g2s( glm::vec2 v ) {
				return sf::Vector2f( v.x, v.y );
			}
			
			/** 
			 * Convert 2D vector from box2D to SFML ( b2Vec2 to sf::Vector2f )
			 * @param	v 	- box2D vector
			 * @return 		SFML vector 
			 */ 
			static sf::Vector2f b2s( b2Vec2 v ) {
				return sf::Vector2f( v.x*BOX2D_TO_PIXEL, v.y*BOX2D_TO_PIXEL );
			}
			
			/** 
			 * Convert degrees to radians
			 * @param	deg	- angle in degrees
			 * @return 		angle in radians  
			 */ 
			static float rad( float deg ) {
				return deg *  (3.1415f/180.0f);
			}
			
			/** 
			 * Convert radians to degrees
			 * @param	rad	- angle in radians
			 * @return 		angle in degrees  
			 */ 
			static float ang( float rad ) {	
				return rad * 180.f / 3.1415f;
			}
			
			/** 
			 * Convert float value from SFML, pixel-coordinate system, to box2d meter-coordinate system 
			 * @param	val	- value (i.e. distance ) in pixels
			 * @return 		value in meters
			 */ 
			static inline float Bf( float val ) {
				return val * PIXEL_TO_BOX2D;
			}
			
			/** 
			 * Convert float value from box2d meter-coordinate system to SFML, pixel-coordinate system 
			 * @param	val	- value (i.e. distance ) in meters
			 * @return 		value in pixels
			 */ 
			static inline float Bs( float val ) {
				return val * BOX2D_TO_PIXEL;
			}
			
			/**
			 * Calculate vertexes coords, rotated by given angle
			 * @param	t_v		- vector of vertexes
			 * @param	t_rotation	- angle in degrees
			 * @return	std::vector<glm::vec2> - vector of rotated vertexes
			 */
			static inline std::vector<glm::vec2> Rotate( std::vector<glm::vec2> t_v, float t_rotation ) {
				std::vector<glm::vec2> rv = t_v;
				if( t_rotation != 0.0f ) {
					rv.clear();
					float rad = Tool::rad( t_rotation );
					float sin = glm::sin( rad );
					float cos = glm::cos( rad );
					glm::mat2x2 m( cos, -sin, sin, cos );
					for( auto w : t_v ) {
						rv.push_back( m * w );
					}
				}
				return rv;
			}

			/**
			 * Calculate vertexes coords, translated by given vector
			 * @param	t_v		- vector of vertexes
			 * @param	t_translation	- translation vector
			 * @return	std::vector<glm::vec2> - vector of translated vertexes
			 */
			static inline std::vector<glm::vec2> Translate( std::vector<glm::vec2> t_v, glm::vec2 t_translation  ) {				
				std::vector<glm::vec2> rv;
				for( auto w : t_v ) {
					rv.push_back(w+t_translation);
				}
				return rv;
			}

			// Calculate rotated and translated vertexes coordinates			
			/**
			 * Calculate vertexes coords, translated by given vector, and rotated by given angle
			 * @param	t_v		- vector of vertexes
			 * @param	t_translation	- translation vector
			 * @param	t_rotation	- angle in degrees
			 * @return	std::vector<glm::vec2> - vector of translated and rotated vertexes
			 */
			static inline std::vector<glm::vec2> Transform( std::vector<glm::vec2> t_v, glm::vec2 t_translation, float t_rotation ) {				
				std::vector<glm::vec2> rv;
				if( t_rotation != 0 ) {
					float rad = Tool::rad( t_rotation );
					float sin = glm::sin( rad );
					float cos = glm::cos( rad );
					glm::mat2x2 m( cos, -sin, sin, cos );
					for( auto w : t_v ) {
						glm::vec2 tmp = m * w;
						tmp = tmp + t_translation;
						rv.push_back(tmp);
					}
				} else {
					for( auto w : t_v ) {
						glm::vec2 tmp = w + t_translation;
						rv.push_back( tmp );
					}
				}
				return rv;
			}
			
			/**
			 * Returns current Date/Time stamp
			 * @return	datetime string
			 */
			static std::string GetCurrentDatetime() {
				auto now = std::chrono::system_clock::now();
   				auto in_time_t = std::chrono::system_clock::to_time_t(now);
    				std::stringstream ss;
    				ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X");
    				return ss.str();
			}

	};
	
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

	/**
	 * Interface.
	 * Abstrac class.
	 * If something sopose to be played animated, should implements Animated interface.
	 */
	class Animated {
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
}; // namespace n2d

#endif
