#include <tldTileset.h>
#include <tldSprite.h>

using namespace nudny;

bool tldTileset::Load(tson::Tileset& t_tson_tileset, Resources& t_resources, std::string t_dir, glm::vec2 t_map_grid_size) {
	m_tileset = t_tson_tileset;
	if( t_map_grid_size.x != 0 && t_map_grid_size.y != 0 ) {
		std::string tex_path = t_dir;
		tex_path.append( m_tileset.getImage() );
		int tex_id = t_resources.textures.Load( tex_path );
		if( tex_id != -1 ) {
			for( auto& tile : m_tileset.getTiles() ) {
				if( !IsTileExists( tile.getGid() )) {
					std::unique_ptr<tldSprite> s;
					if( s->Load( tile, t_resources, t_dir, t_map_grid_size ) ) {
						//m_sprites.insert( { tile.getGid(), std::unique_ptr<Sprite>( std::move( s ) });
						m_sprites.insert( std::pair<int,std::unique_ptr<Sprite>>(tile.getGid(),std::unique_ptr<Sprite>( std::move(s))));
					}
				}
				if( !tile.getClassType().empty() ) {
					AddAlias( tile.getGid(), tile.getClassType() );
				}
			}
		}
	}
	return true;
}
