#ifndef NUDNY_SILNIK_2D_UTILS_TOOL_H
#define NUDNY_SILNIK_2D_UTILS_TOOL_H

#include <chrono>
#include <iostream>
#include <sstream>
#include <glm/glm.hpp>
#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>
#include <tileson/tileson.h>

namespace nudny {
	const float PIXEL_TO_BOX2D = 0.01f;
	const float BOX2D_TO_PIXEL = 100.0f;
	
	
	std::vector<glm::vec2>	FlipVerticesHorizontal( std::vector<glm::vec2>, float );
	std::vector<glm::vec2>	FlipVerticesVertical( std::vector<glm::vec2>, float );	
	std::vector<glm::vec2>	FlipVerticesDiagonal( std::vector<glm::vec2>, glm::vec2  );
	class Tool {
		public:
			static b2Vec2 g2b( glm::vec2 v, float s = PIXEL_TO_BOX2D ) { 
				return b2Vec2( v.x*s, v.y*s );
			}
			static b2Vec2 s2b( sf::Vector2f v, float s = PIXEL_TO_BOX2D ) {
				return b2Vec2( v.x*s, v.y*s );
			}
			static glm::vec2 b2g( b2Vec2 v, float s = BOX2D_TO_PIXEL ) {
				return glm::vec2( v.x*s, v.y*s );
			}
			static glm::vec2 s2g( sf::Vector2f v ) {
				return glm::vec2( v.x, v.y );
			}
			static sf::Vector2f g2s( glm::vec2 v ) {
				return sf::Vector2f( v.x, v.y );
			}
			static sf::Vector2f b2s( b2Vec2 v ) {
				return sf::Vector2f( v.x*BOX2D_TO_PIXEL, v.y*BOX2D_TO_PIXEL );
			}
			static float rad( float deg ) {
				return deg *  (3.1415f/180.0f);
			}
			static float ang( float rad ) {	
				return rad * 180.f / 3.1415f;
			}
			static inline float Bf( float val ) {
				return val * PIXEL_TO_BOX2D;
			}
			static inline float Bs( float val ) {
				return val * BOX2D_TO_PIXEL;
			}
			static glm::vec4 ConvertTsonToGlm( const tson::Rect& t_rect ) {
				return glm::vec4( t_rect.x, t_rect.y, t_rect.width, t_rect.height );
			}
			static sf::IntRect ConvertTsonToSfml( const tson::Rect& t_rect ) {
				return sf::IntRect( t_rect.x, t_rect.y, t_rect.width, t_rect.height );
			}
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
			static inline std::vector<glm::vec2> Translate( std::vector<glm::vec2> t_v, glm::vec2 t_translation  ) {				
				std::vector<glm::vec2> rv;
				for( auto w : t_v ) {
					rv.push_back(w+t_translation);
				}
				return rv;
			}
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
			static std::string GetCurrentDatetime() {
				auto now = std::chrono::system_clock::now();
   				auto in_time_t = std::chrono::system_clock::to_time_t(now);
    				std::stringstream ss;
    				ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X");
    				return ss.str();
			}
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
			static glm::vec4 GetDrawingRectG( tson::Rect t_rect, glm::vec2 t_grid_size) {
				tson::Rect r = GetDrawingRectT( t_rect, t_grid_size );
				glm::vec4 a = glm::vec4( r.x, r.y, r.width, r.height );
				return a;
			}


	}; // class Tool
}; // namespace nudny

#endif
