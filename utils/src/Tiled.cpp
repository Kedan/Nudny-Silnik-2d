#include <Tiled.h>

using namespace nudny;

std::unique_ptr<Tiled> Tiled::m_instance;

std::mutex Tiled::m_mutex;

Tiled& Tiled::Instance() {
	std::lock_guard<std::mutex> lock( m_mutex );
	if( !m_instance ) {
		m_instance.reset( new Tiled() );
	}
	return *m_instance;
}

std::unique_ptr<Circle> Tiled::GetCircle( tson::Object& t_object ) {
	std::unique_ptr<Circle> circle;
	circle.reset( new Circle() );
	circle->SetRadius( (t_object.getSize().x + t_object.getSize().y) * 0.5f );
	circle->SetPosition( t_object.getPosition().x, t_object.getPosition().y );
	circle->SetRotation( t_object.getRotation() );
	return std::move( circle );
}

std::unique_ptr<Rectangle> Tiled::GetRectangle( tson::Object& t_object ) {
	std::unique_ptr<Rectangle> rectangle( new Rectangle() );
	rectangle->SetOrigin( t_object.getSize().x/2, t_object.getSize().y/2 );
	rectangle->SetRotation( t_object.getRotation() );
	rectangle->SetPosition( t_object.getPosition().x + t_object.getSize().x/2, t_object.getPosition().y + t_object.getSize().y/2 );
	rectangle->SetSize( t_object.getSize().x, t_object.getSize().y );  
	return std::move( rectangle );
}

std::unique_ptr<Polygon> Tiled::GetPolygon( tson::Object& t_object ) {
	std::unique_ptr<Polygon> polygon( new Polygon() );
	polygon->SetPosition( t_object.getPosition().x, t_object.getPosition().y );
	polygon->SetRotation( t_object.getRotation() );
	return std::move( polygon );
}

std::vector<glm::vec2> Tiled::GetPolygonVertices( tson::Object& t_object, glm::vec2 t_half_size, glm::vec2 t_position_offset ) {
	std::vector<glm::vec2> vertices;
	for( auto v : t_object.getPolygons() ) {
		vertices.push_back( glm::vec2( v.x-t_half_size.x+t_position_offset.x, v.y-t_half_size.y+t_position_offset.y ));
	}
	return vertices;
}

std::unique_ptr<Sprite> Tiled::GetSprite( tson::Tile& t_tile, std::shared_ptr<Resources> t_resources, std::string t_dir, glm::vec2 t_map_grid_size ) {
	tson::Rect r 	= nudny::Tiled::Instance().GetCorrectDrawingRect( t_tile.getDrawingRect(), t_map_grid_size );
	glm::vec2 s 	= nudny::Tiled::Instance().GetCorrectTileSize( r, t_tile.getTileSize(), t_map_grid_size );
	float w2	= s.x*0.5f;
	float h2	= s.y*0.5f;
	std::string t	= t_dir.append( t_tile.getTileset()->getImage() );
	int tex_id	= t_resources->textures.Load( t );
	
	std::unique_ptr<Sprite> sprite( new Sprite( t_tile.getGid() ));
	//sprite->GID 	= t_tile.getGid();
	sprite->SetSize( s.x, s.y );
	sprite->SetTexture( &t_resources->textures.GetRef( tex_id ) );
	sprite->SetTextureCoords( r.x, r.y, r.width, r.height );
	sprite->collide = false;

	for( auto o : t_tile.getObjectgroup().getObjects()) {
		// if object is polygon
		if( o.getPolygons().size() > 2 ) {	
			tson::Vector2i o_local_offset = o.getPosition();
			std::vector<glm::vec2> tmp_v;
			for( auto v : o.getPolygons() ) {
				tmp_v.push_back( glm::vec2( v.x-w2+o_local_offset.x, v.y-h2+o_local_offset.y  ));
			}
			sprite->collide = true;
			sprite->SetVertices( tmp_v );
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
				sprite->collide = true;
				sprite->SetVertices( tmp_v );
			}
		}			
	}
	if( t_tile.getObjectgroup().getObjects().size() == 0 ) {
		std::vector<glm::vec2> tmp_v;
	       	tmp_v.push_back( glm::vec2(-w2,-h2));
		tmp_v.push_back( glm::vec2(-w2,h2));
		tmp_v.push_back( glm::vec2(w2,h2));
		tmp_v.push_back( glm::vec2(w2,-h2));
		sprite->collide = false;
		sprite->SetVertices( tmp_v );
	}
	if( t_tile.getAnimation().size() > 0 ) {
		nudny::Tiled::Instance().LoadSpriteAnimation( sprite->animation, t_tile.getAnimation(), t_tile.getTileset(), t_map_grid_size  );
	}
	return sprite;
}

