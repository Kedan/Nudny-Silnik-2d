#include <tldUtils.h>
#include <tldSpriteAnimation.h>

using namespace nudny;

bool tldSpriteAnimation::Load( tson::Animation& t_animation, tson::Tileset* m_tileset_ptr, glm::vec2 t_map_grid_size ) {
	m_tiled_animation = t_animation;
	for( auto frame : m_tiled_animation.getFrames() ) {
		int first_gid		= m_tileset_ptr->getFirstgid();
		int tile_id		= frame.getTileId();
		tson::Tile *tile	= m_tileset_ptr->getTile( first_gid + tile_id - 1);
		if( tile ) {
			glm::vec4	draw_rect = Converter::TSON_TO_GLM().Rect( tldUtils::GetCorrectDrawingRectangle( tile->getDrawingRect(), t_map_grid_size ));
			AddFrame( frame.getDuration() * 0.001f, draw_rect );
		} else {
			std::cout << "tsonutils load sprite animation  - tile from frame is nullptr\n";
		}
	}
	return true;
}
