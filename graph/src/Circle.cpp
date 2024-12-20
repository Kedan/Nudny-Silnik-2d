#include <graph/Adapter.hpp>
#include <graph/Circle.hpp>

namespace ns {

void Circle::reset() {
	sf.setOrigin( sf::Vector2f( radius+origin.x, radius+origin.y ));
	sf.setRadius( radius );
	sf.setPosition( position );
	sf.setFillColor( color ); 
	b2.center = ns::b2( origin );
	b2.radius = ns::b2( radius );
}

void Circle::center() {
	origin = sf::Vector2f(0.0f, 0.f);
}

void Circle::create(b2BodyId& t_id ) {
	reset();
	id = b2CreateCircleShape( t_id, &def, &b2 );
}

void Circle::update(const sf::Time& t_time ) {
}

void Circle::simulate(const sf::Time& t_time) {
	ns::sync( sf, b2Shape_GetBody(id));
}

void Circle::draw(sf::RenderWindow& t_window) {
	t_window.draw( sf );
}

};
