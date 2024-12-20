#ifndef NUNDY_SILNIK_2D_CORE_GAME_STATE_HPP
#define NUNDY_SILNIK_2D_CORE_GAME_STATE_HPP

#include <core/Interfaces.hpp>
#include <core/Pipeline.hpp>
#include <core/Resources.hpp>
#include <core/Camera.hpp>
#include <core/Input.hpp>
#include <functional>

namespace ns {
	
	class GameStateConfig {
		public:
			std::string		name;
			GameStateConfig& operator=(const GameStateConfig&);
			void			load(const int&);
	};
	
	class GameState :
	public ns::itf::Stateful,
   	public ns::itf::Drawable,
	public ns::itf::Updatable,
	public ns::itf::Simulated,
	public ns::itf::Interactive,
	public ns::itf::Pipelined {
		public:
			void enter(){};
			void exit(){};
			virtual std::unique_ptr<GameState> 	dispatch(const sf::Event&) = 0;
		protected:
			GameStateConfig				m_config;
			Pipeline					m_pipeline;
			std::unique_ptr<Resources>	src = std::make_unique<Resources>(Resources());
			std::unique_ptr<Camera>		m_camera;
	};

};

#endif
