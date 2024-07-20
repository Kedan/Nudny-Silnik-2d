#include <tldEntityFactory.h>

using namespace nudny;

tldEntityFactory::tldEntityFactory() {
}

std::shared_ptr<Entity> tldEntityFactory::Create() {
	return Create( *m_object.get() );
}

void tldEntityFactory::Clear() {
	m_object.reset();
}
