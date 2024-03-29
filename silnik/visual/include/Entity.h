#ifndef NUDNY_SILNIK_VISUAL_ENTITY_H
#define NUDNY_SILNIK_VISUAL_ENTITY_H

#include "Text.h"
#include "Body.h"

namespace n2d {
	// i.e. Layer or Map can be in Entity family?
	class Entity : public Drawable, public Updatable, public Interactive {
		public:
			int			id;
			std::string		name;
			glm::vec2		position;
			float			rotation;
			
			//std::vector<Shape*>	shapes;
			std::vector<Body*> 	bodies;
			Text			text;
			bool			show_text = false;
			
			Entity();
			//int Add( Shape* );
			int Add( Body* );
			void Draw( sf::RenderWindow& w );
			void Draw( sf::RenderWindow& w, sf::Transform& t );
			void Update( float );
			void Events( sf::Event& );

			void Create( b2World& world );
			
			//void FlipHorizontally();
			//void FlipVerically();
			//void SetPosition( float, float );
			//void SetPosition( glm::vec2 );
			void SetRotation( float );
			void SetVelocity( float, float );
			void SetType( b2BodyType );
			//void SetVelocity( glm::vec2 ); 
			//void SetAngularVelocity( float );
			//void SetAcceleration( float, float );
			//void SetAcceleration( glm::vec2 );
			//void SetAngularAcceleration( float );
			//void Enable( bool );
			//void Disable();
			//void SetColor( float, float, float, float );
			//void SetColor( glm::vec4 );
			//void SetAlpha( float );
		protected:
			void LoadText( tson::Object& );
			void LoadTemplate( tson::Object& );
	}; // class Entity
}; // namespace n2d

#endif
