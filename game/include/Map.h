#ifndef NUDNY_SILNIK_2D_GAME_MAP_H
#define NUDNY_SILNIK_2D_GAME_MAP_H

#include <memory>
#include <glm/glm.hpp>
#include <Interfaces.h>
#include <Log.h>
#include <Tileset.h>

namespace nudny {
	class Map : 
	public Drawable,
	public Creatable, 
	public Updatable,
	public Interactive 
	{
		public:
			Map();
			Map( std::string );
			~Map();
	
			void		SetGridSize( glm::vec2 );
			glm::vec2	GetGridSize();
			float		GetGridWidth();
			float		GetGridHeight();

			void Draw( sf::RenderWindow& );
			void Draw( sf::RenderWindow&, sf::Transform& );
			void Create( b2World& );
			void Update( sf::Time& );
			void Events( sf::Event& );
		public:
			std::unique_ptr<tson::Map>	data;
			glm::vec2	position;
		//	Tileset		tileset;
		//	Resources 	src;
		protected:
			glm::vec2			m_grid_size;
			std::unique_ptr<tson::Map>	m_tson_map;
			std::string			m_file_path;
			std::string			m_dir;
			bool				m_assets_loaded;
	}; // class Map
}; // namespace

#endif
