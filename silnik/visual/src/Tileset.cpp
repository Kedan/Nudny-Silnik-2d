#include <JSONLoader.h>
#include <Tileset.h>
#include <Animation.h>

using namespace n2d;

Tileset::Tileset() {
	m_sprites.clear();
	LOG.Time() << "Tileset constructor\n";
	LOG << "\n\nIMPORTANT!\n"
		<< "\tTile must have to defined bounding figure!\n"
		<< "\tIf not - segmentation foult occurs!\n"
		<< "\tCheck tilesets in Tiled til\n"
		<< "\tMust code exception for this!\n\n\n";
}

Tileset::~Tileset() {
	LOG.Time() << "Tileset descructor\n";
}

bool Tileset::Load( tson::Tileset& t_tileset, std::string t_dir ) {
	LOG.Time() << "Tileset Load - begin. \tName: " << t_tileset.getName() << " " << "("<< t_tileset.getTiles().size() <<")\n";
	if( m_grid_size.x != 0 && m_grid_size.y != 0 ) {
		LOG.Time() << "Tileset Load - \tMap grid size: [" << m_grid_size.x << ", " << m_grid_size.y << " ]\n";
		std::string texture_path = t_dir;
		texture_path.append( t_tileset.getImage() );
		int texture_id = mp_resources->textures.Load( texture_path );
		if( texture_id > -1 ) {
			int GID, w, h;
			float w2,h2;
			tson::Rect draw_rect;
			glm::vec2 tilesize;
			for( auto& tile : t_tileset.getTiles() ) {
				GID = tile.getGid();
				int animation_size = tile.getAnimation().size();
				int tmp_i = 0;
	
				LOG << "\tTile GID: " << GID;
				if( !IsTileExists( GID )) {
					draw_rect	= GetCorrectedDrawingRect( tile.getDrawingRect() );
					tilesize	= GetCorrectTileSize( draw_rect, tile.getTileSize() );
					w2 		= tilesize.x/2;
					h2		= tilesize.y/2;
					
					LOG << "\tframes: " <<animation_size;
					LOG << "\ttson draw rect: [" << draw_rect.x << ", " <<  draw_rect.y << ", " << draw_rect.width << ", " << draw_rect.height << " ] ";
					LOG << "\ttson tile size: [" << tilesize.x << ", "<< tilesize.y <<" ] \tbounding_figures( "<<tile.getObjectgroup().getObjects().size()<<" )"; 
					
					m_sprites[GID] = Sprite();
					m_sprites[GID].GID = GID;
					m_sprites[GID].SetSize( tilesize.x, tilesize.y );
					m_sprites[GID].SetTexture( mp_resources->textures.GetRef( texture_id ) );
					m_sprites[GID].SetTextureCoords( draw_rect.x, draw_rect.y, draw_rect.width, draw_rect.height );
					m_sprites[GID].collide = false;
					for( auto o : tile.getObjectgroup().getObjects()) {
						std::cout << "Obj TYpe " << o.getPosition().x << " " << o.getPosition().y << "\n";
						// if object is polygon
						if( o.getPolygons().size() > 2 ) {	
							tson::Vector2i o_local_offset = o.getPosition();
							std::vector<glm::vec2> tmp_v;
							for( auto v : o.getPolygons() ) {
								tmp_v.push_back( glm::vec2( v.x-w2+o_local_offset.x, v.y-h2+o_local_offset.y  ));
							}
							m_sprites[GID].collide = true;
							m_sprites[GID].SetVertices( tmp_v );
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
								m_sprites[GID].collide = true;
								m_sprites[GID].SetVertices( tmp_v );
							}
						//	std::vector<glm::vec2> tmp_v;
						//	tmp_v.push_back( glm::vec2(-w2,-h2));
						//	tmp_v.push_back( glm::vec2(-w2,h2));
						//	tmp_v.push_back( glm::vec2(w2,h2));
						//	tmp_v.push_back( glm::vec2(w2,-h2));
						//	m_sprites[GID].collide = true;
						//	m_sprites[GID].SetVertices( tmp_v );
						}			
					}
				       	if( tile.getObjectgroup().getObjects().size() == 0 ) {
				        	std::vector<glm::vec2> tmp_v;
				               	tmp_v.push_back( glm::vec2(-w2,-h2));
				        	tmp_v.push_back( glm::vec2(-w2,h2));
				        	tmp_v.push_back( glm::vec2(w2,h2));
				        	tmp_v.push_back( glm::vec2(w2,-h2));
						m_sprites[GID].collide = false;
				        	m_sprites[GID].SetVertices( tmp_v );
					}
					// animation load
					if( tile.getAnimation().size() > 0 ) {
						m_sprites[GID].animation.Load( tile.getAnimation(), t_tileset, m_grid_size );
					}
				} else {
					LOG << "\talready exists!";
				}// if tile exists
				if( !tile.getClassType().empty() ) {
					m_sprite_names[ tile.getClassType() ] = GID;
				}
				LOG << "\n";
			}
		}
	} else {
		LOG.Time() << "WARNING:\n"
			<< "\tCalculateing tile position may go wrong if grid is 0!\n"
			<< "\tTileset::SetMapGrid() should be called befoer Tileset::Load!\n"
			<< "\tCheck in Map::LoadTilesets()\n";
	}
	LOG.Time() << "Tileset Load - end\n";
	return true;
}

