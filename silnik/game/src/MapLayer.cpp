#include "MapLayer.h"

using namespace n2d;

Layer::Layer() {
}

void Layer::SetDefaultData( tson::Layer& t_layer ) {
	id	= t_layer.getId();
	name 	= t_layer.getName();
	visible = t_layer.isVisible();
	position.x = t_layer.getX() * 16;//mp_tileset->tilesize.x;
	position.y = t_layer.getY() * 16;//mp_tileset->tilesize.y;
}

glm::vec2 Layer::GetCorrectTilePosition( tson::Vector2f t_obj_position, glm::vec2 t_tile_size ) {
	float tmp = t_tile_size.y != m_grid_size.y ? t_tile_size.y - m_grid_size.y : 0;
	return glm::vec2( 
		m_grid_size.x * (int)( t_obj_position.x/t_tile_size.x ) + t_tile_size.x/2, 
		m_grid_size.y * (int)( t_obj_position.y/t_tile_size.t ) + (t_tile_size.y/2) - tmp
	); 
}

ImageLayer::ImageLayer() {
	LOG.Time() << "ImageLayer constructor\n";
}

void ImageLayer::Draw( sf::RenderWindow& t_window ) {
	m_body.Draw( t_window );
} 

void ImageLayer::Draw( sf::RenderWindow& t_window, sf::Transform& t_transform ) {
	m_body.Draw( t_window, t_transform );
}

void ImageLayer::Update( float t_dt ) {
	m_body.Update( t_dt);
}

bool ImageLayer::Load( std::string t_dir, tson::Layer& t_layer) {
	LOG.Time() << "ImageLayer Load - begin\n";
	if( mp_resources != nullptr && mp_tileset != nullptr ) {
		SetDefaultData( t_layer );	
		std::string tmp = t_dir;
		tmp.append( t_layer.getImage() );
		m_texture_id	= mp_resources->LoadTexture( tmp );
		glm::vec2 tex_size;
		tex_size.x = mp_resources->GetTexturePtr( m_texture_id )->getSize().x;
		tex_size.y = mp_resources->GetTexturePtr( m_texture_id )->getSize().y;
		glm::vec2 lyr_pos;
		lyr_pos.x = position.x + t_layer.getOffset().x;
		lyr_pos.y = position.y + t_layer.getOffset().y;

		m_body.SetPosition( position.x + t_layer.getOffset().x + tex_size.x/2, position.y + t_layer.getOffset().y + tex_size.y/2) ;
		m_rect.SetTexture( mp_resources->GetTextureRef( m_texture_id ));
		m_rect.SetSize( tex_size );
		m_rect.SetOrigin( tex_size.x/2, tex_size.y/2 );
		m_rect.SetPosition(0,0);
		m_body.Add( &m_rect );
		m_loaded = true;
	}
	LOG.Time() << "ImageLayer Load " << (m_loaded ? "OK" : "Failed") << "\n";
	return m_loaded;
}

void ImageLayer::Create( b2World& t_world ) {
	if( m_loaded ) {
		m_body.Create( t_world );
		m_body.Disable();
	}	
}

void ImageLayer::Events( sf::Event& t_event ) {}

TileLayer::TileLayer() {
	LOG.Time() << "TileLayer - constructor\n";
}

void TileLayer::Draw( sf::RenderWindow& t_window ) {
	m_body.Draw( t_window );
} 

void TileLayer::Draw( sf::RenderWindow& t_window, sf::Transform& t_transform ) {
	m_body.Draw( t_window, t_transform );
}

void TileLayer::Update( float t_dt ) {
	m_body.Update( t_dt);
}

