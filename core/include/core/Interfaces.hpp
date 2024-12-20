#ifndef NUDNY_SILNIK_2D_CORE_INTERFACES_HPP
#define NUDNY_SILNIK_2D_CORE_INTERFACES_HPP

#include <memory>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

namespace ns {
	namespace itf {
		class Drawable {
			public:
				virtual void draw(sf::RenderWindow&)=0;
		};
		class Updatable {
			public:
				virtual void update(const sf::Time&)=0;
		};
		class Simulated {
			public:
				virtual void simulate(const sf::Time&)=0;
		};
		class Interactive {
			public:
				virtual void handleEvents([[maybe_unused]] const sf::Event&)=0;
		};
		class Pipelined {
			public:
				virtual void initPipeline()=0;
		};
		class Stateful {
			public:
				virtual void enter()=0;
				virtual void exit()=0;
		};
		class Factory {
			public:
				virtual std::unique_ptr<Stateful> create(const int&)=0;
		};
	};
};

#endif
