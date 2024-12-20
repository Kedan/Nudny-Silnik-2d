#include <iostream>
#include "core/Input.hpp"

namespace ns {

std::unique_ptr<Input> Input::m_instance;

std::mutex Input::m_mutex;

Input& Input::getInstance() {
	std::lock_guard<std::mutex> lock(m_mutex);
	if(!m_instance) {
		m_instance.reset(new Input());
	}
	return *m_instance;
}

void Input::reset() {
	m_keyPressed.clear();
	m_keyReleased.clear();
	m_buttonPressed.clear();
	m_buttonReleased.clear();
	m_wheelScrolled.clear();
}

void Input::dispatch( const sf::Event& t_event, const sf::RenderWindow& t_window ) {
	switch( t_event.type ) {
		case sf::Event::MouseMoved:
			m_mousePosition.x = sf::Mouse::getPosition( t_window ).x;
			m_mousePosition.y = sf::Mouse::getPosition( t_window ).y;
			break;
		case sf::Event::KeyPressed:
			down( t_event.key.code );
			break;
		case sf::Event::KeyReleased:
			up( t_event.key.code );
			break;
		case sf::Event::MouseButtonPressed:
			down( t_event.mouseButton.button );
			break;
		case sf::Event::MouseButtonReleased:
			up( t_event.mouseButton.button );
			break;
		case sf::Event::MouseWheelScrolled:
			scroll( t_event.mouseWheelScroll.wheel, t_event.mouseWheelScroll.delta );
			break;
	}
}

void Input::down( const sf::Keyboard::Key& t_key ) {
	m_keyPressed[ t_key ] 	= true;
	m_keyHeld[ t_key ] 		= true;
}

void Input::up( const sf::Keyboard::Key& t_key ) {
	m_keyReleased[ t_key ]	= true;
	m_keyHeld[ t_key ]		= false;
}

void Input::down( const sf::Mouse::Button& t_button ) {
	m_buttonPressed[ t_button ] 	= true;
	m_buttonHeld[ t_button ]		= true;
}

void Input::up( const sf::Mouse::Button& t_button ) {
	m_buttonReleased[ t_button ] 	= true;
	m_buttonHeld[ t_button ]		= false;
}

bool Input::wasPressed( const sf::Keyboard::Key& t_key ) {
	return m_keyPressed[ t_key ];
}

bool Input::wasReleased( const sf::Keyboard::Key& t_key ) {
	return m_keyReleased[ t_key ];
}

bool Input::isHeld( const sf::Keyboard::Key& t_key ) {
	return m_keyHeld[ t_key ];
}

bool Input::wasPressed( const sf::Mouse::Button& t_button ) {
	return m_buttonPressed[ t_button ];
}

bool Input::wasReleased( const sf::Mouse::Button& t_button ) {
	return m_buttonReleased[ t_button ];
}

bool Input::isHeld( const sf::Mouse::Button& t_button ) {
	return m_buttonHeld[ t_button ];
}

bool Input::wasScrolled( const sf::Mouse::Wheel& t_wheel ) {
	return m_wheelScrolled[ t_wheel ] != 0.0f;
}

float Input::getScrollDelta( const sf::Mouse::Wheel& t_wheel ) {
	return m_wheelScrolled[ t_wheel ];
}

int Input::getMouseX() {
	return m_mousePosition.x;
}

int Input::getMouseY() {
	return m_mousePosition.y;
}

glm::vec2 Input::getMousePos() {
	return glm::vec2{m_mousePosition.x, m_mousePosition.y};
}

const sf::Vector2i& Input::getMousePossf() {
	return m_mousePosition;
}

void Input::scroll( const sf::Mouse::Wheel& t_wheel, float t_delta ) {
	m_wheelScrolled[t_wheel] = t_delta;
}

bool 	kp( sf::Keyboard::Key t_k) { return Input::getInstance().wasPressed(t_k); }
bool 	kr( sf::Keyboard::Key t_k) { return Input::getInstance().wasReleased(t_k); }
int		mx() { return ns::Input::getInstance().getMouseX(); }
int		my() { return ns::Input::getInstance().getMouseY(); }

} // namespace ns
