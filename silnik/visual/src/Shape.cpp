#include "Shape.h"

using namespace n2d;

void Shape::SetDensity( float d ) {
	fixture.density = d;
}

void Shape::SetFriction( float f ) {
	fixture.friction = f;
}

void Shape::SetRestitution( float r ) {
	fixture.restitution = r;
}
