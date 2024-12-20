#include <core/Camera.hpp>
#include <core/Config.hpp>

namespace ns {

Camera::Camera() {
	if(Config::getInstance().isLoaded()) {
		m_size.x = Config::getInstance().json()["resolution"][0];
		m_size.y = Config::getInstance().json()["resolution"][1];
		m_position = m_size*0.5f;
	}
	m_view.setCenter(m_position.x, m_position.y);
	m_view.setSize(m_size.x,m_size.y);
}

void Camera::draw(sf::RenderWindow& t_window ) {
	t_window.setView(m_view);
}

void Camera::handleEvents(const sf::Event& t_event ) {
}

void Camera::update(const sf::Time& t_time ) {
	m_view.setCenter(m_position.x, m_position.y);
}

void Camera::lookAt(const float& t_x, const float& t_y ) {
	m_position.x = t_x;
	m_position.y = t_y;
}
	
};
