#ifndef NUDNY_SILNIK_VISUAL_POLY_H
#define NUDNY_SILNIK_VISUAL_POLY_H

#include "Shape.h"

namespace n2d {
	class Poly : public Shape {
		public:
			std::vector<glm::vec2>	vertices;
			sf::ConvexShape		shape;
			b2PolygonShape		bound;
			
			Poly(){};
			Poly( std::vector<glm::vec2> );
			Poly( const Poly& );

			b2Shape* 		GetUpdatable();
			sf::Drawable*		GetDrawable();
			sf::Transformable* 	GetTransformable();
			Shape*			Clone() const override;
			void 			Draw( sf::RenderWindow& w );
			void 			Draw( sf::RenderWindow& w, sf::Transform& t );
			void 			AddBodyCoords( float x, float y, float rotation );	
			void 			FixToBody();				
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
			void			SetVertices( std::vector<glm::vec2> vertices );
			void			TransformVertices();
			void 			Reset();
			void			Animate( float );
			void			ClearAnimation();
			void			Play();
			void 			Pause();
			void			Stop();
		protected:
			sf::Transform m_transform;
			std::vector<glm::vec2>	m_vertices;
			std::vector<b2Vec2>	b2_vertices;
	};
}; // namespace n2d

#endif
