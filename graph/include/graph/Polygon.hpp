#ifndef NUDNY_SILNIK_2D_GRAPH_POLYGON_HPP
#define NUDNY_SILNIK_2D_GRAPH_POLYGON_HPP

#include <graph/Shape.hpp>

namespace ns {
	class Polygon : public Shape {
		public:
			Polygon() : Shape() {}
			Polygon(std::vector<sf::Vector2f> t_vertices) : Shape(), vertices(t_vertices) {}
			void reset();
			void center();
			void create(b2BodyId&);
			void update(const sf::Time&);
			void simulate(const sf::Time&);
			void draw(sf::RenderWindow&);
		public:
			std::vector<sf::Vector2f>	vertices;
			b2Polygon					boundingShape;
			sf::ConvexShape				visualShape;
	};
};

#endif
