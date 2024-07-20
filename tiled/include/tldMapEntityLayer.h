#ifndef NUDNY_SILNIK_2D_TILED_MAP_ENTITY_LAYER_H
#define NUDNY_SILNIK_2D_TILED_MAP_ENTITY_LAYER_H

#include <MapEntityLayer.h>
#include <tldMapLayer.h>
#include <tldEntityFactory.h>

namespace nudny {
	class tldMapEntityLayer : public MapEntityLayer, public tldMapLayer {
		public:
			bool Load( tson::Layer&, std::string );
		protected:
			std::shared_ptr<tldEntityFactory>	mp_factory;
	}; // class
}; // namespace

#endif
