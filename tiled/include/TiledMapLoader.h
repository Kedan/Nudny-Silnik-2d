#ifndef NUDNY_SILNIK_2D_TILED_MAP_LOADER_H
#define NUDNY_SILNIK_2D_TILED_MAP_LOADER_H

#include <iostream>
#include <Map>

namespace nudny {
	class TiledMapLoader {
		public:
			TilesMapLoader( Map& );
			bool Load( std::string );
		protected:
			bool LoadMap();
			bool LoadMapAssets();
		       	bool LoadMapImages();
			bool LoadMapTilesets();	
			tson::Tileson			m_parser; // field passed by reference
			Map*				mp_map;
			std::unique_ptr<tson::Map>	mp_tson_map;
			std::string			m_dir;

	}; // class
}; // namespace 

#endif