bool Tileset::Load( std::string t_filepath, std::string t_dir) {
	// TODO
	LOG.Time() <<" ERROR: Tileset Load( string, string )  - method not implemented yet!\n";
	return true;
}

bool Tileset::IsTileExists( int t_GID ) {
	return m_sprites.find( t_GID ) != m_sprites.end();
}

Sprite* Tileset::GetTile( int t_GID ) {
	if( IsTileExists( t_GID ))	
		return (Sprite*)(m_sprites[t_GID].Clone());
	return nullptr;
}

Sprite* Tileset::GetTile( std::string t_sprite_name ) {
	if( m_sprite_names.find( t_sprite_name ) == m_sprite_names.end() ) {
		LOG.Time() << "Tileset GetTile( "<<t_sprite_name<<" ) - couldnt find sprite by name. Try by GID.\n";
		return nullptr;
	}
	int tmp_GID = m_sprite_names[ t_sprite_name ];
	return GetTile( tmp_GID );
}

void Tileset::Free() {
	LOG.Time() << "Tileset Free\n";
	m_sprites.clear();
}

void Tileset::SetGridSize( glm::vec2 t_grid_size ) {
	m_grid_size = t_grid_size;
}

tson::Rect Tileset::GetCorrectedDrawingRect( tson::Rect t_draw_rect ) {
	tson::Rect r;
	r.x = t_draw_rect.x;
	r.y = t_draw_rect.y;
	int i = 1;
	if( m_grid_size.x != t_draw_rect.width ) {
		i = (int)(t_draw_rect.x / m_grid_size.x);
		r.x = i * t_draw_rect.width;
	}
	if( m_grid_size.y != t_draw_rect.height ) {
		i = (int)(t_draw_rect.y / m_grid_size.y);
		r.y = i * t_draw_rect.height;
	}
	r.width = t_draw_rect.width;
	r.height = t_draw_rect.height;
	return r;
}

glm::vec2 Tileset::GetCorrectTileSize( tson::Rect t_draw_rect, tson::Vector2i t_tile_size ) {
	return glm::vec2(
		t_draw_rect.width	!= m_grid_size.x ? t_draw_rect.width : t_tile_size.x,
		t_draw_rect.height 	!= m_grid_size.y ? t_draw_rect.height : t_tile_size.y
		);
}

void Tileset::Draw( sf::RenderWindow& t_window ) {
	// TODO
}

void Tileset::Draw( sf::RenderWindow& t_window, sf::Transform& t_transform ) {
	// TODO
}
