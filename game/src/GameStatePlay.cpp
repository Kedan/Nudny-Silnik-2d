#include <GameStatePlay.h>

using namespace nudny;

void GameStatePlay::Init() {
}

void GameStatePlay::InitPhysics() {
	m_world.SetGravity( m_gravity );
}

void GameStatePlay::Simulate() {
	m_world.Step( m_time_step, m_velocity_iterations, m_position_iterations );
}

void GameStatePlay::Draw( sf::RenderWindow& t_window ) {
	m_queue.Draw( t_window );
}

void GameStatePlay::Draw( sf::RenderWindow& t_window, sf::Transform& t_transform ) {
	m_queue.Draw( t_window, t_transform );
}

void GameStatePlay::Update( sf::Time& t_dt ) {
	m_queue.Update( t_dt );
	m_queue.Animate( t_dt );
}

void GameStatePlay::Events( sf::Event& t_event ) {
	m_queue.Events( t_event );
}
