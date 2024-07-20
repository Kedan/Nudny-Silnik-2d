#ifndef NUDNY_SILNIK_2D_TILED_MAP_H
#define NUDNY_SILNIK_2D_TILED_MAP_H

#include <Map.h>

namespace nudny {
	class tldMap : public Map {
		public:
			bool Load( std::string ); 
	}; // class
}; // namespace

#endif
