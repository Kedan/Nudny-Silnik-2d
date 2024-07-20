#ifndef NUDNY_SILNIK_2D_VISUAL_RECTANGLE_H
#define NUDNY_SILNIK_2D_VISUAL_RECTANGLE_H

#include <Shape.h>

namespace nudny {
	class Rectangle : public Shape {
		public:
			Rectangle();
			Rectangle( const Rectangle& );

			void		SetSize( float=50.0f, float=50.0f );
			void		SetSize( glm::vec2 );
			glm::vec2 	GetSize();
			float		GetWidth();
			float		GetHeight();
			Rectangle*	CloneStrict() const;
			
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
			sf::RectangleShape	m_shape;
			b2PolygonShape		m_bound;
			sf::Transform		m_transform;
			bool			m_visible = true;
			glm::vec2		m_size = glm::vec2(40.0f,20.0f);
	}; // class
}; // namespace

#endif
