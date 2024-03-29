#include "Map.h"
#include "MapLayer.h"

using namespace n2d;

Map::Map() {
	tileset.SetResources( src );
}

Map::Map( std::string t_file_path ) {
	tileset.SetResources( src );
	m_file_path = t_file_path;
}

bool Map::Load() {
	if( !m_file_path.empty() )
		return Load( m_file_path );
	return false;
}

bool Map::Load( std::string t_file_path ) {
	bool result	= false;
	m_file_path 	= t_file_path;
	std::size_t pos = m_file_path.rfind("/");
	m_dir 		= m_file_path.substr(0,pos);
	m_dir.append("/");
	tson::Tileson 	parser;
	mp_map 		= parser.parse( m_file_path );
	
	if( mp_map->getStatus() == tson::ParseStatus::OK  ) {
		m_grid_size = glm::vec2( mp_map->getTileSize().x, mp_map->getTileSize().y );
		if( LoadAssets() ) {
			LoadLayers();
			result = true;
		}
	} else {
		std::cerr << "n2d::Map::Load - Could not load " << t_file_path << " map!\n";
	}
	return result;
}

bool Map::LoadAssets() {
	LoadImages();
	LoadTilesets();
	return true;
}

bool Map::LoadTilesets() {
	for( auto& t : mp_map->getTilesets() ) {
		tileset.Load( t, m_dir );
		tileset.SetGridSize(m_grid_size);
	}
	return true;
}

bool Map::LoadImages() {
	for( auto& layer : mp_map->getLayers() ) {
		switch( layer.getType() ) {
			case tson::LayerType::ImageLayer: {
				std::string tmp = m_dir;
				tmp.append( layer.getImage() );
				src.LoadTexture( tmp );
			} 
			break;
		}	
		if( !layer.getImage().empty() ) {
 
		}
	}
	return true;
}

bool Map::LoadLayers() {
	for( auto layer : mp_map->getLayers() ) {
		Layer* lyr = mp_layer_factory->Create( layer, mp_entity_factory );
		if( lyr != nullptr ) {
			lyr->position = position;
			lyr->SetResources( src );
			lyr->SetTileset( tileset );
			lyr->SetGrid( m_grid_size );
			lyr->Load( m_dir, layer );
			m_layers.push_back( lyr );
		}
	}
	return true;
}

void Map::Create( b2World& t_world ) {
	for( auto layer : m_layers ) {
		layer->Create( t_world );
	}
}	

void Map::Free() {
	mp_entity_factory = nullptr;
}

void Map::FreeAssets() {
	src.Free();
	tileset.Free();
}

void Map::Draw( sf::RenderWindow& t_window ) {
	for( auto layer : m_layers ) {
		layer->Draw( t_window );
	}
}

void Map::Draw( sf::RenderWindow& t_window, sf::Transform& t_transform ) {
	for( auto layer : m_layers ) {
		layer->Draw( t_window, t_transform );
	}
}

void Map::Update( float t_dt ) {
	//player.Update( t_dt ); 
	for( auto layer : m_layers ) { 
		layer->Update( t_dt );
	}
}

void Map::Events( sf::Event& t_event ) {
	//player.Events( t_event );
	for( auto layer : m_layers ) {
		layer->Events( t_event );
	}
}
