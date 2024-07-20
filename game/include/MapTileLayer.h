#ifndef NUDNY_SILNIK_2D_GAME_MAP_TILE_LAYER_H
#define NUDNY_SILNIK_2D_GAME_MAP_TILE_LAYER_H

#include <iostream>
#include <memory>
#include <Sprite.h>
#include <Body.h>
#include <MapLayer.h>

namespace nudny {
	class MapTileLayer : 
	public MapLayer
	{
		public:
			MapTileLayer();
			void Draw( sf::RenderWindow& );
			void Draw( sf::RenderWindow&, sf::Transform& );
			void Update( sf::Time& );
			void Events( sf::Event& );
			void Create( b2World& t_world );
		protected:
			glm::vec2				osition_correction;
			std::vector<std::shared_ptr<Sprite>> 	m_tiles;
			Body					m_body;
	};
};

#endif
