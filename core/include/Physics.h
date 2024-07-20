#ifndef NUNDY_SILNIK_2D_CORE_PHYSICS_H
#define NUNDY_SILNIK_2D_CORE_PHYSICS_H

#include <Interfaces.h>

namespace nudny {
	class Physics { 
		public:
			Physics();
			virtual void Create( Body& ) = 0;
			virtual void Step() = 0;
			virtual void SetGravity( float, float );
			virtual void SetGravity( const glm::vec2& );
			virtual glm::vec2 GetGravity();
	}; // class
}; // namespace

#endif
