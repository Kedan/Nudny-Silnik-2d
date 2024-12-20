#ifndef NUDNY_SILNIK_2D_GRAPH_TEXT_HPP
#define NUDNY_SILNIK_2D_GRAPH_TEXT_HPP

#include <SFML/Graphics/Text.hpp>
#include <core/Interfaces.hpp>
#include <graph/FontStyle.hpp>

namespace ns {
	class Text : public itf::Drawable, public sf::Text {
		public:
			void draw( sf::RenderWindow& tWindow );
			void print(const std::string& );
			void setStyle( const FontStyle& );
	};
};

#endif
