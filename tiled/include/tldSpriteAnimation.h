#ifndef NUDNY_SILNIK_2D_TILED_ANIMATION_H
#define NUDNY_SILNIK_2D_TILED_ANIMATION_H

#include <tileson/tileson.h>
#include <Animation.h>

namespace nudny {
	class tldSpriteAnimation : public SpriteAnimation {
		public:
			bool Load( tson::Animation&, tson::Tileset*, glm::vec2 );
		protected:
			tson::Animation m_tiled_animation;
	}; // class
}; // namespace

#endif
