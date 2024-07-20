#ifndef NUDNY_SILNIK_2D_CORE_KEYBOARD_H
#define NUDNY_SILNIK_2D_CORE_KEYBOARD_H

#include <map>
#include <mutex>
#include <memory>
#include <SFML/Window.hpp>
#include <SFML/Window/Keyboard.hpp>
#include "KeyMap.h"

namespace nudny {
	class Keyboard {
		private:
			static std::unique_ptr<Keyboard>	m_instance;
			static std::mutex			m_mutex;
			std::map<sf::Keyboard::Key,bool> 	m_held_keys;
			std::map<sf::Keyboard::Key,bool> 	m_pressed_keys;
			std::map<sf::Keyboard::Key,bool> 	m_released_keys;

			Keyboard(){}
		public:
			Keyboard( const Keyboard& ) = delete;
			Keyboard& operator=(const Keyboard&) = delete;
			static Keyboard& Instance();
			void Clear();
			void Dispatch( sf::Event& );
			void KeyUp( sf::Keyboard::Key );
			void KeyDown( sf::Keyboard::Key );
			bool WasPressed( sf::Keyboard::Key );
			bool WasReleased( sf::Keyboard::Key );
			bool IsHeld( sf::Keyboard::Key );
	};
};

#endif
