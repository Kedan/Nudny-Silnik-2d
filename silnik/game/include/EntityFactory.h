#ifndef NUDNY_ENTITY_FACTORY_H
#define NUDNY_ENTITY_FACTORY_H

#include "Tileset.h"

namespace n2d {
	class EntityFactory {
		public:
			Tileset* 	tileset;
			virtual Entity* Create( tson::Object& ) = 0;
	}; // class EntityFactory
}; // namespace n2d

#endif
