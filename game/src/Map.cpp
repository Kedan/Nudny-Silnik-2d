#include <Map.h>

using namespace nudny;

Map::Map() {
	LOG.Time() << "Map construct\n";
}

Map::Map( std::string t_file ) {
	LOG.Time() << "Map construct\n";
}

Map::~Map() {
	LOG.Time() << "Map destruct\n";
}

void Map::SetGridSize( glm::vec2 t_size ) {
	m_grid_size = t_size;
}

glm::vec2 Map::GetGridSize() {
	return m_grid_size;
}

float Map::GetGridWidth() {
	return m_grid_size.x;
}

float Map::GetGridHeight() {
	return m_grid_size.y;
}

void Map::Draw( sf::RenderWindow& t_window ) {
}

void Map::Draw( sf::RenderWindow& t_window, sf::Transform& t_transform ) {
}

void Map::Create( b2World& t_world ) {
}

void Map::Update( sf::Time& t_dt ) { 
}

void Map::Events( sf::Event& t_event ) {
}
