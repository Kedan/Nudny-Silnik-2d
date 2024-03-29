#include "Text.h"

using namespace n2d;

Text::Text() {}

Text::Text( const tson::Text t_text ) {
	Load( t_text );
}

bool Text::Load( const tson::Text t_text ) {
	m_font.loadFromFile( t_text.fontFamily );
	m_text.setFont( m_font );
	m_text.setString( t_text.text );
	m_text.setCharacterSize( t_text.pixelSize );
	m_text.setFillColor( sf::Color( t_text.color.r, t_text.color.g, t_text.color.b, t_text.color.a  ));
	return true;	
}

void Text::Update( float t_dt ) {
}

void Text::Draw( sf::RenderWindow& t_window ) {
	t_window.draw( m_text );
}

void Text::Draw( sf::RenderWindow& t_window, sf::Transform& t_transform ) {
	t_window.draw( m_text, t_transform );
}

void Text::SetColor( float r, float g, float b, float a ) {
	m_text.setFillColor( sf::Color( r, g, b, a ));
}

void Text::SetColor( glm::vec4 t_color ) {
	m_text.setFillColor( sf::Color( t_color[0], t_color[1], t_color[2], t_color[3] ));
}

void Text::SetText( std::string t_text ) {
	m_text.setString( t_text );
}

