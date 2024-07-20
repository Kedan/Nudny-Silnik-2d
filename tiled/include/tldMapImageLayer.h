#ifndef NUDNY_SILNIK_2D_TILES_MAP_IMAGE_LAYER_H
#define NUDNY_SILNIK_2D_TILES_MAP_IMAGE_LAYER_H

#include <tldMapLayer.h>
#include <Resources.h>
#include <MapImageLayer.h>

namespace nudny {
	class tldMapImageLayer : 
		public MapImageLayer, 
		public tldMapLayer
       	{
		public:
			bool Load( tson::Layer&, std::string );
	}; // class 
}; // namespace

#endif
