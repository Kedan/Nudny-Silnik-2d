#ifndef NUDNY_SILNIK_2D_GAME_MAP_COLLISION_LAYER_H
#define NUDNY_SILNIK_2D_GAME_MAP_COLLISION_LAYER_H

#include <MapLayer.h>
#include <Body.h>
#include <Queue.h>

namespace nudny {
	class MapCollisionLayer : public MapLayer {
		public:
			MapCollisionLayer();
			
			void Draw( sf::RenderWindow& );
			void Darw( sf::RenderWindow&, sf::Transform& );
			void Update( sf::Time& );
			void Create( b2World& );
			void Events( sf::Event& );
		protected:
			glm::vec2				m_position_correction;
			Body					m_body;
			std::vector<std::shared_ptr<Shape>>	m_shapes;
			Queue					m_queue;
	};
};

#endif
