#include "Keyboard.h"
#include "Actor.h"

using namespace n2d;

Actor::Actor() {
};

void Actor::Move() {
	SetVelocity( move_direction.x * m_walk_speed, 0 );
}	







