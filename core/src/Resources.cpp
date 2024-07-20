#include "Resources.h"

using namespace nudny;

Resources::Resources() {
	LOG.Time() << "Resources constructor\n";
	Free();
	textures.ReserveMemory( 50 );

}

Resources::~Resources() {
	LOG.Time() << "Resources destructor\n";
	Free();
}

void Resources::Free() {
	LOG.Time() << "Resources Free()\n";
	textures.Free();
	fonts.Free();
	sounds.Free();
	music.Free();
}
