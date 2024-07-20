#include "Converter.h"
#include "TiledUtils.h"

using namespace nudny;

std::unique_ptr<TiledUtils> TiledUtils::m_instance;
std::mutex TiledUtils::m_mutex;
tson::Tileson TiledUtils::m_parser;

TiledUtils& TiledUtils::Instance() {
	std::lock_guard<std::mutex> lock( m_mutex );
	if( !m_instance ) {
		m_instance.reset( new TiledUtils() );
	}
	return *m_instance;
}

TiledUtils::TiledUtils() {
}

void TiledUtils::LoadRectangle( Rectangle& t_rect, tson::Object& t_obj ) {
	t_rect.SetOrigin( t_obj.getSize().x/2, t_obj.getSize().y/2 );
	t_rect.SetRotation( t_obj.getRotation() );
	t_rect.SetPosition( t_obj.getPosition().x + t_obj.getSize().x/2, t_obj.getPosition().y + t_obj.getSize().y/2 );
	t_rect.SetSize( t_obj.getSize().x, t_obj.getSize().y );  
}

void TiledUtils::LoadCircle( Circle& t_circle, tson::Object& t_obj ) {
	t_circle.SetPosition( t_obj.getPosition().x, t_obj.getPosition().y );
	t_circle.SetRadius( (t_obj.getSize().x + t_obj.getSize().y) * 0.5f );
}

std::vector<glm::vec2> TiledUtils::LoadPolygonVertices( tson::Object& t_obj, glm::vec2 t_half_size, glm::vec2 t_position_offset ) {
	std::vector<glm::vec2> vertices;
	glm::vec2 p( t_obj.getPosition().x, t_obj.getPosition().y );
	glm::vec2 s( t_obj.getSize().x, t_obj.getSize().y );
	for( auto v : t_obj.getPolygons() ) {
		//vertices.push_back( glm::vec2( v.x-(s.x/2)+p.x, v.y-(s.y/2)+p.y ));
		//vertices.push_back( glm::vec2( v.x, v.y ));
		vertices.push_back( glm::vec2( v.x-t_half_size.x+t_position_offset.x, v.y-t_half_size.y+t_position_offset.y ));
	}
	return vertices;
}

void TiledUtils::LoadPolygon( Polygon& t_poly, tson::Object& t_obj ) {
	t_poly.SetPosition( t_obj.getPosition().x, t_obj.getPosition().y );
	t_poly.SetRotation( t_obj.getRotation() );
}

void TiledUtils::LoadSprite( Sprite& t_sprite, tson::Tile& t_tile, Resources& t_resources, std::string t_dir, glm::vec2 t_map_grid_size ) {
	LOG.Time() << "TiledUtils Load Sprite "
		<< "\t gid=" << t_sprite.GetGid()
		<< "\t sprite=" << &t_sprite
		<< "\t tson::Tile=" << &t_tile
		<< "\t resources=" << &t_resources
		<< "\t dir=" << t_dir
		<< "\t map_grid_size=("<<t_map_grid_size.x<<","<<t_map_grid_size.y<<")\n";
	tson::Rect r 	= TiledUtils::GetCorrectDrawingRectangle( t_tile.getDrawingRect(), t_map_grid_size );
	glm::vec2 s 	= TiledUtils::GetCorrectTileSize( r, t_tile.getTileSize(), t_map_grid_size );
	float w2	= s.x*0.5f;
	float h2	= s.y*0.5f;
	std::string t	= t_dir.append( t_tile.getTileset()->getImage() );
	int tex_id	= t_resources.textures.Load( t );
	
	//t_sprite.GID 	= t_tile.getGid();
	t_sprite.SetSize( s.x, s.y );
	t_sprite.SetTexture( &t_resources.textures.GetRef( tex_id ) );
	t_sprite.SetTextureCoords( r.x, r.y, r.width, r.height );
	t_sprite.collide = false;

	for( auto o : t_tile.getObjectgroup().getObjects()) {
		// if object is polygon
		if( o.getPolygons().size() > 2 ) {	
			tson::Vector2i o_local_offset = o.getPosition();
			std::vector<glm::vec2> tmp_v;
			for( auto v : o.getPolygons() ) {
				tmp_v.push_back( glm::vec2( v.x-w2+o_local_offset.x, v.y-h2+o_local_offset.y  ));
			}
			t_sprite.collide = true;
			t_sprite.SetVertices( tmp_v );
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
				t_sprite.collide = true;
				t_sprite.SetVertices( tmp_v );
			}
		}			
	}
	if( t_tile.getObjectgroup().getObjects().size() == 0 ) {
		std::vector<glm::vec2> tmp_v;
	       	tmp_v.push_back( glm::vec2(-w2,-h2));
		tmp_v.push_back( glm::vec2(-w2,h2));
		tmp_v.push_back( glm::vec2(w2,h2));
		tmp_v.push_back( glm::vec2(w2,-h2));
		t_sprite.collide = false;
		t_sprite.SetVertices( tmp_v );
	}
	if( t_tile.getAnimation().size() > 0 ) {
		//nudny::TiledUtils::LoadSpriteAnimation( t_sprite.animation, t_tile.getAnimation(), t_tile.getTileset(), t_map_grid_size  );
	}
	//LOG.Time() << "TiledUtils Load Sprite - end\n";
}

