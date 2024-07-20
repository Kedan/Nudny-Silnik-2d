#ifndef NUDNY_SILNIK_2D_VISUAL_SHAPE_H
#define NUDNY_SILNIK_2D_VISUAL_SHAPE_H

#include <iostream>
#include <vector>
#include <list>
#include <memory>
#include <glm/glm.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "box2d/box2d.h"
#include "Interfaces.h"
#include "Resources.h"

namespace nudny {
	class Shape : 
		public Drawable,
	       	public Colored,
		public Textured,
		public Transformable,
		public Visual,
		public Animated 
	{
		public:
			Shape(){}
			Shape( b2FixtureDef& );
			~Shape(){}
			
			void SetSensor( bool );
			bool IsSensor();

			inline void SetDensity( float t_density=1.0f ) {
				fixture.density = t_density;
			}
			inline void SetRestitution( float t_restitution=0.01f ) {
				fixture.restitution = t_restitution;
			}
			inline void SetFriction( float t_friction=0.3f ) {
				fixture.friction = t_friction;
			}
			
			virtual const b2Shape*	 		GetUpdatable() const			= 0;
			virtual const sf::Drawable*		GetDrawable() const			= 0;
			virtual const sf::Transformable* 	GetTransformable() const 		= 0;
			virtual Shape*				Clone() const 				= 0;
			virtual void 				AddBodyCoords( float, float, float ) 	= 0;
			virtual void				FixToBody() 				= 0;
		public:
			b2FixtureDef			fixture;
			bool				collide = true;
		protected:
			std::shared_ptr<b2Fixture>	mp_fixture;
			glm::vec2			m_origin;
			glm::vec2			m_position = glm::vec2(0,0);
			float				m_rotation = 0;
			glm::vec2			m_scale = glm::vec2( 1,1);
			glm::vec4			m_tex_coords;
			glm::vec4			m_color;
			const sf::Texture*		mp_texture = nullptr;

	}; // class Shape
}; // namespace nudny 

#endif
