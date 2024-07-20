#include <MapCollisionLayer.h>

using namespace nudny;

MapCollisionLayer::MapCollisionLayer() {
}

void MapCollisionLayer::Draw( sf::RenderWindow& t_window ) {
	m_queue.Draw( t_window );
}

void MapCollisionLayer::Draw( sf::RenderWindow& t_window, sf::Transform& t_transform ) {
	m_queue.Draw( t_window, t_transform );
}

void MapCollisionLayer::Update( sf::Time& t_time ) {
	m_queue.Update( t_time );
}

void MapCollisionLayer::Create( b2World& t_world ) {
	m_queue.Create( t_world );
}

void MapCollisionLayer::Events( sf::Event& t_event ) {
	m_queue.Events( t_event );
}
