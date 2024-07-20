#ifndef NUDNY_SILNIK_2D_TILED_TILESET_H
#define NUDNY_SILNIK_2D_TILED_TILESET_H

#include <tileson/tileson.h>
#include <tldUtils.h>
#include <Tileset.h>

namespace nudny {
	class tldTileset : public Tileset {
		public:
			bool Load( tson::Tileset&, Resources&, std::string, glm::vec2 );
		protected:
			tson::Tileset m_tileset;
	}; // class
}; // namespace

#endif
