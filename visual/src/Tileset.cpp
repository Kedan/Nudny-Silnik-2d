#include "Tileset.h"

using namespace nudny;

Tileset::Tileset() {
	LOG.Time() << "Tileset constructor\n";
	m_sprites.clear();
	m_sprite_names.clear();
}

Tileset::~Tileset() {
	LOG.Time() << "Tileset destructor\n";
}

//void Tileset::SetResources( std::shared_ptr<Resources> t_resources ) {
//	mp_resources = t_resources;
//}

void Tileset::SetGridSize( glm::vec2 t_grid_size ) {
	m_grid_size = t_grid_size;
}

bool Tileset::AddTile( Sprite* t_sprite, std::string t_alias ) {
	if( t_sprite->GetGid() != -1 && !IsTileExists( t_sprite->GetGid() )) {
		m_sprites.insert( std::pair<int,std::unique_ptr<Sprite>>( t_sprite->GetGid(), std::unique_ptr<nudny::Sprite>( t_sprite)));
		if( !t_alias.empty() ) {
			AddAlias( t_sprite->GetGid(), t_alias );
		}
		return true;
	}
	return false;
}

bool Tileset::AddSprite( Sprite* t_sprite, std::string t_alias ) {
	return AddTile( t_sprite, t_alias );
}

Sprite* Tileset::GetTile( int t_gid ) {
	if( IsTileExists( t_gid ) ) {
		return m_sprites[t_gid]->CloneStrict();
	}
	return nullptr;
}

Sprite* Tileset::GetTile( std::string t_alias ) {
	if( m_sprite_names.find( t_alias) != m_sprite_names.end() ) {
		int gid = m_sprite_names[ t_alias ];
		return m_sprites[ gid ]->CloneStrict() ;
	}
	return nullptr;
}

bool Tileset::IsTileExists( int t_gid ) {
	return m_sprites.find( t_gid ) != m_sprites.end();
}

bool Tileset::AddAlias( int t_gid, std::string t_alias ) {
	//if( m_sprite_names.find( t_alias ) != m_sprite_names.end() && m_sprites.find( t_gid )!=m_sprites.end()) {
		m_sprite_names[ t_alias ] = t_gid;
		return true;
	//}
	//return false;
}

bool Tileset::AddTileAnimation( std::string t_tile_alias, std::map<std::string,float> t_frames ) {
	if( m_sprite_names.find( t_tile_alias ) == m_sprite_names.end() ) {
		return false;
	}
	int id = m_sprite_names[ t_tile_alias ];
	int fid;
	for( auto [ tile_alias, frame_duration] : t_frames ) {
		if( m_sprite_names.find( tile_alias ) != m_sprite_names.end() ) {
			fid = m_sprite_names[ tile_alias ];
			m_sprites[id]->animation->AddFrame( frame_duration, m_sprites[fid]->GetTextureCoords());
		}	
	}
	return true;
}

void Tileset::Draw( sf::RenderWindow& t_window ) {
	// TODO
}

void Tileset::Draw( sf::RenderWindow& t_window, sf::Transform& t_transform ) {
	// TODO
}

bool Tileset::LoadTilesetFromTexture( const sf::Texture& t_texture, int t_rows, int t_columns, int t_tile_width, int t_tile_height, std::string t_alias_prefix ) {
	bool result = true;
	int gid = m_sprites.size();
	int current_tile_index = 0;
	std::string alias;
	for( int r = 0; r < t_rows; r++ ) {
		for( int c = 0; c<t_columns; c++ ) {
			Sprite* tmp = new Sprite( gid );
			tmp->SetTexture( t_texture );
			tmp->SetTextureCoords( c*t_tile_width, r*t_tile_height, t_tile_width, t_tile_height );
			if( !t_alias_prefix.empty() ) {
				alias = t_alias_prefix;
				alias += std::to_string( current_tile_index );
			} 
			result &= AddTile( tmp, alias );
			gid++;
			current_tile_index++;
		}
	}
	return result;
}

bool Tileset::LoadTileFromTexture( const sf::Texture& t_texture, int t_draw_rect_x, int t_draw_rect_y, int t_draw_rect_width, int t_draw_rect_height, std::string t_alias ) {
	int gid = m_sprites.size();
	Sprite* tmp = new Sprite( gid );
	tmp->SetTexture( t_texture );
	tmp->SetTextureCoords( t_draw_rect_x, t_draw_rect_y, t_draw_rect_width, t_draw_rect_height );
	return AddTile( tmp, t_alias );
}
