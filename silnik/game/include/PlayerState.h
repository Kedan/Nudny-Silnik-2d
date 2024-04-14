/*
 * 
 * Pre-defined Player Ststes:
 *
 * 1. OnAir - abstract
 * 2. OnGround - abstract
 * 3. Idle
 * 4. Walk
 * 5. Run
 * 6. Sprint
 * 7. JumpBegin
 * 8. Jump
 * 9. JumpEnd
 * 10. Crouch
 * 11. CrouchWalk
 * 12. Slide
 * 13. Attack
 * 14. AltAttack
 * 15. Block
 * 16. Hit
 * 17. Die
 * 18. Fall
 * 19. Spell
 *
 */

#ifndef NUDNY_PLAYER_STATE_H
#define NUDNY_PLAYER_STATE_H

#include "Interfaces.h"

namespace n2d {
	class Player;

	class PlayerState {
		public:
			std::string		name = "abstract";
			virtual PlayerState* 	Dispatch( sf::Event&, Player& ) = 0;
			virtual void		Events( sf::Event&, Player& ) = 0;
			virtual void		Enter( Player& ) = 0;
			virtual void		Exit( Player& ) = 0;
	};
	
	class PlayerStateOnAir : public PlayerState {
	};

	class PlayerStateOnGround : public PlayerState {
	};
	
	class PlayerStateIdle : public PlayerStateOnGround {
		public:
			PlayerStateIdle() {
				name = "idle";
			};
			PlayerState* 	Dispatch( sf::Event&, Player& );
			void		Events( sf::Event&, Player& );
			void		Enter( Player& );
			void		Exit( Player& );
	};

	class PlayerStateMove : public PlayerStateOnGround {
		public:
			PlayerStateMove() {
				name = "move";
			}
			PlayerState* 	Dispatch( sf::Event&, Player& );
			void		Events( sf::Event&, Player& );
			void		Enter( Player& );
			void		Exit( Player& );
	};
	
	class PlayerStateCrouch : public PlayerStateOnGround {
		public:
			PlayerStateCrouch() {
				name = "crouch";
			}
			PlayerState*	Dispatch( sf::Event&, Player& );
			void		Events( sf::Event&, Player& );
			void		Enter( Player& );
			void		Exit( Player& );
	};

	class PlayerStateJumpBegin : public PlayerState {
	};

	class PlayerStateJumpEnd : public PlayerState {
	};
}; // namespace n2d

#endif
