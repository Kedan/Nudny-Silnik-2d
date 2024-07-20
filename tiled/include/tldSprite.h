#ifndef NUDNY_SILNIK_2D_TILED_SPRITE_H
#define NUDNY_SILNIK_2D_TILED_SPRITE_H

#include <tileson/tileson.h>
#include <Sprite.h>

namespace nudny {
	class tldSprite : public Sprite {
		public:
			bool Load( tson::Tile&, Resources&, std::string, glm::vec2);
		protected:
			tson::Tile	m_tile;
	}; // class
}; // namespace

#endif
