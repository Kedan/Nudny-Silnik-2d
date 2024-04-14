#ifndef NUDNY_ENTITY_STATE_H
#define NUDNY_ENTITY_STATE_H

#include "Tools.h"
#include "Interfaces.h"
#include "Entity.h"
#include "State.h"

namespace n2d {
	class EntityState : public State {
		protected:
			Entity*			mp_entity;
			std::vector<Model>	models;
	}; // class	
}; // namespace

#endif
