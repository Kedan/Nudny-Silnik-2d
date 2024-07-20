#include <MapTileLayer.h>

using namespace nudny;

MapTileLayer::MapTileLayer() {
}

void MapTileLayer::Draw( sf::RenderWindow& t_window ) {
	m_body.Draw( t_window );
}

void MapTileLayer::Draw( sf::RenderWindow& t_window, sf::Transform& t_transform ) {
	m_body.Draw( t_window, t_transform );
}

void MapTileLayer::Update( sf::Time& t_time ) {
	m_body.Update( t_time );
}

void MapTileLayer::Events( sf::Event& t_event ) {
}

void MapTileLayer::Create( b2World& t_world ) {
	if( m_is_loaded ) {
		m_body.SetPosition( m_position );
		m_body.Create( t_world );
	}
}
