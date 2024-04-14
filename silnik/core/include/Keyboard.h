#ifndef NUDNY_KEYBOARD_H
#define NUDNY_KEYBOARD_H

#include <map>
#include <mutex>
#include <SFML/Window.hpp>
#include <SFML/Window/Keyboard.hpp>
#include "KeyMap.h"

namespace n2d {
	/**
	 * Singleton.
	 * Responsible for recording keyboard events.
	 */
	class Keyboard {
		private:

			static Keyboard*			m_instance;
			static std::mutex			m_mutex;
			std::map<sf::Keyboard::Key,bool> 	m_held_keys;
			std::map<sf::Keyboard::Key,bool> 	m_pressed_keys;
			std::map<sf::Keyboard::Key,bool> 	m_released_keys;
		public:
			/**
			 * Singleton. Return n2d::Keyboard class instance
			 */
			static Keyboard* Instance();


			/**
			 * Clear all key state. Resetting mehod called every new frame.
			 */
			void Clear();

			/**
			 * Handle events.
			 * @param	- event reference
			 */
			void Dispatch( sf::Event& );

			/**
			 * Register key up event, and save key code.
			 * @param	- key code
			 */
			void KeyUp( sf::Keyboard::Key );

			/** 
			 * Register key down event, and save key code.
			 * @param	- key code
			 */
			void KeyDown( sf::Keyboard::Key );

			/**
			 * Return true if key was pressed.
			 * @param	- key code
			 */
			bool WasPressed( sf::Keyboard::Key );

			/**
			 * Return true if key was released.
			 * @param	- key code
			 */
			bool WasReleased( sf::Keyboard::Key );

			/**
			 * Return true of key is held for some time
			 * @param	- key code
			 */
			bool IsHeld( sf::Keyboard::Key );
	};
};

#endif
