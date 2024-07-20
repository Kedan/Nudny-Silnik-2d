#include <TiledLayerLoader.h>

using namespace nudny;

void TiledLayerLoader::PreLoad( tson::Layer& t_layer ) {
	id	= t_layer.getId();
	name 	= t_layer.getName();
	visible = t_layer.isVisible();
	position.x = t_layer.getX() * 16; //mp_tileset->tilesize.x;
	position.y = t_layer.getY() * 16; //mp_tileset->tilesize.y;
}

TiledImageLayerLoader::TiledImageLayerLoader( ImageLayer& t_layer ) {
	mp_layer = &t_layer;
}

bool TiledImageLayerLoader::Load( tson::Layer& t_tson_layer ) {
	bool result = false;
	if( mp_resources && mp_layer ) {
	}
	return result;
}
