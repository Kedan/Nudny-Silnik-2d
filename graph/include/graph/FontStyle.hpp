#ifndef NUDNY_SILNIK_2D_GRPAH_FONT_STYLE_HPP
#define NUDNY_SILNIK_2D_GRPAH_FONT_STYLE_HPP

namespace ns {
	struct FontStyle {
		sf::Font	font;	
		int			size{14};
		sf::Color	color{255,255,255,255};
		uint32_t	style;
	};
};

#endif
