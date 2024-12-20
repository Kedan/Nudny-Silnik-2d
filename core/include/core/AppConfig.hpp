#ifndef NUDNY_SILNIK_2D_CORE_APP_CONFIG_HPP
#define NUDNY_SILNIK_2D_CORE_APP_CONFIG_HPP

#include <core/Config.hpp>

namespace ns {
	class AppConfig {
		public:
			std::string	name{"Nudny Silnik 2D"};
			float		screenWidth{800};
			float		screenHeight{600};
			float		masterVolume{0.75f};
			float		musicVolume{0.75f};
			float		sfxVolume{0.75f};
			float		fps{60.0f};
			bool		vsync{false};
			bool		fullscreen{false};
			
			bool		load();
			AppConfig& operator=( const AppConfig& );
	};
};

#endif
