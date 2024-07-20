#ifndef NUDNY_SILNIK_2D_GAME_MAP_DECORATION_LAYER_H
#define NUDNY_SILNIK_2D_GAME_MAP_DECORATION_LAYER_H

#include <MapLayer.h>
#include <Queue.h>

namespace nudny {
	class MapDecorationLayer : public MapLayer {
		public:
			MapDecorationLayer();
			void AddTile( std::shared_ptr<Sprite> );
		public:
			void Draw( sf::RenderWindow& );
			void Draw( sf::RenderWindow&, sf::Transform& );
			void Update( sf::Time& );
			void Events( sf::Event& );	
			void Run( sf::Event&, sf::Time&, sf::RenderWindow& );
			void Run( sf::Event&, sf::Time&, sf::RenderWindow&, sf::Transform& );
		protected:
			Queue					m_queue;
			std::vector<std::shared_ptr<Sprite>> 	m_tiles;
	};
};

#endif
