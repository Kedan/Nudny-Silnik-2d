#ifndef NUDNY_SILNIK_2D_VISUAL_SPRITE_H
#define NUDNY_SILNIK_2D_VISUAL_SPRITE_H

#include <Animation.h>
#include <Polygon.h>

namespace nudny {
	class Sprite : 
		public Polygon,
		public Playable
	{
		public:
			Sprite( int = 0 );
			Sprite( const sf::Texture&, int = 0 );
			Sprite( const sf::Texture*, int = 0 );	
			Sprite( const Sprite& );
			
			void				Print();
			
			void				InitAnimation();	
			void				ShowCollisionShape( bool );
			int				GetGid();
			//const	std::unique_ptr<SpriteAnimation>& 	GetAnimation() const;
			const	sf::Sprite& 		GetSprite() const;
			void				SetSize(float,float);
			void				SetSize( glm::vec2 );
			glm::vec2			GetSize();
			Sprite*				CloneStrict();
			Shape*				Clone();
			void 				SetTexture( const sf::Texture& );

			//const b2Shape* 			GetUpdatable() const;
			const sf::Drawable*		GetDrawable() const;
			const sf::Transformable* 	GetTransformable() const;		
			void 				AddBodyCoords( float x, float y, float rotation ); // ?
			//void 				FixToBody();
			
			void 				Draw( sf::RenderWindow& t_window );
			void 				Draw( sf::RenderWindow& t_window, sf::Transform& t_transform );
			
			void				SetColor( sf::Color& );	
			void 				SetColor( int, int, int, int );
			void				SetColor( glm::vec4 );
			void 				SetAlpha( int );
			void 				SetVisible( bool );
			int 				GetAlpha();
			glm::vec4 			GetColor();
			glm::vec4			GetRGBA();
			glm::vec3			GetRGB();
			const sf::Color&		GetColorsf();

			void				SetTexture(const sf::Texture* );
			void				SetTextureCoords( void );
			void				SetTextureCoords( glm::vec4 );
			void				SetTextureCoords( const sf::IntRect& );
			void				SetTextureCoords( float, float, float, float );
			const sf::Texture*		GetTexture();
			glm::vec4			GetTextureCoords();
			const sf::IntRect&		GetTextureCoordssf();

			void				SetOrigin( float, float );
			void				SetOrigin( glm::vec2 );
			void				SetPosition( float, float );
			void				SetPosition( glm::vec2 );
			void				SetRotation( float );
			void				SetScale( float, float );
			void				SetScale( glm::vec2 );
			glm::vec2			GetOrigin();
			glm::vec2			GetPosition();
			float				GetRotation();
			glm::vec2 			GetScale();

			void				FlipHorizontal();
			void 				FlipVertical();
			void 				FlipDiagonal();

			inline void			SomeSpriteMethod() {
				std::cout << "Me lajki, lajki!\n";
			}

			void 	Play();
			void 	Pause();
			void 	Stop();
			void 	Loop( bool );
			bool	IsPaused();
			bool	IsPlaying();
			bool	IsLooped();
			void	Animate( sf::Time& );
		protected:
			int		m_gid;
			bool		m_show_collision_shape	= false;
			glm::vec2	m_size;
			sf::Sprite	m_sprite;
			
		public:
			std::unique_ptr<SpriteAnimation>	animation;
			//SpriteAnimation	animation;	
	}; // class Sprite
}; // namespace nudny

#endif
