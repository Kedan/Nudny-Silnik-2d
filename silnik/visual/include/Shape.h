#ifndef NUDNY_SILNIK_VISUAL_SHAPE_H
#define NUDNY_SILNIK_VISUAL_SHAPE_H

#include <iostream>
#include <vector>
#include <list>
#include <memory>
#include <glm/glm.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "box2d/box2d.h"
#include "Interfaces.h"
#include "Resources.h"
#include "Animation.h"

namespace n2d {
	class Shape : public Drawable, public Animated {
		protected:
			Resources*			mp_resources;
		public:
			bool				collide = true;
			sf::Texture			texture;
			b2FixtureDef			fixture;
			glm::vec2			origin;
			glm::vec2			position = glm::vec2(0,0);
			float				rotation = 0;
			int				texture_id;
			glm::vec4			tex_coords;
			glm::vec4			color;

			void SetDensity( float=1.0f );
			void SetRestitution( float=0.01f );
			void SetFriction( float=0.3f );

			void inline			SetResources( Resources& t_resources ) {
				mp_resources = &t_resources;
			}

			virtual b2Shape* 		GetUpdatable() 						= 0;
			virtual sf::Drawable*		GetDrawable() 						= 0;
			virtual sf::Transformable* 	GetTransformable() 					= 0;
			virtual Shape* 			Clone() const 						= 0;
			virtual void 			AddBodyCoords( float, float, float ) 			= 0;
			virtual void			FixToBody() 						= 0;
			virtual void 			SetPosition( float=0.0f, float=0.0f ) 			= 0;
			virtual void			SetPosition( glm::vec2 ) 				= 0;
			virtual void			SetOrigin( float, float ) 				= 0;
			virtual void			SetOrigin( glm::vec2 ) 					= 0;
			virtual void			SetColor( int=255, int=255, int=255, int=255 ) 		= 0;
			virtual void			SetColor( glm::vec4 ) 					= 0;
			virtual void			SetColor( sf::Color ) 					= 0;
			virtual void			SetTexture( int ) 					= 0;
			virtual void			SetTexture( std::string )				= 0;
			virtual void			SetTexture( sf::Texture& )				= 0;
			virtual void			SetTextureCoords( float=0, float=0, float=0, float=0 ) 	= 0;
			virtual void			SetTextureCoords( glm::vec4 ) 				= 0;
	};
}; // namespace n2d 

#endif
