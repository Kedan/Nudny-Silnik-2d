#include <MapDecorationLayer.h>

using namespace nudny;

MapDecorationLayer::MapDecorationLayer() {
}

void MapDecorationLayer::AddTile( std::shared_ptr<Sprite> t_tile ) {
	if( t_tile ) {
		m_tiles.push_back(  t_tile );
		m_queue.drawable.Add( t_tile );
		if( t_tile->IsAniamted() ) {
			m_queue.animated.Add( t_tile );
		}
	}
}

void MapDecorationLayer::Draw( sf::RenderWindow& t_window ) {
	m_queue.Draw( t_window );
}

void MapDecorationLayer::Draw( sf::RenderWindow& t_window ) {
	m_queue.Draw( t_window );
}

void MapDecorationLayer::Update( sf::Time& t_time ) {
	m_queue.Update( t_time );
}

void MapDecorationLayer::Events( sf::Event& t_event ) {
	m_queue.Events( t_event );
}

void MapDecorationLayer::Run( sf::Event& t_event, sf::Time& t_time, sf::RenderWindow& t_window ) {
	m_queue.Run( t_event, t_time, t_window );
}

void MapDecorationLayer::Run( sf::Event& t_event, sf::Time& t_time, sf::RenderWindow& t_window, sf::Transform& t_transform ) {
	m_queue.Run( t_event, t_time, t_window, t_transform );
}

