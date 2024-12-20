#include <graph/Adapter.hpp>
#include <game/Body.hpp>

namespace ns {
	Body::Body() {
		def = b2DefaultBodyDef();
		def.type = b2_dynamicBody;
	}

	void Body::add(std::unique_ptr<Shape> t_shape) {
		shapes.push_back(std::move(t_shape));
	}

	void Body::create(b2WorldId& t_world) {
		def.position = ns::b2( position );
		def.rotation = b2MakeRot(glm::radians(rotation));
		id = b2CreateBody( t_world, &def );
		for(auto& s : shapes ) {
			s->position = position;
			s->rotation = rotation;
			s->create(id);	
		}
	}
	
//	void Body::create(Physic t_world) {
//		def.position = ns::b2( position );
//		def.rotation = b2MakeRot(glm::radians(rotation));
//		id = b2CreateBody( t_world.id, &def );
//		for(auto& s : shapes ) {
//			s->position = position;
//			s->rotation = rotation;
//			s->create(id);	
//		}
//	}

	void Body::update(const sf::Time& t_time) {
	}

	void Body::simulate(const sf::Time& t_time) {
		for(auto& s : shapes) {
			s->simulate(t_time);
		}
	}

	void Body::draw(sf::RenderWindow& t_window) {
		for(auto& s : shapes ) {
			s->draw(t_window);
		}
	}
};
