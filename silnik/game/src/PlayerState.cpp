#include "Keyboard.h"
#include "PlayerState.h"
#include "Player.h"

using namespace n2d;

/* player idle */

PlayerState* PlayerStateIdle::Dispatch( sf::Event& t_event, Player& t_player ) {
	if( Keyboard::Instance()->WasPressed( sf::Keyboard::Down )) {
		return new PlayerStateCrouch();
	}
	if( Keyboard::Instance()->WasPressed( sf::Keyboard::Left ) || Keyboard::Instance()->WasPressed( sf::Keyboard::Right )) {
		return new PlayerStateMove();
	}
	return nullptr;
}

void PlayerStateIdle::Events( sf::Event& t_event, Player& t_player ) {
	t_player.move_direction.x = 0;
	t_player.SetVelocity( 0 , 0 );
}

void PlayerStateIdle::Enter( Player& t_player ) {
}

void PlayerStateIdle::Exit( Player& t_player ) {
}

/* player move */

PlayerState* PlayerStateMove::Dispatch( sf::Event& t_event, Player& t_player ) {
	if( Keyboard::Instance()->WasPressed( sf::Keyboard::Down )) {
		return new PlayerStateCrouch();
	}
	if( !Keyboard::Instance()->IsHeld( sf::Keyboard::Left ) && !Keyboard::Instance()->IsHeld( sf::Keyboard::Right )) {
		return new PlayerStateIdle();
	}
	return nullptr;
}

void PlayerStateMove::Events( sf::Event& t_event, Player& t_player ) {
	if( Keyboard::Instance()->WasReleased( sf::Keyboard::Left) || Keyboard::Instance()->WasReleased( sf::Keyboard::Right )) {
		t_player.move_direction.x = 0;
	}
	if( Keyboard::Instance()->IsHeld( sf::Keyboard::Left )) {
		t_player.move_direction.x = -1;
	}
	if( Keyboard::Instance()->IsHeld( sf::Keyboard::Right )) {
		t_player.move_direction.x = 1;
	}
	if( Keyboard::Instance()->IsHeld( sf::Keyboard::Left ) && Keyboard::Instance()->IsHeld( sf::Keyboard::Right )) {
		t_player.move_direction.x = 0;
	}
	t_player.Move();
	//t_player.SetVelocity( t_player.move_direction.x, 0 );
}

void PlayerStateMove::Enter( Player& t_player ) {
	for( auto body : t_player.bodies ) {
		//body->GetBodyPtr()->SetFixedRotation( true );
	}
	//t_player.SetType( b2_kinematicBody );	
}

void PlayerStateMove::Exit( Player& t_player ) {
	for( auto body : t_player.bodies ) {
		//body->GetBodyPtr()->SetFixedRotation( false );
	}
	//t_player.SetType(  b2_dynamicBody );
}


/* player crouch */

PlayerState* PlayerStateCrouch::Dispatch( sf::Event& t_event, Player& t_player ) {
	if( Keyboard::Instance()->WasReleased( sf::Keyboard::Down )) {
		if( !Keyboard::Instance()->IsHeld( sf::Keyboard::Left ) && !Keyboard::Instance()->IsHeld( sf::Keyboard::Right )) {
			return new PlayerStateIdle();
		} else {
			return new PlayerStateMove();
		}
	}
	return nullptr;
}

void PlayerStateCrouch::Events( sf::Event& t_event, Player& t_player ) {
	if( t_player.toggle_crouch || Keyboard::Instance()->IsHeld( sf::Keyboard::Down )) {
		if( Keyboard::Instance()->WasReleased( sf::Keyboard::Left) || Keyboard::Instance()->WasReleased( sf::Keyboard::Right )) {
			t_player.move_direction.x = 0;
		}
		if( Keyboard::Instance()->IsHeld( sf::Keyboard::Left )) {
			t_player.move_direction.x = -0.5f;
		}
		if( Keyboard::Instance()->IsHeld( sf::Keyboard::Right )) {
			t_player.move_direction.x = 0.5f;
		}
		if( Keyboard::Instance()->IsHeld( sf::Keyboard::Left ) && Keyboard::Instance()->IsHeld( sf::Keyboard::Right )) {
			t_player.move_direction.x = 1.25f;
		}
	}
}

void PlayerStateCrouch::Enter( Player& t_player ) {
}

void PlayerStateCrouch::Exit( Player& t_player ) {
}
