#ifndef NUDNY_TEXT_H
#define NUDNY_TEXT_H

#include <tileson/tileson.h>
#include <SFML/Graphics/Text.hpp>
#include <Interfaces.h>

namespace n2d {
	class Text : public Drawable, public Updatable {
		protected:
			sf::Font	m_font;
			sf::Text	m_text;
		public:
			Text();
			Text( const tson::Text );
			bool Load( const tson::Text );
			void Update( float );
			void Draw( sf::RenderWindow& );
			void Draw( sf::RenderWindow&, sf::Transform& );

			void SetColor( float, float, float, float );
			void SetColor( glm::vec4 );
			void SetText( std::string );
	}; // class Text
}; // namespace n2d

#endif
