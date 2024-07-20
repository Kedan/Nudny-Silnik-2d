#ifndef NUDNY_SILNIK_2D_GAME_MAP_ENTITY_LAYER_H
#define NUDNY_SILNIK_2D_GAME_MAP_ENTITY_LAYER_H

#include <memory>
#include <glm/glm.hpp>
#include <EntityFactory.h>
#include <MapLayer.h>
#include <Queue.h>


namespace nudny {
	class MapEntityLayer : public MapLayer {
		public:
			MapEntityLayer();
			void Draw( sf::RenderWindow& );
			void Draw( sf::RenderWindow&, sf::Transform& );
			void Update( sf::Time& );
			void Events( sf::Event& );
			void Create( b2World& );
		protected:
			glm::vec2				m_position_correction;
			//std::shared_ptr<EntityFactory>		mp_factory;
			std::vector<std::shared_ptr<Entity>> 	m_entities;
			Queue					m_queue;
	};
};

#endif
