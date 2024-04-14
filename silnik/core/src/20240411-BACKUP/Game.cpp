#include "Game.h"

using namespace n2d;

Game::Game() {}

void Game::Reset() {
	// load first state of the game
}

void Game::Load( json& t_conf ) {
	mp_conf = &t_conf;
}

void Game::Draw( sf::RenderWindow& t_window ) {
	mp_state->Draw( t_window );
}

void Game::Update( float t_dt ) {
	mp_state->Update( t_dt );
}

void Game::Create() {
	mp_state->Create();
}

void Game::Events( sf::Event& t_event ) {
	std::unique_ptr<Game> state = std::make_unique<Game>( mp_state->Dispath( t_event  ));
	if( state != nullptr ) {
		mp_state->Exit();
		mp_state = std::move( state );
		mp_state->Enter();
	}
	mp_state->Events( t_event );
}
