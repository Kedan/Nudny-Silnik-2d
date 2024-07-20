#ifndef NUDNY_SILNIK_2D_VISUAL_POLYGON_H
#define NUDNY_SILNIK_2D_VISUAL_POLYGON_H

#include <Shape.h>

namespace nudny {
	class Polygon : public Shape {
		public:
			Polygon();
			Polygon( std::vector<glm::vec2> );
			Polygon( const Polygon& );
			
			void				Print();

			void				SetVertices( std::vector<glm::vec2>);
			void				TransformVertices();
			void				Reset();
			Polygon*			CloneStrict() const;

			const b2Shape* 			GetUpdatable() const;
			const sf::Drawable*		GetDrawable() const;
			const sf::Transformable* 	GetTransformable() const;		
			Shape*			Clone() const;
			void 			AddBodyCoords( float x, float y, float rotation );	
			void 			FixToBody();
			
			void 			Draw( sf::RenderWindow& t_window );
			void 			Draw( sf::RenderWindow& t_window, sf::Transform& t_transform );
			
			void			SetColor( sf::Color& );	
			void 			SetColor( int, int, int, int );
			void			SetColor( glm::vec4 );
			void 			SetAlpha( int );
			void 			SetVisible( bool );
			int 			GetAlpha();
			glm::vec4 		GetColor();
			glm::vec4		GetRGBA();
			glm::vec3		GetRGB();
			const sf::Color&	GetColorsf();

			void			SetTexture(const sf::Texture* );
			void			SetTextureCoords( glm::vec4 );
			void			SetTextureCoords( const sf::IntRect& );
			void			SetTextureCoords( float, float, float, float );
			const sf::Texture*	GetTexture();
			glm::vec4		GetTextureCoords();
			const sf::IntRect&	GetTextureCoordssf();

			void			SetOrigin( float, float );
			void			SetOrigin( glm::vec2 );
			void			SetPosition( float, float );
			void			SetPosition( glm::vec2 );
			void			SetRotation( float );
			void			SetScale( float, float );
			void			SetScale( glm::vec2 );
			glm::vec2		GetOrigin();
			glm::vec2		GetPosition();
			float			GetRotation();
			glm::vec2 		GetScale();

			void			FlipHorizontal();
			void 			FlipVertical();
			void 			FlipDiagonal();

			void			Animate( sf::Time& );
		protected:
			bool			m_is_fixed_to_body = false;
			sf::ConvexShape		m_shape;
			b2PolygonShape		m_bound;
			sf::Transform		m_transform;
			std::vector<glm::vec2>	m_vertices_transformed;
			std::vector<glm::vec2>	m_vertices;
			std::vector<b2Vec2>	m_b2_vertices;
	};
}; // namespace

#endif
