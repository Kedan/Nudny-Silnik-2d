#ifndef NUDNY_MAP_H
#define NUDNY_MAP_H

#include <iostream>
#include <list>
#include <glm/glm.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "box2d/box2d.h"
#include "tileson/tileson.h"
#include "Interfaces.h"
#include "Resources.h"
#include "Entity.h"
#include "EntityFactory.h"
#include "MapLayer.h"
#include "Actor.h"
#include "Keyboard.h"

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

			int				m_music_id;
			std::string			m_music_path;
		public:
			glm::vec2			position;
			Resources			src;
			Tileset				tileset;
			Logger				log;
		public:
			Map();
			Map( std::string );
			~Map();
			bool Load();
			bool Load( std::string );
			bool LoadAssets();
			void Create( b2World& );
			void Free();	
			void FreeAssets();
			void SetEntityFactory( EntityFactory& t_entity_factory );
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
			bool LoadAudio();

	}; // class Map
}; // namespace n2d

#endif