bool TileLayer::Load( std::string t_dir, tson::Layer& t_layer) {
	LOG.Time() << "TileLayer Load - begin. name=" << t_layer.getName() << "\n";
	m_body.is_ground = true;
	SetDefaultData( t_layer );
	float w2,h2;
	LOG.Time() << "TileLayer Load - Loadin objects ("<<t_layer.getTileObjects().size()<<"):\n";

	for( auto& [pos,obj] : t_layer.getTileObjects() ) {
		int GID = obj.getTile()->getGid();
		if( mp_tileset->IsTileExists( GID )) {
			tson::Vector2f p = obj.getPosition();
			tson::Vector2i sp = obj.getTile()->getTileSize();
			Sprite* s = mp_tileset->GetTile( GID );
			glm::vec2	tile_size 	= s->GetSize(); 
			glm::vec2 correct_pos	= GetCorrectTilePosition( obj.getPosition(), s->GetSize() );

			w2 = s->GetSize().x/2;
			h2 = s->GetSize().y/2;
			s->SetPosition( correct_pos.x, correct_pos.y);
			if( obj.getTile()->hasFlipFlags( tson::TileFlipFlags::Horizontally )) {
				s->FlipHorizontal();
			}
			if( obj.getTile()->hasFlipFlags( tson::TileFlipFlags::Vertically )) {
				s->FlipVertical();
			}
			if( obj.getTile()->hasFlipFlags( tson::TileFlipFlags::Diagonally )) {
				s->FlipDiagonal();
			}
			
			LOG << "\tTile GID:" << GID << "\tsize["<<tile_size.x<<","<<tile_size.y<<"]" << "\tpos["<<correct_pos.x<<","<<correct_pos.y<<"]\n";

			s->Play();
			m_tiles.push_back( s );
			m_body.Add( s );
			m_loaded = true;
		} else {
			LOG << "ERROR: \t\tTile " << GID << " not exists!\n";
			m_loaded = false;
		}
	}
	LOG.Time() << "TileLayer load - end(" << (m_loaded ? "OK" : "Failed") <<")\n";
	return m_loaded;
}

void TileLayer::Create( b2World& t_world ) {
	LOG.Time() << "TileLayer Create( world="<<&t_world<<")\n";
	if( m_loaded ) {
		m_body.SetPosition( position.x, position.y );
		m_body.Create( t_world );
	}	
}

void TileLayer::Events( sf::Event& t_event ) {
}

EntityLayer::EntityLayer( EntityFactory* t_factory ) {
	LOG.Time() << "EntityLayer constructor( entity_factory="<<&t_factory<<")\n";
	mp_factory = t_factory;
}

void EntityLayer::Draw( sf::RenderWindow& t_window ) {
	for( auto entity : m_entities ) {
		entity->Draw( t_window );
	}
}

void EntityLayer::Draw( sf::RenderWindow& t_window, sf::Transform& t_transform ) {
	for( auto entity : m_entities ) {
		entity->Draw( t_window, t_transform );
	}
}

void EntityLayer::Update( float t_dt ) {
	for( auto entity : m_entities ) {
		entity->Update( t_dt );
	}
}

bool EntityLayer::Load( std::string t_dir, tson::Layer& t_layer) {
	LOG.Time() << "EntityLayer Load -  begin\n";
	LOG.Time() << "EntityLayer Load - Loading objects("<<t_layer.getObjects().size()<<")\n";
	if( mp_factory != nullptr ) {
		for( auto object : t_layer.getObjects() ) {
			Entity* e = mp_factory->Create( object );
			LOG << "\tEntity " << e << " " << object.getName() << "\n";
			if( e != nullptr ) {
				m_entities.push_back( e );
			}
		}
		m_loaded = true;
	} else {
		LOG.Time() << "\tERROR: Layer factory pointer is nullptr!!\n";
	}
	LOG.Time() << "EntityLayer - Load end ("<< (m_loaded ? "ok" : "failed" ) <<")\n";
	return m_loaded;
}

void EntityLayer::Create( b2World& t_world ) {
	for( auto entity : m_entities ) {
		entity->Create( t_world );
	}
}

void EntityLayer::Events( sf::Event& t_event ) {
	for( auto entity : m_entities ) {
		entity->Events( t_event );
	}
}

Layer* LayerFactory::Create( tson::Layer& t_layer, EntityFactory* t_entity_factory ) {
	Layer* result = nullptr;
	switch( t_layer.getType() ) {
		case tson::LayerType::ImageLayer:
			result = new ImageLayer();
			break;
		case tson::LayerType::TileLayer:
			result = new TileLayer();
			break;
		case tson::LayerType::ObjectGroup:
			result = new EntityLayer( t_entity_factory );
			break;
		default:
			std::cout << "LayerFactory - unknown type of layer\n";
			break;
	}
	return result;	
}
