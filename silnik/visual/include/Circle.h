#ifndef NUDNY_SILNIK_VISUAL_CIRCLE_H
#define NUDNY_SILNIK_VISUAL_CIRCLE_H

#include "Shape.h"

namespace n2d {
	class Circle : public Shape {
		public:
			float 		radius;
			sf::CircleShape	shape;
			b2CircleShape	bound;
			
			Circle();
			Circle( const Circle& );

			b2Shape* 		GetUpdatable();
			sf::Drawable*		GetDrawable();
			sf::Transformable* 	GetTransformable();		
			Shape* 			Clone() const override;
			void 			Draw( sf::RenderWindow& w );
			void 			Draw( sf::RenderWindow& w, sf::Transform& t );
			void 			AddBodyCoords( float x, float y, float rotation );	
			void 			FixToBody();
			void 			SetRadius( float r=20.f );
			void 			SetPosition( float=0.0f, float=0.0f );
			void 			SetPosition( glm::vec2 );
			void 			SetOrigin( float, float );
			void 			SetOrigin( glm::vec2 );
			void 			SetColor( int=255, int=255, int=255, int=255 );
			void 			SetColor( glm::vec4 );
			void 			SetColor( sf::Color );
			void 			SetTexture( int );
			void 			SetTexture( std::string );
			void 			SetTexture( sf::Texture& );
			void 			SetTextureCoords( float=0, float=0, float=0, float=0 );
			void 			SetTextureCoords( glm::vec4 );

			void			Animate( float );
			void			ClearAnimation();
			void			Play();
			void 			Pause();
			void			Stop();
	}; // class Circle
}; // namespace n2d

#endif
