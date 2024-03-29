#ifndef NUDNY_STATE_FACTORY_H
#define NUDNY_STATE_FACTORY_H

#include "State.h"

namespace n2d {
	class StateFactory {
		public:
			virtual State* Create() = 0;
	}; // class StateFactory
}; // namespace n2d

#endif
