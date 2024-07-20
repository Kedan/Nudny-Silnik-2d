#ifndef NUDNY_SILNIK_2D_GAME_MAP_IMAGE_LAYER_H
#define NUDNY_SILNIK_2D_GAME_MAP_IMAGE_LAYER_H

#include <Rectangle.h>
#include <Body.h>
#include <MapLayer.h>

namespace nudny {
	class MapImageLayer : public MapLayer {
		public:
			MapImageLayer();
			void Draw( sf::RenderWindow& );
			void Draw( sf::RenderWindow&, sf::Transform& );
			void Update( sf::Time& );
			void Events( sf::Event& );
		protected:
			int 		m_texture_id;
			Rectangle	m_rectangle;
			Body		m_body;
	};
};

#endif
