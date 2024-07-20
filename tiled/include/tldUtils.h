#ifndef NUDNY_SILNIK_2D_UTILS_TILEDUTILS_H
#define NUDNY_SILNIK_2D_UTILS_TILEDUTILS_H

#include <tileson/tileson.h>
#include <Log.h>
#include "Resources.h"
#include <Tool.h>
#include <Circle.h>
#include <Rectangle.h>
#include <Polygon.h>
#include <Sprite.h>
#include <Tileset.h>
#include <Map.h>

namespace nudny {
	class tldUtils {
		public:
			tldUtils( const tldUtils& ) = delete;
			tldUtils& operator=( const tldUtils& ) = delete;
			static tldUtils& Instance();

			tldUtils();
			static glm::vec2 GetCorrectTileSize( const tson::Rect& t_rect, const tson::Vector2i& t_size, glm::vec2 t_map_grid_size );
			static tson::Rect GetCorrectDrawingRectangle( const tson::Rect& t_tile_drawing_rect, glm::vec2 t_map_grid_size);
			static glm::vec2 GetCorrectTilePosition( tson::Vector2f t_tile_position, glm::vec2 t_tile_size , glm::vec2 t_map_grid_size );
		protected:
			static std::unique_ptr<tldUtils>	m_instance;
			static std::mutex			m_mutex;
	}; // class tldUtils
}; // namespace

#endif
