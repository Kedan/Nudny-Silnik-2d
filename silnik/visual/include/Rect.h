#ifndef NUDNY_SILNIK_VISUAL_RECT_H
#define NUDNY_SILNIK_VISUAL_RECT_H

#include "Shape.h"

namespace n2d {
	class Rect : public Shape {
		public:
			glm::vec2		size;
			sf::RectangleShape 	shape;
			b2PolygonShape		bound;
			
			Rect();
			Rect( const Rect& );
	
			b2Shape* 		GetUpdatable();
			sf::Drawable*		GetDrawable();
			sf::Transformable* 	GetTransformable();
			Shape*			Clone() const override;
			void 			Draw( sf::RenderWindow& w );
			void 			Draw( sf::RenderWindow& w, sf::Transform& t );
			void 			AddBodyCoords( float x, float y, float rotation );	
			void 			FixToBody();				
			void 			SetSize( float=40.0f, float=40.0f );
			void 			SetSize( glm::vec2 ); 
			void 			SetRotation( float=0.0f );
			void 			SetPosition( float=0.0f, float=0.0f );
			void 			SetPosition( glm::vec2 );
			void 			SetOrigin( float=20.0f, float=20.0f );
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
		protected:
			sf::Transform m_transform;
	}; // class Rect
}; // namespace n2d

#endif
