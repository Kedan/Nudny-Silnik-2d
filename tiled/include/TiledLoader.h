#ifndef NUDNY_SILNIK_2D_TILED_LOADER_H
#define NUDNY_SILNIK_2D_TILED_LOADER_H

#include <iostream>
#include <tileson/tileson.h>

namespace nudny {
	class TiledLoader {
		public:
			TiledLoader();
			bool Load( std::string );
		protected:
			tson::Tileson	m_parser;
			TiledMapLoader	m_map_laoder;
	}; // class TiledLoader
}; // namespace nudny

#endif
