#include "game/GameState.hpp"

namespace ns {
	
void GameState::enter() {
}

void GameState::exit() {
}

std::unique_ptr<GameState> dispatch(const sf::Event& t_event) {
	return nullptr;
}

void GameState::initPipeline() {
}

void GameState::draw(sf::RenderWindow& t_window)  {
}

void GameState::update(const sf::Time& t_time) {
}

void GameState::simulate(const sf::Time& t_time) {
}

void GameState::handleEvents(const sf::Event& t_event) {
}

}; // namespace ns
