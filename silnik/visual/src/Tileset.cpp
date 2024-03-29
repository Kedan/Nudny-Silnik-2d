#include <JSONLoader.h>
#include <Tileset.h>
#include <Animation.h>

using namespace n2d;

Tileset::Tileset() {
	m_sprites.clear();
}

void Tileset::Load( tson::Tileset& t_tileset, std::string t_dir ) {
	//m_sprites.clear();
	std::string texture_path = t_dir;
	texture_path.append( t_tileset.getImage() );
	int texture_id = mp_resources->LoadTexture( texture_path );
	if( texture_id > -1 ) {
		int GID, w, h;
		float w2,h2;
		tson::Rect draw_rect;
		//glm::vec4 draw_rect;
		glm::vec2 tilesize;
		for( auto& tile : t_tileset.getTiles() ) {
			GID = tile.getGid();
			int animation_size = tile.getAnimation().size();
			int tmp_i = 0;

		//	std::cout << "GID: " << GID << ", Tile animation frames: " << animation_size << "\n";
//			if( animation_size > 0 ) {
//				std::cout << "Animation current frame tile id: " << tile.getAnimation().getCurrentFrame()->getTileId() << "\n";
//				std::cout << "Animation current frame duration (ms): " << tile.getAnimation().getCurrentFrame()->getDuration() << "\n";
//				std::cout << "Frames("<<animation_size<<"): \n"; 
//				for( auto frame : tile.getAnimation().getFrames() ) {
//					std::cout << "begin - ";
//					int tID = frame.getTileId(); 
//					int tGID = t_tileset.getTile( tID )->getGid();
//					std::cout << "Tile id: " << frame.getTileId() << "\n";
//					std::cout << "Tile GID: " << tGID << "\n";
//					std::cout << "Duration: " << frame.getDuration() << "\n";
//					std::cout << " check!" << tmp_i << "\n";
//					tmp_i++;
//				}
//			}
//
			if( !IsTileExists( GID )) {
				draw_rect 	= tile.getDrawingRect();
				w		= tile.getTileSize().x;
				h 		= tile.getTileSize().y;

				// drawing rect correction if tile size is different then grid size

		//		tilesize	= GetCorrectTileSize( tile.getDrawingRect(), tile.getTileSize() );
		//		draw_rect	= GetCorrectedDrawingRect( tile.getDrawingRect(), tilesize );
		//		w2 		= tilesize.x/2;
		//		h2		= tilesize.y/2;

		//		std::cout << "TS [" << tilesize.x << ", " << tilesize.y << "] " << "DR [" << draw_rect.x << ", " << draw_rect.y << ", " << draw_rect.z << ", " << draw_rect.w << "]\n";
				w2 		= w/2;
				h2		= h/2;
				tilesize	= glm::vec2( w, h );
				
			//	int tmpGID = 99;
			//	if( GID == tmpGID ) {
			//		std::cout << "GID "<<tmpGID<<" draw rect: "
			//			<< draw_rect.x << " , "
			//			<< draw_rect.y << " , "
			//			<< draw_rect.width << ", "
			//			<< draw_rect.height << "\n";
			//	}	
				m_sprites[GID] = Sprite();
				m_sprites[GID].GID = GID;
				m_sprites[GID].SetSize( w, h );
				//m_sprites[GID].SetSize( tilesize.x, tilesize.y );
				m_sprites[GID].SetTexture( mp_resources->GetTextureRef( texture_id ) );
				m_sprites[GID].SetTextureCoords( draw_rect.x, draw_rect.y, draw_rect.width, draw_rect.height );
				//m_sprites[GID].SetTextureCoords( draw_rect );
				m_sprites[GID].collide = false;
				for( auto o : tile.getObjectgroup().getObjects()) {
					 if( o.getPolygons().size() > 2 ) {	
						tson::Vector2i o_local_offset = o.getPosition();
						std::vector<glm::vec2> tmp_v;
						for( auto v : o.getPolygons() ) {
							tmp_v.push_back( glm::vec2( v.x-w2+o_local_offset.x, v.y-h2+o_local_offset.y  ));
						}
						m_sprites[GID].collide = true;
						m_sprites[GID].SetVertices( tmp_v );
					} else {
						std::vector<glm::vec2> tmp_v;
						tmp_v.push_back( glm::vec2(-w2,-h2));
						tmp_v.push_back( glm::vec2(-w2,h2));
						tmp_v.push_back( glm::vec2(w2,h2));
						tmp_v.push_back( glm::vec2(w2,-h2));
						m_sprites[GID].collide = true;
						m_sprites[GID].SetVertices( tmp_v );
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
					m_sprites[GID].animation.Load( tile.getAnimation(), t_tileset );
				}
			}
		}
	}
}

void Tileset::Load( std::string t_filepath, std::string t_dir) {
	// TODO
}

bool Tileset::IsTileExists( int t_GID ) {
	return m_sprites.find( t_GID ) != m_sprites.end();
}

Sprite* Tileset::GetTile( int t_GID ) {
	if( IsTileExists( t_GID ))	
		return (Sprite*)(m_sprites[t_GID].Clone());
	return nullptr;
}

void Tileset::Free() {
	m_sprites.clear();
}

void Tileset::SetGridSize( glm::vec2 t_grid_size ) {
	m_grid_size = t_grid_size;
}

glm::vec4 Tileset::GetCorrectedDrawingRect( tson::Rect t_draw_rect, glm::vec2 t_tile_size ) {
	glm::vec4 r;
	r.x = t_draw_rect.x;
	r.y = t_draw_rect.y;
	int i = 1;
	if( t_tile_size.x != m_grid_size.x ) {
		i = (int)(t_draw_rect.x / m_grid_size.x);
		r.x = i * t_tile_size.x;
	}
	if( t_tile_size.y != m_grid_size.y ) {
		i = (int)(t_draw_rect.y / m_grid_size.y);
		r.y = i * t_tile_size.y;
	}
	r.z = t_draw_rect.width;
	r.w = t_draw_rect.height;
//	std::cout << "Tileset :: GetCorrectedDrawingRect - [ "
//		<< r.x << ", "
//		<< r.y << ", "
//		<< r.z << ", "
//		<< r.w << "] ";
//	std::cout << " tile size: ["
//		<< t_tile_size.x << ", " 
//		<< t_tile_size.y << "] ";
//	std::cout << "["
//		<< t_draw_rect.x << ", "
//		<< t_draw_rect.y << ", "
//		<< t_draw_rect.width << ", "
//		<< t_draw_rect.height << "]\n";
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
