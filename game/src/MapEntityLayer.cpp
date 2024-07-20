#include <MapEntityLayer.h>

using namespace nudny;

MapEntityLayer::MapEntityLayer() {
}

void MapEntityLayer::Draw( sf::RenderWindow& t_window ) {
	for( auto entity : m_entities ) {
		entity->Draw( t_window );
	}
}

void MapEntityLayer::Draw( sf::RenderWindow& t_window, sf::Transform& t_transform ) {
	for( auto entity : m_entities ) {
		entity->Draw( t_window, t_transform );
	}
}

void MapEntityLayer::Update( sf::Time& t_time ) {
	for( auto entity : m_entities ) {
		entity->Update( t_time );
	}
}

void MapEntityLayer::Events( sf::Event& t_event ) {
	for( auto entity : m_entities ) {
		entity->Events( t_event );
	}
}

void MapEntityLayer::Create( b2World& t_world ) {
	for( auto entity : m_entities ) {
		entity->Create( t_world );
	}
}
