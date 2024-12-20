#ifndef NUDNY_SILNIK_2D_GAME_HUD_HPP
#define NUDNY_SILNIK_2D_GAME_HUD_HPP

#include "core/Interfaces.hpp"
#include "core/Resources.hpp"
#include "core/Pipeline.hpp"
#include "graph/FontStyle.hpp"
#include "graph/Text.hpp"

namespace ns {
	class Hud :
	public itf::Drawable,
	public itf::Updatable,
	public itf::Interactive {
		public:
			Hud();
			void	setupPipeline();
			void	draw( sf::RenderWindow& );
			void 	update( const sf::Time& );
			void 	handleEvents( const sf::Event& );
		protected:
			sf::View					mView;
			std::shared_ptr<Pipeline>	mPipeline;
			std::shared_ptr<Resources>	mResources;
			std::string					mMsg{"Hello World!"};
			ns::FontStyle 				mFontStyle;
			std::shared_ptr<ns::Text> 	mText;
	};
};

#endif
