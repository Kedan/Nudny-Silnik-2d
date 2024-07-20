#include <tldMapEntityLayer.h>

using namespace nudny;

bool tldMapEntityLayer::Load( tson::Layer& t_layer, std::string t_dir ) {
	if( mp_factory ) {
		for( auto object : t_layer.getObjects() ) {
			m_entities.push_back( mp_factory->Create( object ));
		}
		m_is_loaded = true;
	}
	return m_is_loaded;
}
