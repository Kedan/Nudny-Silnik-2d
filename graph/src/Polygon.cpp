#include <graph/Adapter.hpp>
#include <graph/Polygon.hpp>

namespace ns {
	
	void Polygon::reset() {
		visualShape.setPointCount(static_cast<std::size_t>(vertices.size()));
		for(int i=0; i<vertices.size();++i ) {
			visualShape.setPoint(i,vertices[i]);
		}
		visualShape.setOrigin( origin );
		visualShape.setPosition( position );
		visualShape.setRotation( rotation );
		visualShape.setFillColor( color );

		boundingShape = ns::b2( visualShape );
	}
	
	void Polygon::center() {
	}

	void Polygon::create(b2BodyId& t_body) {
		reset();
		id = b2CreatePolygonShape( t_body, &def, &boundingShape );
	}

	void Polygon::update(const sf::Time& t_time) {

	}

	void Polygon::simulate(const sf::Time& t_time) {
		ns::sync( visualShape, b2Shape_GetBody(id));
	}

	void Polygon::draw(sf::RenderWindow& t_window) {
		t_window.draw(visualShape);
	}

};
