#ifndef NUDNY_KEYBOARD_H
#define NUDNY_KEYBOARD_H

#include <map>
#include <mutex>
#include <SFML/Window.hpp>
#include <SFML/Window/Keyboard.hpp>
#include "KeyMap.h"

namespace n2d {
	class Keyboard {
		private:
			static Keyboard*			m_instance;
			static std::mutex			m_mutex;
			std::map<sf::Keyboard::Key,bool> 	m_held_keys;
			std::map<sf::Keyboard::Key,bool> 	m_pressed_keys;
			std::map<sf::Keyboard::Key,bool> 	m_released_keys;
		public:
			static Keyboard* Instance();

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
