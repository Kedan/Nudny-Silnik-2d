#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <core/AppState.hpp>
#include <core/Resources.hpp>
#include <game/Interfaces.hpp>

//#include "game/Camera.hpp"

namespace ns {
	
	class GameStateConfig {
		public:
			std::string		name;
			GameStateConfig& operator=(const GameStateConfig&);
	};
	
	class GameState : public AppState {
		public:
			void enter();
			void exit();
			std::unique_ptr<AppState> dispatch(const sf::Event&);
			void initPipeline();
			void draw(sf::RenderWindow&);
			void update(const sf::Time&);
			void simulate(const sf::Time&);
			void handleEvents(const sf::Event&);

			std::unique_ptr<Resources>	src;
			//std::unique_ptr<Camera>		camera;
		protected:
			GameStateConfig	m_config;
	};
};
