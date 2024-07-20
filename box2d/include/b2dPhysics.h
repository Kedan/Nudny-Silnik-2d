#ifndef NUDNY_SILNIK_2D_BOX2D _PHYSICS_H
#define NUDNY_SILNIK_2D_BOX2D_PHYSICS_H

#include <Physics.h>

namespace nudny {
	class b2dPhysics : public Physics {
		public:
			b2dPhysics();
			b2dPhysics( float, float );
			b2dPhysics( glm::vec2 );
			~b2dPhysics();

			void 		Step();
			void 		SetGravity( float, float );
			void 		SetGravity( glm::vec2 );
			glm::vec2 	GetGravity();

			b2World		world = b2World( b2Vec2( 0, -10.0f ));
		protected:
			void		Init();

			float		m_time_step = 1 / 60.0f;
			int		m_sub_step_count = 4;
			

	}; // class b2dPhysics
}; // namespace nudny 

#endif
