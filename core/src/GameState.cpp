#include <core/GameState.hpp>
#include <core/Input.hpp>

//namespace ns {
//
//std::unique_ptr<GameState> GameState::dispatch(const sf::Event& t_event) {
//	if( Input::getInstance().wasPressed( sf::Keyboard::P )) {
//		return std::make_unique<GameState>(GameState());
//	}
//	return nullptr;
//}
//
//void GameState::enter() {
//	std::cout << "ns::GameState enter" << this << std::endl;
//}
//
//void GameState::exit() {
//	std::cout << "ns::GameState exit" << this << std::endl;
//}
//
//void GameState::initPipeline() {
//}
//
//void GameState::draw(sf::RenderWindow& t_window ) {
//}
//
//void GameState::update(const sf::Time& t_time) {
//}
//
//void GameState::simulate(const sf::Time& t_time) {
//}
//
//void GameState::handleEvents(const sf::Event& t_event) {
//}
//
//};
