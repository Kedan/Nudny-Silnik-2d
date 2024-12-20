#ifndef NUDNY_SILNIK_2D_GRAPH_RECTANGLE_HPP
#define NUDNY_SILNIK_2D_GRAPH_RECTANGLE_HPP

#include <graph/Shape.hpp>

namespace ns {
	class Rectangle : public Shape {
		public:
			Rectangle() : Shape() {}
			Rectangle( float t_width, float t_height ) : Shape(), size(t_width, t_height) {}
			void reset();
			void center();
			void create(b2BodyId&);
			void update(const sf::Time&);
			void simulate(const sf::Time&);
			void draw(sf::RenderWindow&);
		public:
			sf::Vector2f		size{20.f,20.f};
			b2Polygon			boundingShape;
			sf::RectangleShape 	visualShape;
	};
};

#endif