glm::vec2 TiledUtils::GetCorrectTileSize( const tson::Rect& t_rect, const tson::Vector2i& t_size, glm::vec2 t_map_grid_size ) {
	return glm::vec2( 
		t_rect.width	!= t_map_grid_size.x ? t_rect.width : t_size.x,
		t_rect.height 	!= t_map_grid_size.y ? t_rect.height : t_size.y
	);
}

tson::Rect TiledUtils::GetCorrectDrawingRectangle( const tson::Rect& t_draw_rect, glm::vec2 t_map_grid_size ) {
	tson::Rect r;
	r.x = t_draw_rect.x;
	r.y = t_draw_rect.y;
	int i = 1;
	if( t_map_grid_size.x != t_draw_rect.width ) {
		i = (int)(t_draw_rect.x / t_map_grid_size.x);
		r.x = i * t_draw_rect.width;
	}
	if( t_map_grid_size.y != t_draw_rect.height ) {
		i = (int)(t_draw_rect.y / t_map_grid_size.y);
		r.y = i * t_draw_rect.height;
	}
	r.width = t_draw_rect.width;
	r.height = t_draw_rect.height;
	return r;
}

void TiledUtils::LoadSpriteAnimation( SpriteAnimation& t_animation, tson::Animation& t_tson_animation, tson::Tileset* t_tson_tileset, glm::vec2 t_map_grid_size ) { 
	for( auto frame : t_tson_animation.getFrames() ) {
		int first_gid		= t_tson_tileset->getFirstgid();
		int tile_id		= frame.getTileId();
		tson::Tile *tile	= t_tson_tileset->getTile( first_gid + tile_id - 1);
		if( tile ) {
			glm::vec4	draw_rect = Converter::TSON_TO_GLM().Rect( TiledUtils::GetCorrectDrawingRectangle( tile->getDrawingRect(), t_map_grid_size ));
			t_animation.AddFrame( frame.getDuration() * 0.001f, draw_rect );
		} else {
			std::cout << "tsonutils load sprite animation  - tile from frame is nullptr\n";
		}
	}
}

