#include <game/Physic.hpp>

namespace ns {
	Physic::Physic(float x=0.0f, float y=10.0f ) {
		def = b2DefaultWorldDef();
		def.gravity = b2Vec2(x,y);
		id = b2CreateWorld( &def );
	}

	Physic::~Physic() {
		b2DestroyWorld(id);
	}
	void Physic::run() {
		b2World_Step( id, time, step );
	}
};
