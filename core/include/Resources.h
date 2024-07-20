#ifndef NUDNY_SILNIK_2D_CORE_RESOURCES_H
#define NUDNY_SILNIK_2D_CORE_RESOURCES_H

#include "Resource.h"

namespace nudny {
	class Resources {
		public:
		
			ResourceSFML<sf::Texture>	textures;
			ResourceSFML<sf::SoundBuffer>	sounds;
			ResourceSFML<sf::Font>		fonts;
			ResourceSFMLMusic		music;
			
			Resources();
			~Resources();
			void Free();	
	}; // class Resources
}; // namespace n2d

#endif
