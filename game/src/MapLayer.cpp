#include <MapLayer.h> 

using namespace nudny;

MapLayer::MapLayer() {
}

int MapLayer::GetId() {
	return m_id;
}

std::string MapLayer::GetName() {
	return m_name;
}

bool MapLayer::IsVisible() {
	return m_visible;
}

glm::vec2 MapLayer::GetPosition() {
	return m_position;
}

float MapLayer::GetX() {
	return m_position.x;
}

float MapLayer::GetY() {
	return m_position.y;
}

glm::vec2 MapLayer::GetGridSize() {
	return m_grid_size;
}

float MapLayer::GetGridWidth() {
	return m_grid_size.x;
}

float MapLayer::GetGridHeight() {
	return m_grid_size.y;
}

void MapLayer::SetPosition( float t_x, float t_y ) {
	m_position.x = t_x;
	m_position.y = t_y;
}

void MapLayer::SetPosition( glm::vec2 t_position ) {
	m_position = t_position;
}

void MapLayer::SetVisible( bool t_visible ) {
	m_visible = t_visible;
}
 
void MapLayer::SetGridSize( float t_w, float t_h ) {
	m_grid_size.x = t_w;
	m_grid_size.y = t_h;
}

void MapLayer::SetGridSize( glm::vec2 t_size ) {
	m_grid_size = t_size;
}

void MapLayer::Draw( sf::RenderWindow& t_window ) {
}

void MapLayer::Draw( sf::RenderWindow& t_window, sf::Transform& t_transform ) {
}

void MapLayer::Update( sf::Time& t_time ) {
}

void MapLayer::Events( sf::Event& t_event ) {
}
