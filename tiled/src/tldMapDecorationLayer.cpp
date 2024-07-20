#include <tldUtils.h>
#include <tldMapDecorationLayer.h>

using namespace nudny;

bool tldMapDecorationLayer::Load( tson::Layer& t_layer, std::string t_dir ) {
	if( mp_resources && mp_tileset ) {
		float w2, h2;
		m_layer = t_layer;
		m_id	= m_layer.getId();
		m_name 	= m_layer.getName();
		m_visible = m_layer.isVisible();
		m_position.x = m_layer.getX() * 16;
		m_position.y = m_layer.getY() * 16;
		for( auto [pos,obj] : m_layer.getTileObjects() ) {
			int GID = obj.getTile()->getGid();
			if( mp_tileset->IsTileExists( GID )) {
				tson::Vector2f	p 		= obj.getPosition();
				tson::Vector2i	sp 		= obj.getTile()->getTileSize();
				std::shared_ptr<Sprite> 	s( mp_tileset->GetTile( GID ));
				glm::vec2	tile_size 	= s->GetSize(); 
				//glm::vec2 	correct_pos	= tldUtils::GetCorrectTilePosition( m_grid_size, obj.getPosition(), s->GetSize() );
				glm::vec2 	correct_pos	= tldUtils::GetCorrectTilePosition(  obj.getPosition(), s->GetSize(), m_grid_size ); 
				w2				= tile_size.x / 2;
				h2				= tile_size.y / 2;
				s->SetPosition( correct_pos.x, correct_pos.y );
				if( obj.getTile()->hasFlipFlags( tson::TileFlipFlags::Horizontally )) {
					s->FlipHorizontal();
				}
				if( obj.getTile()->hasFlipFlags( tson::TileFlipFlags::Vertically )) {
					s->FlipVertical();
				}
				if( obj.getTile()->hasFlipFlags( tson::TileFlipFlags::Diagonally )) {
					s->FlipDiagonal();
				}
				s->Play();
				AddTile( s );			
			}
		}
	}
	return m_is_loaded;
};
