#ifndef NUDNY_SILNIK_2D_CORE_APP_HPP
#define NUDNY_SILNIK_2D_CORE_APP_HPP

#include <string>
#include <memory>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <core/AppConfig.hpp>
#include <core/GameState.hpp>
#include <core/GameStateFactory.hpp>

namespace ns {
	class App {
		public:
			App( const std::string& tConfig, const GameStateFactory& tFactory );
			bool run();
			inline const AppConfig& getConfig() const { return mConfig; }
		protected:
			AppConfig							mConfig;
			bool								mExit{true};
			sf::Time							mTime;
			sf::Clock							mClock;
			sf::RenderWindow					mWindow;
			sf::Event							mEvent;
			const GameStateFactory*				mFactory{nullptr};
			std::unique_ptr<GameState>		mCurrentState{nullptr};
	};
}; // namespace ns

#endif
