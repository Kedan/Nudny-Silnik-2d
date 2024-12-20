#include <graph/Adapter.hpp>
#include <graph/Rectangle.hpp>

namespace ns {

	void Rectangle::reset() {
		visualShape.setSize( size );
		visualShape.setOrigin( origin );
		visualShape.setPosition( position );
		visualShape.setRotation( rotation );
		visualShape.setFillColor( color );

		boundingShape = ns::b2( visualShape );
	}

	void Rectangle::center() {
		origin = sf::Vector2f( size.x/2, size.y/2 );
	}

	void Rectangle::create(b2BodyId& t_body) {
		reset();
		id = b2CreatePolygonShape( t_body, &def, &boundingShape );
	}

	void Rectangle::update(const sf::Time& t_time) {

	}

	void Rectangle::simulate(const sf::Time& t_time) {
		ns::sync( visualShape, b2Shape_GetBody(id));
	}

	void Rectangle::draw(sf::RenderWindow& t_window) {
		t_window.draw(visualShape);
	}

};
