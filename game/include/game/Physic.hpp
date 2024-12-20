#ifndef NUDNY_SILNIK_2D_GAME_PHYSIC_HPP
#define NUDNY_SILNIK_2D_GAME_PHYSIC_HPP

#include <box2d/box2d.h>

namespace ns {
	class Physic {
		public:
			Physic(float, float);
			~Physic();
			void run();
		public:
			float		time{1.0f/60.f};
			int			step{4};
			b2WorldDef 	def;
			b2WorldId	id;
		private:
			Physic(const Physic&) = delete;
			Physic(const Physic&&) = delete;

	};
};

#endif