glm::vec2 Tiled::GetCorrectTileSize( tson::Rect t_rect, tson::Vector2i t_size, glm::vec2 t_map_grid_size ) {
	return glm::vec2( 
		t_rect.width	!= t_map_grid_size.x ? t_rect.width : t_size.x,
		t_rect.height 	!= t_map_grid_size.y ? t_rect.height : t_size.y
	);
}	

tson::Rect Tiled::GetCorrectDrawingRect( const tson::Rect t_tile_draw_rect, glm::vec2 t_map_grid_size ) {
	tson::Rect r;
	r.x = t_tile_draw_rect.x;
	r.y = t_tile_draw_rect.y;
	int i = 1;
	if( t_map_grid_size.x != t_tile_draw_rect.width ) {
		i = (int)(t_tile_draw_rect.x / t_map_grid_size.x);
		r.x = i * t_tile_draw_rect.width;
	}
	if( t_map_grid_size.y != t_tile_draw_rect.height ) {
		i = (int)(t_tile_draw_rect.y / t_map_grid_size.y);
		r.y = i * t_tile_draw_rect.height;
	}
	r.width = t_tile_draw_rect.width;
	r.height = t_tile_draw_rect.height;
	return r;
}

void Tiled::LoadSpriteAnimation( SpriteAnimation& t_animation, tson::Animation& t_tson_animation, tson::Tileset* t_tson_tileset, glm::vec2 t_map_grid_size ) {
	for( auto frame : t_tson_animation.getFrames() ) {
		int first_gid		= t_tson_tileset->getFirstgid();
		int tile_id		= frame.getTileId();
		tson::Tile *tile	= t_tson_tileset->getTile( first_gid + tile_id - 1);
		if( tile ) {
			//glm::vec4	draw_rect = Tool::GetDrawingRect( tile->getDrawingRect(), t_map_grid_size );
			t_animation.AddFrame( frame.getDuration() * 0.001f, Tool::ConvertTsonToGlm( GetCorrectDrawingRect( tile->getDrawingRect(), t_map_grid_size ))	);
		} else {
			std::cout << "tsonutils load sprite animation  - tile from frame is nullptr\n";
		}
	}
}

void Tiled::LoadTileset( Tileset& t_tileset, tson::Tileset& t_tson_tileset,  std::shared_ptr<Resources>t_resources, std::string t_dir, glm::vec2 t_map_grid_size ) {
	LOG.Time() << "TsonUtils - Load Tileset( n2d::"<< &t_tileset << ", tson::"<<&t_tson_tileset<<", "<<t_dir<<" ) - begin\n";
	if( t_map_grid_size.x != 0 && t_map_grid_size.y != 0 ) {
		std::string tex_path = t_dir;
		tex_path.append( t_tson_tileset.getImage() );
		int tex_id = t_resources->textures.Load( tex_path );
		if( tex_id != -1 ) {
			for( auto& tile : t_tson_tileset.getTiles() ) {
				if( !t_tileset.IsTileExists( tile.getGid() )) {
					std::unique_ptr<Sprite> s = std::move( Tiled::Instance().GetSprite( tile, t_resources, t_dir, t_map_grid_size ));
					//TsonUtils::LoadSprite( t_tileset.AddNewSprite(tile.getGid()), tile, t_resources, t_dir, t_map_grid_size );	
				}
				if( !tile.getClassType().empty() ) {
					t_tileset.AddAlias( tile.getGid(), tile.getClassType() );
				}
			}
		}
	} else {
		LOG.Time() << "WARNING:\n"
			<< "\tCalculateing tile position may go wrong if grid is 0!\n"
			<< "\tTileset::SetMapGrid() should be called befoer TsonUtils::LoadTileset()!\n"
			<< "\tCheck in TsonUtils::LoadMap()\n";
	}
	LOG.Time() << "TsonUtils - Load - end\n";

}
