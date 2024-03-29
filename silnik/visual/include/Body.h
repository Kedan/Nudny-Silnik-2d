#ifndef NUDNY_SILNIK_VISUAL_BODY_H
#define NUDNY_SILNIK_VISUAL_BODY_H

#include "Shape.h"

namespace n2d {
	/*
	 *
	 * If body is in entity, position is in entity, relative coordinate system
	 *
	 */
	class Body : public Drawable, public Updatable {
		protected:
			std::vector<Shape*>	m_shapes;
			b2Body*			m_body = nullptr;// do not user smart ptr. b2Worl class deletes bodies
		public:
			glm::vec2		position;
			float 			rotation;
			bool			is_ground;
			b2BodyDef		def;

			Body( float x=0.0f, float y = 0.0f, float rotation = 0.0f );
			Body( glm::vec2 position, float rotattion = 0.0f );
			
			void Create( b2World& world );
			void Add( Shape* );
			void Draw( sf::RenderWindow& w );
			void Draw( sf::RenderWindow& w, sf::Transform& t );
			void Update( float );
			

			// !! Setters and Getters can only be used AFTER body.Create( b2World& ) !!
			// !! (Otherwise b2Body* m_body = nullptr -> Segmentation fault) !!
			void SetPosition( float x, float y );
			void SetPosition( glm::vec2 p );
			void SetRotation( float r );

			void Enable(bool=true);
			void Disable();
			bool IsEnable();
			inline b2Body* GetBodyPtr() {
				return m_body;
			}
	}; // class Body
}; // namespace n2d

#endif
