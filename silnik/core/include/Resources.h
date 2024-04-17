#ifndef NUDNY_RESOURCES_H
#define NUDNY_RESOURCES_H

#include "Resource.h"

namespace n2d {
	/**
	 * Container and manager for any resources: images, audio files, whatever you want..
	 */
	class Resources {
		public:
		
			ResourceSFML<sf::Texture>	textures;
			ResourceSFML<sf::SoundBuffer>	sound_buffers;
			ResourceSFML<sf::Font>		fonts;
			ResourceSFMLMusic		music;
			
			/**
			 * Default constructor 
			 */
			Resources();

			/**
			 * Default destructor
			 */
			~Resources();
			
			/**
			 * Free all assets
			 */
			void Free();	
	}; // class Resources
}; // namespace n2d

#endif
