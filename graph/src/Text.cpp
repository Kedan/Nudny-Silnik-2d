#include <graph/Text.hpp>

void ns::Text::draw( sf::RenderWindow& tWindow ) {
	tWindow.draw( *this );
}

void ns::Text::print(const std::string& tString ) {
	setString( sf::String(tString) );
}

void ns::Text::setStyle( const ns::FontStyle& tStyle ) {
	sf::Text::setFont( tStyle.font );
	sf::Text::setCharacterSize( tStyle.size );
	sf::Text::setFillColor( tStyle.color );
	sf::Text::setStyle( tStyle.style );
}