void TiledUtils::LoadTileset( Tileset& t_tileset, tson::Tileset& t_tson_tileset, Resources& t_resources, std::string t_dir, glm::vec2 t_map_grid_size ) {
	LOG.Time() << "TiledUtils - Load Tileset( n2d::"<< &t_tileset << ", tson::"<<&t_tson_tileset<<", "<<t_dir<<" ) - begin\n";
	if( t_map_grid_size.x != 0 && t_map_grid_size.y != 0 ) {
		std::string tex_path = t_dir;
		tex_path.append( t_tson_tileset.getImage() );
		int tex_id = t_resources.textures.Load( tex_path );
		if( tex_id != -1 ) {
			for( auto& tile : t_tson_tileset.getTiles() ) {
				if( !t_tileset.IsTileExists( tile.getGid() )) {
					if( t_tileset.CreateNewSprite( tile.getGid(), tile.getClassType()) ) {
						TiledUtils::LoadSprite( *t_tileset.GetTileProto(tile.getGid()), tile, t_resources, t_dir, t_map_grid_size );
					}
				//iledUtils::LoadSprite( *tmp, tile, t_resources, t_dir, t_map_grid_size );
				//	std::unique_ptr<Sprite> s( new Sprite( tile.getGid() ));
				//	TiledUtils::LoadSprite( *s, tile, t_resources, t_dir, t_map_grid_size );
				//	LOG.Time() << "\t creating new sprite in tileset"
				//		<< "gid=" << s->GetGid()
				//		<< "classtype=" << tile.getClassType()
				//		<< "\n";
				//	t_tileset.CreateNewSprite( s->GetGid(), std::move(s), tile.getClassType() );
				}
				if( !tile.getClassType().empty() ) {
					t_tileset.AddAlias( tile.getGid(), tile.getClassType() );
				}
			}
		}
	} else {
		LOG.Time() << "WARNING:\n"
			<< "\tCalculateing tile position may go wrong if grid is 0!\n"
			<< "\tTileset::SetMapGrid() should be called befoer TiledUtils::LoadTileset()!\n"
			<< "\tCheck in TiledUtils::LoadMap()\n";
	}
	LOG.Time() << "TiledUtils - Load - end\n";
}

bool TiledUtils::LoadMap( Map& t_map, std::string t_file ) {
	LOG.Time() << "TiledUtils LoadMap " << t_file << "\n";
	bool 				result 	= false;
	std::string			path	= t_file;
	std::size_t			tmp	= path.rfind("/");
	std::string			dir	= path.substr(0,tmp);
	t_map.data				= TiledUtils::Instance().m_parser.parse( path );
//	std::shared_ptr<tson::Map>	map 	= TiledUtils::Instance().m_parser.parse( path ); // to rozpierdala srpajty
	dir.append("/");
//	if( map->getStatus() == tson::ParseStatus::OK ) {
//		t_map.SetGridSize( Converter::TSON_TO_GLM().Vec2( map->getTileSize() ));
//		if( TiledUtils::LoadMapAssets( t_map, map, dir )) {
//			result = TiledUtils::LoadMapLayers( t_map,  map , dir );
//		}
//	}
	LOG.Time() << "TIledUtils loading map "<<(result ? "ok" : "failed")<<"\n";
	return result;
};

bool TiledUtils::LoadMapAssets( Map& t_map, std::shared_ptr<tson::Map> t_tson, std::string t_dir ) {
	LOG.Time() << "TiledUtils LoadMapAssets\n";
//	bool images 	= LoadMapImages( t_map, t_tson, t_dir );
//	bool tilesets 	= LoadMapTilesets( t_map, t_tson, t_dir );	
	return true;
}

bool TiledUtils::LoadMapImages( Map& t_map, std::shared_ptr<tson::Map> t_tson, std::string t_dir ) {
	LOG.Time() << "TiledUtils LoadMapImages\n";
	for( auto& layer : t_tson->getLayers() ) {
		std::cout << layer.getName() << "\n";
		switch( layer.getType() ) {
			case tson::LayerType::ImageLayer: { 
				std::cout << "test\n";
				std::string tmp = t_dir;
				tmp.append( layer.getImage() );
				//t_map.src.textures.Load( tmp );
			} 
			break;
		}	
	}
	return true;
}

