#include "Keyboard.h"

using namespace n2d;

Keyboard* Keyboard::m_instance{nullptr};

std::mutex Keyboard::m_mutex;

Keyboard* Keyboard::Instance() {
	std::lock_guard<std::mutex> lock( m_mutex );
	if( m_instance == nullptr ) {
		m_instance = new Keyboard();
	}
	return m_instance;
}

void Keyboard::Clear() {
	m_pressed_keys.clear();
	m_released_keys.clear();
}

void Keyboard::Dispatch( sf::Event& t_event ) {
	if( t_event.type == sf::Event::KeyPressed ) {
		KeyDown( t_event.key.code );
	}
	if( t_event.type == sf::Event::KeyReleased ) {
		KeyUp( t_event.key.code );
	}
}

void Keyboard::KeyUp( sf::Keyboard::Key t_key ) {
	m_released_keys[ t_key ] 	= true;
	m_held_keys[ t_key ]		= false;
}

void Keyboard::KeyDown( sf::Keyboard::Key t_key ) {
	m_pressed_keys[ t_key ]		= true;
	m_held_keys[ t_key ]		= true;
}

bool Keyboard::WasPressed( sf::Keyboard::Key t_key ) {
	return m_pressed_keys[ t_key ];
}

bool Keyboard::WasReleased( sf::Keyboard::Key t_key ) {
	return m_released_keys[ t_key ];
}

bool Keyboard::IsHeld( sf::Keyboard::Key t_key ) {
	return m_held_keys[ t_key ];
}
