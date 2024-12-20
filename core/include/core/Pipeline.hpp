#ifndef NUDNY_SINLIN_2D_CORE_PIPELINE_HPP
#define NUDNY_SINLIN_2D_CORE_PIPELINE_HPP

#include <iostream>
#include <memory>
#include <functional>
#include <type_traits>
#include <core/Interfaces.hpp>
#include <core/CallbackQueue.hpp>

namespace ns {
	class Pipeline {
		public:
			std::unique_ptr<CallbackQueue<itf::Drawable, sf::RenderWindow&>>	draw{new CallbackQueue<itf::Drawable,sf::RenderWindow&>(&itf::Drawable::draw)};
			std::unique_ptr<CallbackQueue<itf::Updatable,const sf::Time&>>		update{new CallbackQueue<itf::Updatable,const sf::Time&>(&itf::Updatable::update)};
			std::unique_ptr<CallbackQueue<itf::Interactive,const sf::Event&>>	interactive{new CallbackQueue<itf::Interactive,const sf::Event&>(&itf::Interactive::handleEvents)};
			std::unique_ptr<CallbackQueue<itf::Simulated,const sf::Time&>>		simulate{ new CallbackQueue<itf::Simulated,const sf::Time&>(&itf::Simulated::simulate)};

			template<typename T>
			void operator+=(std::shared_ptr<T> obj) {
				if constexpr (std::is_same<T,itf::Drawable>::value) {
					std::cout << "ns::Pipeine::operator+= - Drawable pushed.\n"; 
					draw->push(std::static_pointer_cast<itf::Drawable>(obj));
				}
				if constexpr (std::is_same<T,itf::Updatable>::value) {
					update->push(std::static_pointer_cast<itf::Updatable>(obj));
				}
				if constexpr (std::is_same<T,itf::Interactive>::value) {
					interactive->push(std::static_pointer_cast<itf::Interactive>(obj));
				}
				if constexpr (std::is_same<T,itf::Simulated>::value) {
					simulate->push(std::static_pointer_cast<itf::Simulated>(obj));
				}
			}
	};
}; // namespace ns

#endif
