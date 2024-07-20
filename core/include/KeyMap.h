#ifndef NUDNY_SILNIK_2D_CORE_KEYMAP_H
#define NUDNY_SILNIK_2D_CORE_KEYMAP_H

#include <SFML/Window/Keyboard.hpp>

namespace nudny {
	struct KeyMap {
		int 	APP_CLOSE 		= sf::Keyboard::Key::Escape;
		int	PLAYER_MOVE_FOREWARD 	= -1;
		int	PLAYER_MOVE_BACKWARD	= -1;
		int	PLAYER_MOVE_LEFT	= sf::Keyboard::Key::Left;
		int	PLAYER_MOVE_RIGHT	= sf::Keyboard::Key::Right;
		int	PLAYER_JUMP		= sf::Keyboard::Key::Up;
		int	PLAYER_CROUCH		= sf::Keyboard::Key::Down;
		int	PLAYER_ATTACK		= sf::Keyboard::Key::Space;
	};
};

#endif
