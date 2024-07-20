#include "Converter.h"
#include "tldUtils.h"

using namespace nudny;

std::unique_ptr<tldUtils> tldUtils::m_instance;
std::mutex tldUtils::m_mutex;

tldUtils& tldUtils::Instance() {
	std::lock_guard<std::mutex> lock( m_mutex );
	if( !m_instance ) {
		m_instance.reset( new tldUtils() );
	}
	return *m_instance;
}

tldUtils::tldUtils() {
}

glm::vec2 tldUtils::GetCorrectTileSize( const tson::Rect& t_rect, const tson::Vector2i& t_size, glm::vec2 t_map_grid_size ) {
	return glm::vec2( 
		t_rect.width	!= t_map_grid_size.x ? t_rect.width : t_size.x,
		t_rect.height 	!= t_map_grid_size.y ? t_rect.height : t_size.y
	);
}

tson::Rect tldUtils::GetCorrectDrawingRectangle( const tson::Rect& t_draw_rect, glm::vec2 t_map_grid_size ) {
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

glm::vec2 tldUtils::GetCorrectTilePosition( tson::Vector2f t_tile_position, glm::vec2 t_tile_size, glm::vec2 t_map_grid_size ) {
	float tmp = t_tile_size.y != t_map_grid_size.y ? t_tile_size.y - t_map_grid_size.y : 0;
	return glm::vec2( 
		t_map_grid_size.x * (int)( t_tile_position.x/t_tile_size.x ) + (t_tile_size.x/2), 
		t_map_grid_size.y * (int)( t_tile_position.y/t_tile_size.t ) + (t_tile_size.y/2) - tmp
	); 

}
