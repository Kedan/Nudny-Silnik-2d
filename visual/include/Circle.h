#ifndef NUDNY_SILNIK_2D_VISUAL_CIRCLE_H
#define NUDNY_SILNIK_2D_VISUAL_CIRCLE_H

#include <Shape.h>

namespace nudny {
	class Circle : public Shape {
		public:	
			Circle();
			Circle( const Circle& );
			
			void			SetRadius( const float& t_radius=20.0f );
			float			GetRadius();
			Circle*			CloneStrict() const;
			Shape*			Clone() const;

			const b2Shape* 			GetUpdatable() const;
			const sf::Drawable*		GetDrawable() const;
			const sf::Transformable* 	GetTransformable() const;		
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
			sf::CircleShape		m_shape;
			b2CircleShape		m_bound;
			float 			m_radius;	
	}; // class Circle
}; // namespace n2d

#endif
