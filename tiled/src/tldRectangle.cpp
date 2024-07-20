#include <tldRectangle.h>

using namespace nudny;

tldRectangle::tldRectangle( tson::Object& t_object ) {
	Load( t_object );
}

bool tldRectangle::Load( tson::Object& t_object ) {
	m_tiled_obj = t_object;
	SetOrigin( m_tiled_obj.getSize().x/2, m_tiled_obj.getSize().y/2 );
	SetRotation( m_tiled_obj.getRotation() );
	SetPosition( m_tiled_obj.getPosition().x + m_tiled_obj.getSize().x/2, m_tiled_obj.getPosition().y + m_tiled_obj.getSize().y/2 );
	SetSize( m_tiled_obj.getSize().x, m_tiled_obj.getSize().y ); 
	return true;	
}
