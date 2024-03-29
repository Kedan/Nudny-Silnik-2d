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
}; // namespace n2d

#endif
