#include "Kayboard.h"
#include "GameState.h"
#include "Game.h"

using namespace n2d;

GameState* GameState::GetNextGameState() {
	try {
		int next_state_id 		= m_conf["games"][m_id]["next"];
		std::string next_state_class 	= m_conf["games"][ next_state_id ]["class"];
		return mp_factory->Create( next_state_class, m_conf, next_state_id );
	} catch( const std::exception& e ) {
		std::cout << e.what();
	}
}

GameState* GameStateLogo::Dispath( sf::Event& t_ecent ) {
	if( Keyboard::Instance()->WasPressed( sf::Keyboard::Space || IsTimeElapsed() ) {
		return GetNextGameState();
	}
	return nullptr;	
}

bool GameStateLogo::IsTimeElapsed() {
	return false;
}
