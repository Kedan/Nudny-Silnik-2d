#ifndef NUDNY_MAP_H
#define NUDNY_MAP_H

#include <iostream>
#include <list>
#include <glm/glm.hpp>
#include <SFML/Graphics.hpp>
#include "box2d/box2d.h"
#include "tileson/tileson.h"
#include "Interfaces.h"
#include "Resources.h"
#include "Entity.h"
#include "EntityFactory.h"
#include "MapLayer.h"
#include "Actor.h"

namespace n2d {
	class Map : public Updatable, public Drawable, public Interactive {
		protected:
			glm::vec2			m_grid_size;
			LayerFactory*			mp_layer_factory;
			EntityFactory*			mp_entity_factory;
			std::unique_ptr<tson::Map>	mp_map;
			std::string			m_file_path;
			std::string			m_dir;
			bool				m_assets_loaded;
			std::vector<Layer*>		m_layers;
			//Player*				mp_player;
		public:
			glm::vec2			position;
			Resources			src;
			Tileset				tileset;
		public:
			Map();
			Map( std::string );
			bool Load();
			bool Load( std::string );
			bool LoadAssets();
			void Create( b2World& world );
			void Free();	
			void FreeAssets();
			inline void SetEntityFactory( EntityFactory& t_entity_factory ) {
				mp_entity_factory 		= &t_entity_factory;
				mp_entity_factory->tileset 	= &tileset;
			}
			void Draw( sf::RenderWindow& );
			void Draw( sf::RenderWindow&, sf::Transform& );
			void Update( float );
			void Events( sf::Event& );

			inline glm::vec2 GetGridSize() {
				return m_grid_size;
			}
			inline float GetGridWidth() {
				return m_grid_size.x;
			}
			inline float GetGridHeigh() {
				return m_grid_size.y;
			}
		protected:
			bool LoadTilesets();
			bool LoadImages();
			bool LoadLayers();

	}; // class Map
}; // namespace n2d

#endif
