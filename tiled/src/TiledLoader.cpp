#include <TiledLoader.h>

using namespace nudny;

TiledLoader::TiledLoader() {
	m_map_loader.SetParser( &m_parser );
}
