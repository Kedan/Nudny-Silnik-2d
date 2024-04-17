#include "Map.h"
#include "MapLayer.h"

using namespace n2d;

Map::Map() {
	LOG.Time() << "Map constructor. Filepath: " << m_file_path <<" Tileset " << &tileset <<" resources set on " << &src << "\n";
	tileset.SetResources( src );
}

Map::Map( std::string t_file_path ) {
	tileset.SetResources( src );
	m_file_path = t_file_path;
	LOG.Time() << "Map constructor. Filepath: " << m_file_path <<" Tileset " << &tileset <<" resources set on " << &src << "\n";
}

Map::~Map() {
	Free();
	LOG.Time() << "Map destrucor\n";  
}

bool Map::Load() {
	LOG.Time() << "Map Load - begin\n";
	bool result = false;
	if( !m_file_path.empty() ) {
		result = Load( m_file_path );
	} else {
		LOG << "\t\t map file_path empty. Nothing to load.\n";
	}
	LOG.Time() << "Map Load - end("<< (result ? "ok" : "failed" ) <<")\n";
	return result;
}

bool Map::Load( std::string t_file_path ) {
	LOG.Time() << "Map Load(" << t_file_path <<") - begin\n";
	bool result			= false;
	m_file_path 			= t_file_path;
	std::size_t pos 		= m_file_path.rfind("/");
	m_dir 				= m_file_path.substr(0,pos);
	m_dir.append("/");
	tson::Tileson 	parser;
	mp_map 		= parser.parse( m_file_path );

	if( mp_map->getStatus() == tson::ParseStatus::OK  ) {
		LOG.Time() << "Map json parse OK. Grid size: ["<<m_grid_size.x<<","<<m_grid_size.y<<"]\n";
		m_grid_size = glm::vec2( mp_map->getTileSize().x, mp_map->getTileSize().y );
		if( LoadAssets() ) {
			result = LoadLayers();
		}
	} else {
		LOG.Time() << "ERROR - Map Load: Could not parse json file: \'" << t_file_path << "\'\n";
	}
	LOG.Time() << "Map Load - end("<< ( result ? "ok" : "failed" )<<")\n";
	return result;
}

bool Map::LoadAssets() {
	bool result 	= false;
	bool result_img = false;
	bool result_ts	= false;
	bool result_audio = false;
	LOG.Time() << "Map Load Assets - begin\n";
	result_img 	= LoadImages();
	result_ts 	= LoadTilesets();
	result_audio	= LoadAudio();
	result = result_img && result_ts;
	LOG.Time() << "Map Load Assets - end("<< (result ? "ok" : "failed") <<")\n";
	return result;
}

bool Map::LoadTilesets() {
	bool result = false;
	LOG.Time() << "Map Load Tilesets("<< mp_map->getTilesets().size() <<") - begin\n";
	for( auto& t : mp_map->getTilesets() ) {
		tileset.SetGridSize(m_grid_size);
		result = tileset.Load( t, m_dir );
	}
	LOG.Time() << "Map Load Tileset - end("<<(result?"ok":"failed")<<")\n";
	return result;
}

bool Map::LoadImages() {
	LOG.Time() << "Map Load Images - begin\n";
	for( auto& layer : mp_map->getLayers() ) {
		switch( layer.getType() ) {
			case tson::LayerType::ImageLayer: {
				std::string tmp = m_dir;
				tmp.append( layer.getImage() );
				src.textures.Load( tmp );
			} 
			break;
		}	
	}
	LOG.Time() << "Map Load Image - end\n";
	return true;
}

bool Map::LoadLayers() {
	LOG.Time() << "Map Load Layers\n";
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
	LOG.Time() << "Map Load Layers - end\n";
	return true;
}

bool Map::LoadAudio() {
	LOG.Time() << "Map Load Audio\n";
	tson::PropertyCollection collection = mp_map->getProperties();
	for( const auto&[ key, value ] : collection.getProperties() ) {
		if( value.getName() == "music" ) {
			m_music_path = value.getValue<std::string>();
			m_music_id	= src.music.Load( value.getValue<std::string>());
		}	
	}
	LOG.Time() << "Map Load Audio - end\n";
	return true;
}

void Map::Create( b2World& t_world ) { 
	for( auto layer : m_layers ) {
		layer->Create( t_world );
	}
	LOG.Time() << "Map Create layer. world="<<&t_world<<"\n";
	src.music.Get( m_music_id)->play();
	LOG.Time() << "Map Create: music["<<m_music_id<<"] play\n";
}	

void Map::Free() {
	LOG.Time() << "Map Free\n";
	src.music.Get( m_music_id )->stop();
	mp_entity_factory = nullptr;
}

void Map::FreeAssets() {
	LOG.Time() << "Map Free Assets\n";
	src.Free();
	tileset.Free();
}

void Map::SetEntityFactory( EntityFactory& t_entity_factory ) {
	LOG.Time() << "Map SetEntityFactory: " << &t_entity_factory << "->tilest " << &tileset << "\n";
	mp_entity_factory 		= &t_entity_factory;
	mp_entity_factory->tileset 	= &tileset;
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
	for( auto layer : m_layers ) { 
		layer->Update( t_dt );
	}
}

void Map::Events( sf::Event& t_event ) {
	//player.Events( t_event );
	for( auto layer : m_layers ) {
		layer->Events( t_event );
	}
	if( Keyboard::Instance()->WasPressed( sf::Keyboard::P )) {
		src.music.Get( m_music_id )->pause();
	}
}
