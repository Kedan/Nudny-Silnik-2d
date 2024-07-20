#ifndef NUDNY_SILNIK_2D_GAME_ENTITY_FACTORY_H
#define NUDNY_SILNIK_2D_GAME_ENTITY_FACTORY_H

#include <Entity.h>

namespace nudny {
	class EntityFactory {
		public:
			virtual std::shared_ptr<Entity> Create() = 0;
	}; // class EntityFactory
}; // namespace n2d

#endif
