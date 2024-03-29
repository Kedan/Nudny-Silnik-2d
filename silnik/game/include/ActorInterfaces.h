#ifndef NUDNY_MOVABLE_H
#define NUDNY_MOVABLE_H

#include "Actor.h"
#include "Item.h"

namespace n2d {
	class Alive {
		public:
			virtual void Die() = 0;
			virtual void Respawn() = 0;
			virtual void Bleed() = 0;
			virtual void Heal( Actor* t_actor = nullptr ) = 0;
	}; // class alice
	class Movable {
		public:
			virtual void Idle() = 0;
			virtual void Move( glm::vec2 ) = 0;
			virtual void Jump( glm::vec2 ) = 0;
			virtual void Crouch() = 0;
			virtual void Walk() = 0;
			virtual void Run() = 0;
	}; // class Movable
	class Fighting {
		public:
			virtual void Attack() 		= 0;
			virtual void Block()		= 0;
			virtual void AltAttack() 	= 0;
			virtual void TakeDamage()	= 0;
	}; // class Fighting
	class Equipped {
		public:
			virtual void Loot( Item* ) = 0;
			virtual void Loot( std::vector<Item>, float r_radius ) = 0;
			virtual void Take( Item* ) = 0;
			virtual void Take( std::vector<Item> ) = 0;
			virtual void Drop( Item* ) = 0;
			virtual void Drop( void ) = 0;
			virtual void Sell( Actor*, Item*, float ) = 0 ;
			virtual void Buy( Actor*, Item*, float ) = 0;
			virtual void Trade( Actor*, Item*, Item* ) = 0;
	}; // class Equippe
}; // namespace n2d

#endif
