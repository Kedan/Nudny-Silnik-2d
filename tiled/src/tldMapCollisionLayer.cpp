#include <tldShapeFactory.h>
#include <tldMapCollisionLayer.h>

using namespace nudny;

bool tldMapCollisionLayer::Load( tson::Layer& t_layer, std::string t_dir ) {
	m_layer = t_layer;
	for( auto object : m_layer.getObjects() ) {
		std::shared_ptr<Shape> tmp = tldShapeFactory::Create( object );
		if( tmp ) {
			m_shapes.push_back( tmp );
			m_body.Add( tmp );
		}
	}
	return m_is_loaded;
}
