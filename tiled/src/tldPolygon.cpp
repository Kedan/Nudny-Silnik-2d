#include <tldPolygon.h>

using namespace nudny;

tldPolygon::tldPolygon( tson::Object& t_object ) {
	Load( t_object );
}

bool tldPolygon::Load( tson::Object& t_object ) {
	m_tiled_obj =  t_object;
	
	glm::vec2 geometry_half_size 		= glm::vec2(	m_tiled_obj.getSize().x*0.5f,	m_tiled_obj.getSize().y*0.5f	);
	glm::vec2 geometry_position_offset 	= glm::vec2( 	m_tiled_obj.getPosition().x,	m_tiled_obj.getPosition().y	);

	SetVertices( LoadGeometry( m_tiled_obj, geometry_half_size, geometry_position_offset ));
	SetPosition( m_tiled_obj.getPosition().x, m_tiled_obj.getPosition().y );
	SetRotation( m_tiled_obj.getRotation() );
	return true;
}

std::vector<glm::vec2> tldPolygon::LoadGeometry( tson::Object& t_obj, glm::vec2 t_half_size, glm::vec2 t_position_offset ) {	
	std::vector<glm::vec2> vertices;
	glm::vec2 p( t_obj.getPosition().x, t_obj.getPosition().y );
	glm::vec2 s( t_obj.getSize().x, t_obj.getSize().y );
	for( auto v : t_obj.getPolygons() ) {
		vertices.push_back( glm::vec2( v.x-t_half_size.x+t_position_offset.x, v.y-t_half_size.y+t_position_offset.y ));
	}
	return vertices;
}
