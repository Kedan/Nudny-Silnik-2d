#include "Map.h"
#include "MapLayer.h"

using namespace n2d;

Map::Map() {
	log.SetFile("./logs/map.log");
	log.Open();
	log.out << "Map constructor. Filepath: " << m_file_path <<" Tileset " << &tileset <<" resources set on " << &src << "\n";
	tileset.SetResources( src );
	log.Flush();
}

Map::Map( std::string t_file_path ) {
	tileset.SetResources( src );
	m_file_path = t_file_path;
	log.SetFile("./logs/map.log");
	log.Open();
	log.out << "Map constructor. Filepath: " << m_file_path.c_str() <<" Tileset " << &tileset <<" resources set on " << &src << "\n";
	log.Flush();
}

Map::~Map() {
	log.Close();
	log.Flush();
}

bool Map::Load() {
	log.Time();
	log.out << "Map Load - begin\n";
	if( !m_file_path.empty() ) {
		log.out << "\t...filepath empty - nothing to load.\n";
		return Load( m_file_path );
	}
	log.Time();
	log.out << "Map Load - end\n";
	log.Flush();
	return false;
}

bool Map::Load( std::string t_file_path ) {
	log.Time();
	log.out << "Map Load - begin\n";
	bool result	= false;
	m_file_path 	= t_file_path;
	std::size_t pos = m_file_path.rfind("/");
	m_dir 		= m_file_path.substr(0,pos);
	m_dir.append("/");
	tson::Tileson 	parser;
	mp_map 		= parser.parse( m_file_path );
	
	if( mp_map->getStatus() == tson::ParseStatus::OK  ) {
		log.out << "\tMap json parse OK. ";
		m_grid_size = glm::vec2( mp_map->getTileSize().x, mp_map->getTileSize().y );
		log.out << "Grid size: ["<<m_grid_size.x<<","<<m_grid_size.y<<"]\n";
		if( LoadAssets() ) {
			LoadLayers();
			result = true;
		}
	} else {
		log.out << "n2d::Map::Load - Could not load " << t_file_path << " map!";
	}
	log.Time();
	log.out << "Map Load - end\n";
	log.Flush();
	return result;
}

bool Map::LoadAssets() {
	log.Time();
	log.out << "Map Load Assets - begin\n";
	LoadImages();
	LoadTilesets();
	log.Time();
	log.out << "Map Load Assets - end\n";
	return true;
}

bool Map::LoadTilesets() {
	log.Time();
	log.out << "Map Load Tilesets - begin\n";
	for( auto& t : mp_map->getTilesets() ) {
		tileset.SetGridSize(m_grid_size);
		tileset.Load( t, m_dir );
		log.out << "\tTileset " << t.getName() << " loaded\n";
	}
	log.Time();
	log.out << "Map Load Tileset - end\n";
	log.Flush();
	return true;
}

bool Map::LoadImages() {
	log.Time();
	log.out << "Map Load Images - begin\n";
	for( auto& layer : mp_map->getLayers() ) {
		switch( layer.getType() ) {
			case tson::LayerType::ImageLayer: {
				std::string tmp = m_dir;
				tmp.append( layer.getImage() );
				src.LoadTexture( tmp );
				log.out << "\t Layer: " << layer.getName() << "\tload image: " << tmp << "\n";
			} 
			break;
		}	
	}
	log.Time();
	log.out << "Map Load Image - end\n";
	log.Flush();
	return true;
}

bool Map::LoadLayers() {
	log.Time();
	log.out << "Map Load Layers - begin\n";
	log.out << "INFO:\n" 
		<< "\tBlad jest tutaj. do warstwy jest przekazywana referencja do tilesetu, ale przeciez tilesetow moze byc kilka!\n"
		<< "\tNie - nie jest tak. Bo wszystkie tson::Tilesety z mapy, ladowane sa do JEDNEGO n2d::Tilesetu !\n"
		<< "\tWiec ewidentnie problem jest z pobieraniem referencji do tekstury sprajta.\n";
	for( auto layer : mp_map->getLayers() ) {
		Layer* lyr = mp_layer_factory->Create( layer, mp_entity_factory );
		if( lyr != nullptr ) {
			lyr->position = position;
			lyr->SetResources( src );
			lyr->SetTileset( tileset );
			lyr->SetGrid( m_grid_size );
			lyr->Load( m_dir, layer );
			m_layers.push_back( lyr );
			log.out << "\tpos: ["<<position.x<<","<<position.y<<"] src: " << &src <<" tileset: "<< &tileset << " grid: ["<<m_grid_size.x<<","<<m_grid_size.y<<"] Layer: " << layer.getName() << "\n";
		}
	}
	log.Time();
	log.out << "Map Load Layers - end\n";
	log.Flush();
	return true;
}

void Map::Create( b2World& t_world ) {
	log.Time();
	log.out << "Map Create world=" << &t_world << "\n";
	for( auto layer : m_layers ) {
		layer->Create( t_world );
	}
	log.Flush();
}	

void Map::Free() {
	mp_entity_factory = nullptr;
}

void Map::FreeAssets() {
	log.Time();
	log.out << "Map Free assets\n";
	src.Free();
	tileset.Free();
	log.Flush();
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
