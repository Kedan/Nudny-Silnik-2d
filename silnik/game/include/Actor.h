#ifndef NUDNY_ACTOR_H
#define NUDNY_ACTOR_H

#include <iostream>
#include <glm/glm.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Log.h"
#include "Entity.h"

// skonczona maszyna stanow FSM - Finite State Machine
// hierarchiczna maszyna stanow HSM - Hierarchical State Machine

namespace n2d {
	class Actor : public Entity {
		protected:
			float		m_vit;
			float		m_dmg;
			float		m_def;
			float 		m_walk_speed 	= 0.8f; 
			float 		m_run_speed 	= 0.6f;
			float		m_crouch_speed 	= 0.2f;
		public:
			// move state
			// combat state
			// helth state
			// story state ??

//			Inventory		inventory;

			glm::vec2 		move_direction;
			glm::vec2		attack_direction;
			
			Actor();
			void Move();
	}; // class Actor
}; // namespace n2d

#endif
