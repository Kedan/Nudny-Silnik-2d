#ifndef NUDNY_SILNIK_2D_TILED_LOADER_H
#define NUDNY_SILNIK_2D_TILED_LOADER_H

#include <memory>
#include <glm/glm.hpp>
#include <tileson/tileson.h>
#include <Resources.h>
#include <nudny/silnik/Visual.h>

namespace nudny {
	class TiledCircleLoader {
	};
	class Tiled {
		public:
			Tiled( const Tiled& ) 		= delete;
			Tiled& operator=(const Tiled& ) 	= delete;

			static Tiled& Instance();
			
			std::unique_ptr<Circle> 	GetCircle( tson::Object& );
			std::unique_ptr<Rectangle> 	GetRectangle( tson::Object& );
			std::unique_ptr<Polygon>	GetPolygon( tson::Object& );
			std::vector<glm::vec2>		GetPolygonVertices( tson::Object&, glm::vec2, glm::vec2  );
			std::unique_ptr<Sprite>		GetSprite( tson::Tile& t_tile, std::shared_ptr<Resources> t_resources, std::string t_dir, glm::vec2 t_map_grid_size  );	
			glm::vec2 			GetCorrectTileSize( tson::Rect t_rect, tson::Vector2i t_size, glm::vec2 t_map_grid_size );			
			tson::Rect 			GetCorrectDrawingRect( const tson::Rect t_tile_drawing_rect, glm::vec2 t_map_grid_size );
			
			void 				LoadSpriteAnimation( SpriteAnimation& t_animation, tson::Animation& t_tson_animation, tson::Tileset* t_tson_tileset, glm::vec2 t_map_grid_size );
			void				LoadTileset( Tileset& t_tileset, tson::Tileset& t_tson_tileset,  std::shared_ptr<Resources> t_resources, std::string t_dir, glm::vec2 t_map_grid_size );
		
		private:
			Tiled(){}
			static std::unique_ptr<Tiled>	m_instance;
			static std::mutex		m_mutex;
	}; // class Tiled;
}; // namespace nudny

#endif
