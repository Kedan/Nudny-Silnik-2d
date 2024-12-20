#ifndef NUDNY_SILNIK_2D_GAME_INTERFACES_HPP
#define NUDNY_SILNIK_2D_GAME_INTERFACES_HPP

#include "core/Interfaces.hpp"

namespace ns {
	namespace itf {
		class GameState : public Stateful, public Pipelined, public Drawable, public Updatable, public Simulated, public Interactive {
		};
	};
};

#endif
