#include "Log.h"
#include "Resources.h"

using namespace n2d;

Resources::Resources() {
	LOG.Time() << "Resources constructor\n";
	Free();
	textures.ReserveMemory( 50 );

}

Resources::~Resources() {
	Free();
}

void Resources::Free() {
	textures.Free();
	fonts.Free();
	sound_buffers.Free();
	music.Free();
}
