#include "Shape.h"

using namespace nudny;

Shape::Shape( b2FixtureDef& t_fixture_def ) {
	fixture = t_fixture_def;
}

void Shape::SetSensor( bool t_is_sensor = true ) {
	if( mp_fixture ) {
		mp_fixture->SetSensor( t_is_sensor );
	}
	fixture.isSensor = t_is_sensor;
}

bool Shape::IsSensor() {
	return mp_fixture ? mp_fixture->IsSensor() : fixture.isSensor;
}

