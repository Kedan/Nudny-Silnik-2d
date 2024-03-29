#include "Player.h"

using namespace n2d;

Player::Player() {
//	m_model	= nullptr;
	m_state = new PlayerStateIdle();
}

void Player::Draw( sf::RenderWindow& t_window ) {
	Entity::Draw( t_window );
}

void Player::Draw( sf::RenderWindow& t_window, sf::Transform& t_transform ) {
	Entity::Draw( t_window, t_transform );
}

void Player::Update( float t_dt ) {
	//m_state->Update( *this, t_dt );
	Entity::Update( t_dt );
	//std::cout << "Player update " << move_direction.x << std::endl;
}

void Player::Events( sf::Event& t_event ) {
	PlayerState* player_state = m_state->Dispatch( t_event, *this );
	if( player_state != nullptr ){
		delete m_state;
		m_state = player_state;
	}
	m_state->Events( t_event, *this );
//	switch( t_event.type ) {
//		case sf::Event::KeyPressed:
//			KeyPress( t_event );
//			break;
//		case sf::Event::KeyReleased:
//			KeyRelease( t_event );
//			break;
//	}
}

void Player::KeyPress( sf::Event& t_event ) {
	switch( t_event.key.code ) {
		case sf::Keyboard::Left:
			move_direction = glm::vec2( -1,0);
			break;
		case sf::Keyboard::Right:
			move_direction = glm::vec2( 1, 0);
			break;
	}
}

void Player::KeyRelease( sf::Event& t_event ) {
	move_direction = glm::vec2(0,0);
}
