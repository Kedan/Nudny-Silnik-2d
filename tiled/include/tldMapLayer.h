#ifndef NUDNY_SILNIK_2D_TILED_MAP_LAYER_H
#define NUDNY_SILNIK_2D_TILED_MAP_LAYER_H

#include <tileson/tileson.h>

namespace nudny {
	class tldMapLayer {
		public:
			virtual bool Load( tson::Layer&, std::string ) = 0;
		protected:
			tson::Layer m_layer;
	}; // class
}; // namespace

#endif
