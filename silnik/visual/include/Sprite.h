#ifndef NUDNY_SILNIK_VISUAL_SPRITE_H
#define NUDNY_SILNIK_VISUAL_SPRITE_H

#include "Poly.h"

namespace n2d {
	class Sprite : public Poly {
		protected:
			glm::vec2 				m_size; 
			sf::Sprite 				sprite;
		//	float					m_current_frame_index = 0;
		//	std::vector<std::pair<float,glm::vec4>> m_frames;
		//	bool					m_pause;
		//	bool					m_play;
		//	float					m_elapsed_time;
		public:
	//		bool	loop = false;
	//		float	animation_speed = 1.0f;

			//std::vector<SpriteAnimation>	animations;	
			SpriteAnimation	animation;

			int 	GID;
			Sprite();
			Sprite(int);	
			Sprite( const Sprite& );
		
			void 			SetTexture( int );
			void 			SetTexture( std::string );
			void 			SetTexture( sf::Texture& );
			void 			SetTextureCoords( float=0, float=0, float=0, float=0 );
			void 			SetTextureCoords( glm::vec4 );	
			sf::Drawable*		GetDrawable();
			sf::Transformable* 	GetTransformable();
			//b2Shape* 		GetUpdatable();
			Shape*			Clone() const override;
			void 			Draw( sf::RenderWindow& w );
			void 			Draw( sf::RenderWindow& w, sf::Transform& t );
			void 			AddBodyCoords( float x, float y, float rotation );	
			void 			SetRotation( float=0.0f );
			void 			SetPosition( float=0.0f, float=0.0f );
			void 			SetPosition( glm::vec2 );
			void 			SetColor( int=255, int=255, int=255, int=255 );
			void 			SetColor( glm::vec4 );
			void 			SetColor( sf::Color );
			void 			SetSize( float, float );
		//	void 			FixToBody();				
		//	void 			SetRotation( float=0.0f );
		//	void 			SetPosition( float=0.0f, float=0.0f );
		//	void 			SetPosition( glm::vec2 );
			void 			SetOrigin( float, float );
			void 			SetOrigin( glm::vec2 );
			glm::vec2		GetSize();

			void			FlipHorizontal();
			void			FlipVertical();
			void 			FlipDiagonal();

			bool			IsAnimated();
			void			Animate( float );
			void			ClearAnimation();
			void			Play();
			void 			Pause();
			void			Stop();
			
		//	bool			IsAnimated();
		//	void			Animate( float );
		//	void			ClearAnimation();
		//	void			AddFrame( float, glm::vec4 );
		//	void		 	Play();
		//	void		 	Pause();
		//	void		 	Stop();
	};
}; // namespace n2d

#endif
