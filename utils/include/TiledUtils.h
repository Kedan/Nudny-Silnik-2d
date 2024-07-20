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
	/**
	 * Utility class. Loads Tiled® data into Nudny Silnik® objects.
	 */
	class TiledUtils {
		public:
			TiledUtils( const TiledUtils& ) = delete;
			TiledUtils& operator=( const TiledUtils& ) = delete;
			static TiledUtils& Instance();

			TiledUtils();
			/**
			 * Load n2d::Rectangle from tson::Object
			 * @param Rectangle &t_rect 		- n2d::Rectangle reference. 
			 * @param tson::Object &t_obj 	- data to load. 
			 */
			static void 	LoadRectangle( Rectangle& t_rect, tson::Object& t_obj );
			
			/**
			 * Load n2d::Circle from tson::Object
			 * @param Circle &t_circle 	- n2d::Circle reference. 
			 * @param tson::Object &t_obj 	- data to load. 
			 */
			static void LoadCircle( Circle& t_circle, tson::Object& t_obj );		
			
			/**
			 * Load vertices that defines tson::Object. Those vertices are needed as parameter in n2d::Polygon constructor
			 * @param	tson::Object 	t_obj 		- tson object reference
			 * @param 	glm::vec2	t_half_size	- half of tile size. Default (0,0). Used to load sprite/tile collision shapes.
			 * @param	glm::vec2	t_position_offset	- Sprite/tile coordinate system offset. Used while loading sprite/tile collision shapes. Default value (0,0)
			 * @return std::vectro<glm::vec2> - vector of vertices
			 */	
			static std::vector<glm::vec2> LoadPolygonVertices( tson::Object& t_obj, glm::vec2 t_half_size = glm::vec2(0,0), glm::vec2 t_position_offset = glm::vec2(0,0) );			
			
			/**
			 * Loads tileson object properties into n2d::Polygon.
			 * ACHTUNG! To create n2d::Polygon object, you need set of verticies to define convex shape!
			 * To get it use n2d::TsonUtils::LoadPolygonVertices().  
			 */
			static void LoadPolygon( Polygon& t_poly, tson::Object& t_obj );
	
			/**
			 * Load data to sprite ( given by reference ) from tileson object.
			 * @param n2d::Sprite&	t_sprite 	- nudny sprite reference
			 *
			 * @param tson::Tile&	t_tile		- tileson tile data
			 * @param Resources*	t_resources	- poiner to nudny Resources
			 */		
			static void LoadSprite( Sprite& t_sprite, tson::Tile& t_tile, Resources& t_resources, std::string t_dir, glm::vec2 t_map_grid_size );
			
			/**
			 * Corrects tile size, becouse Tileson puts map grid size into tile size. This couse render problems when you use multiple tilesets with different tile sizes in Tiled editor.
			 * @param	tson::Rect		- tile drawing rectangle
			 * @param	tson::Vector2i		- tile size returned by tileson
			 * @param	glm::vec2		- map grid size
			 * @return	glm::vec2		- correct tile size
			 */
			static glm::vec2 GetCorrectTileSize( const tson::Rect& t_rect, const tson::Vector2i& t_size, glm::vec2 t_map_grid_size );
	
			/**
			 * Corrects tile drawing rectangle size. IF in yout Tiled map you use tilesets with different tile size, Tileson loads map grid size as tile drawing rectangle. This will couse drawing errors.
			 * @param	tson::Rectangle		- tile drawing rectangle reference
			 * @param	glm::vec2		- map grid size
			 * @return	tson::Rectangle		- correct drawing rectangle size
			 */ 
			static tson::Rect GetCorrectDrawingRectangle( const tson::Rect& t_tile_drawing_rect, glm::vec2 t_map_grid_size );
			
			/**
			 * Loads Tiled sprite animation data into nudny::SpriteAnimation object.
			 * @param	nudny::SpriteAnimation&	- reference to nudny animation object
			 * @param	tson::Animation&	- reference to tileson animation object
			 * @param	tons::Tileset*		- pointer to tileseon tileset, that animation uses.
			 * @param	glm::vec2		- map grid size. Used to correct tile size and tile drawing rectangle size.
			 */	
			static void LoadSpriteAnimation( SpriteAnimation& t_animation, tson::Animation& t_tson_animation, tson::Tileset* t_tson_tileset, glm::vec2 t_map_grid_size );
			
			/**
			 * Loads Tiled tileset into nudny::Tileset object
			 * @param	nudny::Tileset&			- reference to nudny::Tileset object
			 * @param	tson::Tileset&			- reference to tileson tileset object
			 * @param	std::shared_ptr<Resources> 	- shared pointer to nudny Resources, that tileset uses.
			 * @param	std::string			- path to resources directory, RELATIVE TO .JSON MAP FILE
			 * @param	glm::vec2			- map grid size. Used to correct tile size and tile drawing rectangle size.
			 */
			static void LoadTileset( Tileset& t_tileset, tson::Tileset& t_tson_tileset, Resources& t_resources, std::string t_dir, glm::vec2 t_map_grid_size );
			static bool LoadMap( Map& t_map, std::string t_map_file );
			static bool LoadMapAssets( Map& t_map, std::shared_ptr<tson::Map> t_tson_map, std::string );
			static bool LoadMapImages( Map& t_map, std::shared_ptr<tson::Map> t_tson_map, std::string );
			static bool LoadMapTilesets( Map& t_map, std::shared_ptr<tson::Map> t_tson_map, std::string );
			static bool LoadMapLayers( Map& t_map, std::shared_ptr<tson::Map> t_tson_map, std::string );
		protected:
			static std::unique_ptr<TiledUtils>	m_instance;
			static std::mutex			m_mutex;
			static tson::Tileson			m_parser;
	}; // class TiledUtils
}; // namespace

#endif
