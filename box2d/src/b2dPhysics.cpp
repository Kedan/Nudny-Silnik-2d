#include <b2dPhysics.h>

using namespace nudny;

b2dPhysics::b2dPhysics() {
}

b2dPhysics::b2dPhysics( float t_x, float t_y ) {
	SetGravity( t_x, t_y );
}

b2dPhysics::b2dPhysics( glm::vec2 t_gravity ) {
	SetGravity( t_gravity );
}

b2dPhysics::~b2dPhysics() {
	b2DestroyWorld( m_world_id );
}

void b2dPhysics::SetGravity( float t_x, float t_y ) {
	m_world_def.gravity = (b2Vec2){ t_x, t_y };
}

void b2dPhysics::SetGravity( glm::vec2 t_gravity ) {
	SetGravity( t_gravity.x, t_gravity.y );
}

glm::vec2 b2dPhysics::GetGravity() {
	return glm::vec2( m_world.GetGravity().x, m_world.GetGravity().y );
}

void b2dPhysics::Init() {
	m_world_id = b2CreateWorld( &m_world_def );
}

void b2dPhysics::Create( Body& t_body ) {
	t_body.m_body_id = b2CreateBody( m_world_id, t_body.m_mody_def );
}

void b2dPhysics::Step() {
	b2World_Step( m_world_id, m_time_step, m_sub_step_count );
}
