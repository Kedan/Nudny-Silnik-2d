#include <Tool.h>


std::vector<glm::vec2> nudny::FlipVerticesHorizontal( std::vector<glm::vec2> t_vertices, float t_mirror = 0.0f ) {
	std::vector<glm::vec2> result;
	for( auto v : t_vertices ) {
		result.push_back( glm::vec2( t_mirror-v.x, v.y ));
	}
	return result;
}

std::vector<glm::vec2> nudny::FlipVerticesVertical( std::vector<glm::vec2> t_vertices, float t_mirror = 0.0f ) {
	std::vector<glm::vec2> result;
	for( auto v : t_vertices ) {
		result.push_back( glm::vec2( v.x, t_mirror - v.y));
	}
	return result;
}

std::vector<glm::vec2> nudny::FlipVerticesDiagonal( std::vector<glm::vec2> t_vertices, glm::vec2 t_mirror = glm::vec2( 0.0f, 0.0f ) ) {
	std::vector<glm::vec2> result;
	for( auto v : t_vertices ) {
		result.push_back( glm::vec2( t_mirror.x - v.x, t_mirror.y - v.y));
	}
	return result;
}
