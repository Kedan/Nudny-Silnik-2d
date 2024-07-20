#include <tlObjects.h>

using namespace nudny;

bool tlCircle::Load( tson::Object& t_object ) {
	m_obj = t_object;
	SetPosition( m_obj.getPosition().x, m_obj.getPosition().y );
	SetRadius( (m_obj.getSize().x + m_obj.getSize().y ) * 0.5f );
	return true;
}

bool tlRectangle::Load( tson::Object& t_object ) {
	m_obj = t_object;
	SetOrigin( m_obj.getSize().x/2, m_obj.getSize().y/2 );
	SetRotation( m_obj.getRotation() );
	SetPosition( m_obj.getPosition().x + m_obj.getSize().x/2, m_obj.getPosition().y + m_obj.getSize().y/2 );
	SetSize( m_obj.getSize().x, m_obj.getSize().y );  
	return true;
}

bool tlPolygon::Load( tson::Object& t_object ) {
	m_obj = t_object;
	SetVertices( TiledUtils::LoadPolygonVertices( t_object, glm::vec2( m_obj.getSize().x/2, m_obj.getSize().y/2), glm::vec2( m_obj.getPosition().x, m_obj.getPosition().y )));
	SetPosition( m_obj.getPosition().x, m_obj.getPosition().y );
	SetRotation( m_obj.getRotation() );
	return true;
}

bool tlSprite::Load( tson::Tile& t_ile, Resources& t_src, std::string t_dir, glm::vec2 t_map_grid_size ) {
	m_obj = t_object;
	tson::Rect r 	= TiledUtils::GetCorrectDrawingRectangle( t_tile.getDrawingRect(), t_map_grid_size );
	glm::vec2 s 	= TiledUtils::GetCorrectTileSize( r, t_tile.getTileSize(), t_map_grid_size );
	float w2	= s.x*0.5f;
	float h2	= s.y*0.5f;
	std::string t	= t_dir.append( t_tile.getTileset()->getImage() );
	int tex_id	= t_resources.textures.Load( t );
	
	m_gid 	= t_tile.getGid();
	SetSize( s.x, s.y );
	SetTexture( &t_resources.textures.GetRef( tex_id ) );
	SetTextureCoords( r.x, r.y, r.width, r.height );
	collide = false;

	for( auto o : t_tile.getObjectgroup().getObjects()) {
		// if object is polygon
		if( o.getPolygons().size() > 2 ) {	
			tson::Vector2i o_local_offset = o.getPosition();
			std::vector<glm::vec2> tmp_v;
			for( auto v : o.getPolygons() ) {
				tmp_v.push_back( glm::vec2( v.x-w2+o_local_offset.x, v.y-h2+o_local_offset.y  ));
			}
			collide = true;
			SetVertices( tmp_v );
		} else if( o.isEllipse() ) {
		} else {
			tson::Vector2i tmp_size = o.getSize();
			tson::Vector2i tmp_pos	= o.getPosition();
			if( tmp_size.x != 0 && tmp_size.y != 0 ) {
				float tw2 = tmp_size.x/2;
				float th2 = tmp_size.y/2;

				float tx = tmp_pos.x/2;
				float ty = tmp_pos.y/2;
						
				std::vector<glm::vec2> tmp_v;
				tmp_v.push_back( glm::vec2(-tw2 + tx, -th2 + ty));
				tmp_v.push_back( glm::vec2(-tw2 + tx ,th2 + ty));
				tmp_v.push_back( glm::vec2(tw2 + tx,th2 + ty ));
				tmp_v.push_back( glm::vec2(tw2 + tx ,-th2 + ty));
				collide = true;
				SetVertices( tmp_v );
			}
		}			
	}
	if( t_tile.getObjectgroup().getObjects().size() == 0 ) {
		std::vector<glm::vec2> tmp_v;
	       	tmp_v.push_back( glm::vec2(-w2,-h2));
		tmp_v.push_back( glm::vec2(-w2,h2));
		tmp_v.push_back( glm::vec2(w2,h2));
		tmp_v.push_back( glm::vec2(w2,-h2));
		collide = false;
		SetVertices( tmp_v );
	}
	if( t_tile.getAnimation().size() > 0 ) {	
		//nudny::TiledUtils::LoadSpriteAnimation( t_sprite.animation, t_tile.getAnimation(), t_tile.getTileset(), t_map_grid_size  );
	}
	return true;
}
