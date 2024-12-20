#ifndef NUDNY_SILNIK_GRAPH_CIRCLE_HPP
#define NUDNY_SILNIK_GRAPH_CIRCLE_HPP

#include <graph/Shape.hpp>

namespace ns {
	class Circle : public Shape {
		public:
			Circle() : Shape() {}
			Circle(float t_r) : Shape(), radius(t_r) {}
			void reset();
			void center();
			void create(b2BodyId&);
			void update(const sf::Time&);
			void simulate(const sf::Time&);
			void draw(sf::RenderWindow&);
		public:
			float			radius{10.f};
			b2Circle		b2;
			sf::CircleShape	sf;
	};
};

#endif
