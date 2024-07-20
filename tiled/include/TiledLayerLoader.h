#ifndef NUDNY_SILNIK_2D_TILED_LAYER_LOADER_H
#define NUDNY_SILNIK_2D_TILED_LAYER_LOADER_H

#include <tileson/tileson.h>

namespace nudny {
	class TiledLayerLoader {
		public:
			virtual bool	Load( tson::Layer& t_tson_layer ) = 0;
			void		SetResources( Resources& t_resources ) {
				mp_resources = &t_resources;
			}
		protected:
			void	PreLoad( tson::Layer& );
			Resources*	mp_resources;	// passed by reference
	}; // class 

	class TiledImageLayerLoader : public TiledLayerLoader {
		public:
			TiledImageLayerLoader( ImageLayer& t_layer );
			bool Load( tson::Layer& t_tson_layer );
		protected:
			ImageLayer* mp_layer; // passed by reference
	}; // class
}; // namespace nudny

#endif
