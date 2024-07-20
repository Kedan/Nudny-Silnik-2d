#ifndef NUDNY_SILNIK_2D_TILED_MAP_TILE_LAYER_H
#define NUDNY_SILNIK_2D_TILED_MAP_TILE_LAYER_H

#include <MapTileLayer.h>
#include <tldMapLayer.h>

namespace nudny {
	class tldMapTileLayer : 
		public MapTileLayer, 
		public tldMapLayer 
	{
		public:
			bool Load( tson::Layer&, std::string );
	}; // class
}; // namespace

#endif
