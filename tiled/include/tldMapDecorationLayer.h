#ifndef NUDNY_SILNIK_2D_TILED_MAP_DECORATION_LAYER_H
#define NUDNY_SILNIK_2D_TILED_MAP_DECORATION_LAYER_H

#include <MapDecorationLayer.h>
#include <tldMapLayer.h>

namespace nudny {
	class tldMapDecorationLayer : public MapDecorationLayer, public tldMapLayer {
		public:
			bool Load( tson::Layer&, std::string );
	}; // class
}; // namespace

#endif
