#ifndef NUDNY_SILNIK_2D_CORE_INTERFACES_H
#define NUDNY_SILNIK_2D_CORE_INTERFACES_H

#include <chrono>
#include <iostream>
#include <sstream>
#include <glm/glm.hpp>
#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>

namespace nudny {
	class Drawable {
		public:
			virtual void Draw( sf::RenderWindow& t_window ) = 0;
			virtual void Draw( sf::RenderWindow& t_window, sf::Transform& t_transform ) = 0;
	};

	class Updatable{
		public:
			virtual void Update( sf::Time& ) = 0;
	};
	
	class Creatable {
		public:
			virtual void Create( b2World& t_world ) = 0;
	};
	
	class Colored {
		public:
			virtual void		SetColor( sf::Color& ) 		= 0;
			virtual void 		SetColor( int, int, int, int ) 	= 0;
			virtual	void		SetColor( glm::vec4 )		= 0;
			virtual void 		SetAlpha( int ) 		= 0;
			virtual void 		SetVisible( bool ) 		= 0;
			virtual int 		GetAlpha() 			= 0;
			virtual glm::vec4 	GetColor() 			= 0;
			virtual glm::vec4	GetRGBA() 			= 0;
			virtual glm::vec3	GetRGB()			= 0;
			virtual const sf::Color&	GetColorsf()		= 0;
	};

	class Textured {
		public:
			virtual void			SetTexture( const sf::Texture* ) 		= 0;
			virtual void			SetTextureCoords( glm::vec4 )			= 0;
			virtual void			SetTextureCoords( const sf::IntRect& )		= 0;
			virtual void			SetTextureCoords( float, float, float, float )	= 0;
			virtual const sf::Texture*	GetTexture() 					= 0;
			virtual glm::vec4		GetTextureCoords()				= 0;
			virtual const sf::IntRect&	GetTextureCoordssf()				= 0;
	};

	class Shaded {
		//using shaders
	};

	class Transformable {
		public:
			virtual void		SetOrigin( float, float)	= 0;
			virtual void		SetOrigin( glm::vec2 )		= 0;
			virtual void		SetPosition( float, float ) 	= 0;
			virtual void		SetPosition( glm::vec2 ) 	= 0;
			virtual void		SetRotation( float)		= 0;
			virtual void		SetScale( float, float ) 	= 0;
			virtual void 		SetScale( glm::vec2 )		= 0;
			virtual glm::vec2 	GetOrigin()			= 0;
			virtual glm::vec2	GetPosition()			= 0;
			virtual float		GetRotation()			= 0;
			virtual glm::vec2 	GetScale()			= 0;
	};

	class Visual {
		public:
			virtual void FlipHorizontal() = 0;
			virtual void FlipVertical() = 0;
			virtual void FlipDiagonal() = 0;
	};
	
	class Physical {
		public:
			virtual void SetDirection( glm::vec2 ) 		= 0;
			virtual void SetSpeed( float ) 			= 0;
			virtual void SetVelocity( glm::vec2 ) 		= 0;
			virtual void SetAngularVelocity( float ) 	= 0;
			virtual void SetImpulse( glm::vec2 ) 		= 0;
			virtual void SetMass( float ) 			= 0;
			//virtual void SetFriction( float ) 		= 0;
			//virtual void SetDensity( float ) 		= 0;
			//virtual void SetRestitution( float ) 		= 0;
			virtual void Awake( bool ) 			= 0;

			virtual glm::vec2 	GetDirection() 		= 0;
			virtual float 		GetSpeed() 		= 0;
			virtual glm::vec2 	GetVelocity() 		= 0;
			virtual float		GetAngularVelocity() 	= 0;
			virtual float		GetMass() 		= 0;
			//virtual float		GetFriction() 		= 0;
			//virtual float		GetDensity() 		= 0;
			//virtual float		GetRestitution() 	= 0;
	};

	class Playable {
		public:
			virtual void Play() 	= 0;
			virtual void Pause() 	= 0;
			virtual void Stop() 	= 0;
			virtual void Loop(bool) = 0;

			virtual bool IsPaused() 	= 0;
			virtual bool IsPlaying() 	= 0;
			virtual bool IsLooped() 	= 0;
	};
	
	class Audible {
		public:
			virtual void SetVolume() 		= 0;
			virtual void SetAttenuation( float ) 	= 0;
		       	
			virtual float GetVolume() 		= 0;
			virtual float GetAttenuation() 		= 0;	
	};
	
	class Animated {
		public:
			virtual void Animate( sf::Time& t_dt ) 	= 0; 
	};

	class Interactive {
		public:
			virtual void Events( sf::Event& ) 	= 0;
	};
}; // namespace

#endif
