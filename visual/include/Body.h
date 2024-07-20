#ifndef NUDNY_SILNIK_2D_VISUAL_BODY_H
#define NUDNY_SILNIK_2D_VISUAL_BODY_H

#include "Log.h"
#include "Shape.h"

namespace nudny {
	class Body : 
		public Drawable, 
		public Updatable,
		public Creatable,
		public Animated,
		public Transformable,
		public Physical,
		public Visual,
		public Colored
	       	{
		public:
			Body( float x=0.0f, float y = 0.0f, float rotation = 0.0f );
			Body( glm::vec2 position, float rotattion = 0.0f );
			
			int		Add( Shape*, std::string = "" );	
			int 		Add( std::shared_ptr<Shape>, std::string = "" );
			//bool 		Remove( std::Shape* );
			bool 		Remove( int );
			bool 		Remove( std::string );
			void 		Fixture();
			
			void 		Enable(bool=true);
			void 		Disable();
			bool 		IsEnable();
			b2Body* const 	GetPtr() const;

			void 		Draw( sf::RenderWindow& w );
			void 		Draw( sf::RenderWindow& w, sf::Transform& t );
			
			void 		Update( sf::Time& );
			
			void 		Create( b2World& world );
			
			void		Animate( sf::Time& t_dt ); 
			
			void		SetOrigin( float, float);
			void		SetOrigin( glm::vec2 );
			void		SetPosition( float, float );
			void		SetPosition( glm::vec2 );
			void		SetRotation( float);
			void		SetScale( float, float );
			void 		SetScale( glm::vec2 );
			glm::vec2 	GetOrigin();
			glm::vec2	GetPosition();
			float		GetRotation();
			glm::vec2 	GetScale();

			void		SetDirection( glm::vec2 );
			void		SetSpeed( float );
			void		SetVelocity( glm::vec2 );
			void		SetAngularVelocity( float );
			void		SetImpulse( glm::vec2 );
			void		SetMass( float );
			void		Awake( bool );
			glm::vec2 	GetDirection();
			float 		GetSpeed();
			glm::vec2 	GetVelocity();
			float		GetAngularVelocity();
			float		GetMass();

			void		FlipHorizontal();
			void		FlipVertical();
			void		FlipDiagonal();

			void		SetColor( sf::Color& );
			void 		SetColor( int, int, int, int );
			void		SetColor( glm::vec4 );
			void 		SetAlpha( int );
			void 		SetVisible( bool );
			int 		GetAlpha();
			glm::vec4 	GetColor();
			glm::vec4	GetRGBA();
			glm::vec3	GetRGB();
			const sf::Color& GetColorsf();
			
		public:
			glm::vec2		position;
			float 			rotation;
			bool			is_ground;
			b2BodyDef		def;
		protected:
			std::vector<std::shared_ptr<Shape>>		m_shapes;
			std::map<int,b2Fixture*>			m_fixtures;
			std::unordered_multimap<std::string,int>	m_shape_sets;
			b2Body*						m_body = nullptr; // do not use smart pointer!	
			glm::vec2 	m_direction;
			b2MassData	m_mass_data;			
	}; // class Body
}; // namespace n2d

#endif
