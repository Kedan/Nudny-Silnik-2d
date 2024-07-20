#ifndef NUDNY_SILNIK_2D_TILED_WORLD_H
#define NUDNY_SILNIK_2D_TILED_WORLD_H

#include <tileson/tileson.h>
#include <World.h>

namespace nudny {
	class tldWorld : public World {
		public:
			bool Load( std::string );
	}; // class
}; // namespace

#endif
