#ifndef NUDNY_SILNIK_GAME_BODY_HPP
#define NUDNY_SILNIK_GAME_BODY_HPP

#include <memory>
#include <glm/glm.hpp>
#include <box2d/box2d.h>
#include <graph/Shape.hpp>
#include <game/Physic.hpp>

namespace ns {
	class Body {
		public:
			Body();
			void add(std::unique_ptr<Shape>);
			void create(b2WorldId&);
			//void create(Physic p);
			void update(const sf::Time&);
			void simulate(const sf::Time&);
			void draw(sf::RenderWindow&);
		public:
			float		rotation{0.f};
			sf::Vector2f 	position{0.f, 0.f};
			b2BodyDef	def;
			b2BodyId	id;
			std::vector<std::unique_ptr<Shape>> shapes;
	};
};

#endif
