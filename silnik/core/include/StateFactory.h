#ifndef NUDNY_STATE_FACTORY_H
#define NUDNY_STATE_FACTORY_H

#include "State.h"

namespace n2d {
	/**
	 * Abstract factory. Most basic state factory. Note that IT NOT IMPLEMENT Creatable abstraction. This is something different.
	 */
	class StateFactory {
		public:
			virtual State* Create() = 0;
	}; // class StateFactory
}; // namespace n2d

#endif
