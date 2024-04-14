#ifndef NUDNY_SILNIK_TOOL_H
#define NUDNY_SILNIK_TOOL_H

#include <chrono>
#include <iostream>
#include <sstream>
#include <glm/glm.hpp>
#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>
#include <tileson/tileson.h>

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

			/**
			 * Calculate correct value of tile drawing rect.
			 * Tileson gets wrong one, if use tiles with different sizes
			 * @param	&t_rect		- Tileson drawing rect tson::Tile::getDrawingRect()
			 * @param	t_grid_size	- Tileson tile size read from tson::Map class -> tson::Map::getTileSize(), converted to glm::vec2
			 * @return			- Corrected drawing rect
			 */
			static tson::Rect GetDrawingRectT( tson::Rect t_draw_rect, glm::vec2 t_grid_size) {
				tson::Rect r;
				r.x = t_draw_rect.x;
				r.y = t_draw_rect.y;
				int i = 1;
				if( t_grid_size.x != t_draw_rect.width ) {
					i = (int)(t_draw_rect.x / t_grid_size.x);
					r.x = i * t_draw_rect.width;
				}
				if( t_grid_size.y != t_draw_rect.height ) {
					i = (int)(t_draw_rect.y / t_grid_size.y);
					r.y = i * t_draw_rect.height;
				}
				r.width = t_draw_rect.width;
				r.height = t_draw_rect.height;
				return r;
			}

			/**
			 * Calculate correct value of tile drawing rect.
			 * Tileson gets wrong one, if use tiles with different sizes
			 * @param	&t_rect		- Tileson drawing rect tson::Tile::getDrawingRect()
			 * @param	t_grid_size	- Tileson tile size read from tson::Map class -> tson::Map::getTileSize(), converted to glm::vec2
			 * @return			- Corrected drawing rect
			 */
			static glm::vec4 GetDrawingRectG( tson::Rect t_rect, glm::vec2 t_grid_size) {
				tson::Rect r = GetDrawingRectT( t_rect, t_grid_size );
				glm::vec4 a = glm::vec4( r.x, r.y, r.width, r.height );
				return a;
			}


	}; // class Tool
}; // namespace n2d

#endif
