#include <tldUtils.h>
#include <tldMapTileLayer.h>

using namespace nudny;

bool tldMapTileLayer::Load( tson::Layer& t_layer, std::string t_dir ) {
	if( mp_resources && mp_tileset ) {
		float w2,h2;
		m_layer 		= t_layer;
		m_body.is_ground	= true;
		m_id			= m_layer.getId();
		m_name 			= m_layer.getName();
		m_visible 		= m_layer.isVisible();
		m_position.x 		= m_layer.getX() * 16;
		m_position.y		= m_layer.getY() * 16;
		for( auto& [pos,obj] : t_layer.getTileObjects() ) {
			int GID = obj.getTile()->getGid();
			if( mp_tileset->IsTileExists( GID )) {
				tson::Vector2f 	p 		= obj.getPosition();
				tson::Vector2i 	sp 		= obj.getTile()->getTileSize();
				
				//Sprite* 	s 		= mp_tileset->GetTile( GID );
				
				std::shared_ptr<Sprite> s( mp_tileset->GetTile( GID ));
				glm::vec2	tile_size 	= s->GetSize(); 
				glm::vec2 	correct_pos	= tldUtils::GetCorrectTilePosition( obj.getPosition(), s->GetSize(), m_grid_size );
	
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
				s->animation->Play();
				m_tiles.push_back( s );
				m_body.Add( s );
				m_is_loaded = true;
			}
		}
	}
	return m_is_loaded;
};
