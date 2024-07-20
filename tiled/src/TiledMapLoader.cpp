#include <Converter.h>
#include <TiledMapLoader.h>

using namespace nudny;

TiledMapLoader( Map& t_map ) {
	mp_map = t_map;
}

bool TiledMapLoader::Load(  std::string t_filename ) {
	bool result = false;
	if( m_parser ) {
		std::string	path	= t_filename;
		std::size_t	tmp	= path.rfind("/");
		std::string	m_dir	= path.substr(0,tmp);
		mp_tson_map = m_parser->parse( path );
		if( mp_tson_map->getStatus() == tson::ParseStatus::OK ) {
			result = LoadMap();
		}
	}
	return result;
}

bool TiledMapLoader::LoadMap() {
	m_map.SetGridSize( Converter::TSON_TO_GLM().Vec2( mp_tson_map->getTileSize() ));
	if( LoadMapAssets( m_map )) {
		//result = TiledUtils::LoadMapLayers( m_map,  mp_tson_map , m_dir );
	}
};

bool TiledMapLoader::LoadMapAssets() {
	return LoadMapImages() && LoadMapTilesets();
}

bool TiledMapLoader::LoadMapImages() {
	return false;
}

bool TiledMapLoader::LoadMapTilesets() {
	return false;
}