bool TiledUtils::LoadMapTilesets( Map& t_map, std::shared_ptr<tson::Map> t_tson, std::string t_dir ) {
	bool result = false;
	LOG.Time() << "Map Load Tilesets("<< t_tson.get()  << t_tson->getTilesets().size() <<") - begin\n";
	for( auto t : t_tson->getTilesets() ) {
		//t_map.tileset.SetGridSize( t_map.GetGridSize());
		//TiledUtils::LoadTileset( t_map.tileset, t, t_map.src, t_dir, t_map.GetGridSize() );
		//result = tileset.Load( t, m_dir );
		result = true;
	}
	LOG.Time() << "Map Load Tileset - end("<<(result?"ok":"failed")<<")\n";
	return result;
	
}

bool TiledUtils::LoadMapLayers( Map& t_map, std::shared_ptr<tson::Map> t_tson, std::string ) {
	return true;
}
//bool TiledUtils::LoadDecorationLayer( DecorationLayer& t_layer, tson::Layer& t_tson_layer, Resources* tp_src, Tileset* tp_tileset, glm::vec2 t_map_grid_size ) {
//	LOG.Time() << "Tiled Utils Load Decoration Layer( lyr:"
//		<< &t_layer 
//		<< ", tson::lyt:" 
//		<< &t_tson_layer 
//		<< ", src:" 
//		<< tp_src 
//		<< ",  map_grid["
//		<< t_map_grid_size.x
//		<< ","
//		<< t_map_grid_size.y
//		<< "]) - begin\n";
//	t_layer.SetDefaultData( t_tson_layer );
//	float w2, h2;
//	for( auto [pos,obj] : t_tson_layer.getTileObjects() ) {
//		int GID = obj.getTile()->getGid();
//		if( tp_tileset->IsTileExists( GID )) {
//			tson::Vector2f	p 		= obj.getPosition();
//			tson::Vector2i	sp 		= obj.getTile()->getTileSize();
//			Sprite* 	s		= tp_tileset->GetTile( GID );
//			glm::vec2	tile_size 	= s->GetSize(); 
//			glm::vec2 	correct_pos	= TiledUtils::GetCorrectTilePosition( t_map_grid_size, obj.getPosition(), s->GetSize() );
//			w2				= tile_size.x / 2;
//			h2				= tile_size.y / 2;
//			s->SetPosition( correct_pos.x, correct_pos.y );
//			if( obj.getTile()->hasFlipFlags( tson::TileFlipFlags::Horizontally )) {
//				s->FlipHorizontal();
//			}
//			if( obj.getTile()->hasFlipFlags( tson::TileFlipFlags::Vertically )) {
//				s->FlipVertical();
//			}
//			if( obj.getTile()->hasFlipFlags( tson::TileFlipFlags::Diagonally )) {
//				s->FlipDiagonal();
//			}
//			s->Play();
//			t_layer.AddTile( s );			
//		}
//	}
//	LOG.Time() << "Tiled Utils Load Decoration Layer() - end\n";
//	return true;
//}
//
//glm::vec2 TiledUtils::GetCorrectTilePosition( glm::vec2 t_map_grid_size, tson::Vector2f t_obj_position, glm::vec2 t_tile_size ) {
//	float tmp = t_tile_size.y != t_map_grid_size.y ? t_tile_size.y - t_map_grid_size.y : 0;
//	return glm::vec2( 
//		t_map_grid_size.x * (int)( t_obj_position.x/t_tile_size.x ) + t_tile_size.x/2, 
//		t_map_grid_size.y * (int)( t_obj_position.y/t_tile_size.t ) + (t_tile_size.y/2) - tmp
//	); 
//}
//
//bool TiledUtils::LoadMusic( MusicShape& t_music, tson::Object& t_object ) {
//	tson::PropertyCollection p = t_object.getProperties();
//	t_music.Load( p.getValue<std::string>("file_path") );
//	t_music.SetVolume( p.getValue<float>("volume"));
//	t_music.SetRadius( t_object.getSize().x/2 );
//	t_music.SetPosition( t_object.getPosition().x, t_object.getPosition().y );
//	t_music.SetVisible( true );
//	t_music.SetColor();
//	return true;
//};
