#include <tldCircle.h>

using namespace nudny;

tldCircle::tldCircle( tson::Object& t_object ) {
	Load( t_object );
}

bool tldCircle::Load( tson::Object& t_object ) {
	m_tiled_obj = t_object;
	SetPosition( m_tiled_obj.getPosition().x, m_tiled_obj.getPosition().y );
	SetRadius( (m_tiled_obj.getSize().x+m_tiled_obj.getSize().y )*0.5f );
	return true;
}
