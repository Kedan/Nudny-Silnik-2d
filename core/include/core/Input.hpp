#ifndef NUDNY_SILNIK_2D_CORE_INPUT_HPP
#define NUDNY_SILNIK_2D_CORE_INPUT_HPP

#include <memory>
#include <map>
#include <glm/vec2.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

namespace ns {
	class Input {
		private:
			static std::unique_ptr<Input>		m_instance;
			static std::mutex					m_mutex;

			std::map<sf::Keyboard::Key,bool>	m_keyPressed;
			std::map<sf::Keyboard::Key,bool>	m_keyReleased;
			std::map<sf::Keyboard::Key,bool>	m_keyHeld;

			std::map<sf::Mouse::Button,bool>	m_buttonPressed;
			std::map<sf::Mouse::Button,bool>	m_buttonReleased;
			std::map<sf::Mouse::Button,bool>	m_buttonHeld;

			std::map<sf::Mouse::Wheel,float>	m_wheelScrolled;
			
			sf::Vector2i						m_resetPoint;
			sf::Vector2i						m_mousePosition;
			
			Input(){};
		public:
			Input( const Input& ) = delete;
			Input& operator=( const Input& ) = delete;

			static Input&		getInstance();
			void				reset();
			void				dispatch( const sf::Event&, const sf::RenderWindow& );
			void				up( const sf::Keyboard::Key& );
			void				up( const sf::Mouse::Button& );
			void				up( const sf::Mouse::Wheel&, float );
			void 				down( const sf::Keyboard::Key& );
			void				down( const sf::Mouse::Button& );
			void				down( const sf::Mouse::Wheel&, float );
			bool				wasPressed( const sf::Keyboard::Key& );
			bool				wasPressed( const sf::Mouse::Button& );
			bool				wasReleased( const sf::Keyboard::Key& );
			bool				wasReleased( const sf::Mouse::Button& );
			bool				wasScrolled( const sf::Mouse::Wheel& );
			bool				isHeld( const sf::Keyboard::Key& );
			bool				isHeld( const sf::Mouse::Button& );
			void				scroll( const sf::Mouse::Wheel&, float tDelta );
			float				getScrollDelta( const sf::Mouse::Wheel& );
			int					getMouseX();
			int					getMouseY();
			glm::vec2			getMousePos();
			const sf::Vector2i&	getMousePossf();
	};

	bool 	kp( sf::Keyboard::Key t_k);
	bool 	kr( sf::Keyboard::Key t_k);
	int		mx();
	int		my();

};

#endif
