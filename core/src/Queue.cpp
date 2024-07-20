#include <Queue.h>

using namespace nudny;

Queue::Queue() {
	Clear();
}

void Queue::Draw( sf::RenderWindow& t_window ) {
	for( auto o : drawable.m_queue ) {
		o->Draw( t_window );
	}
}

void Queue::Draw( sf::RenderWindow& t_window, sf::Transform& t_transform ) {
	for( auto o : drawable.m_queue ) {
		o->Draw( t_window, t_transform );
	}
}

void Queue::Update( sf::Time& t_time ) {
	for( auto o : updatable.m_queue ) {
		o->Update( t_time );
	}
}

void Queue::Events( sf::Event& t_event ) {
	for( auto o : interactive.m_queue ) {
		o->Events( t_event );
	}
}

void Queue::Create( b2World& t_world ) {
	for( auto o : creatable.m_queue ) {
		o->Create( t_world );
	}
}

void Queue::Animate( sf::Time& t_time ) {
	for( auto o : animated.m_queue ) {
		o->Animate( t_time );
	}
}

void Queue::Run( sf::Event& t_event, sf::Time& t_time, sf::RenderWindow& t_window ) {
	Events( t_event );
	Update( t_time );
	Draw( t_window );
}

void Queue::Run( sf::Event& t_event, sf::Time& t_time, sf::RenderWindow& t_window, sf::Transform& t_transform ) {
	Events( t_event );
	Update( t_time );
	Draw( t_window, t_transform );
}

void Queue::Clear() {
	creatable.m_queue.clear();
	drawable.m_queue.clear();
	animated.m_queue.clear();
	updatable.m_queue.clear();
	interactive.m_queue.clear();
}
