#ifndef NUDNY_RESOURCES_H
#define NUDNY_RESOURCES_H

#include <iostream>
#include <mutex>
#include <vector>
#include <map>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "box2d/box2d.h"
#include "tileson/tileson.h"
#include "JSONLoader.h"
#include "Log.h"

#include "Resource.h"

namespace n2d {
	/**
	 * Container and manager for any resources: images, audio files, whatever you want..
	 */
	class Resources {
		protected:
		//	std::vector<sf::Font>		m_fonts;
		//	std::map<std::string,int> 	m_fontNames;
		//	
		//	/** Textures container */
		//	std::vector<sf::Texture>	m_textures;
		//	/** Keep texture name - ID pairs */
		//	std::map<std::string,int>	m_textureNames;

		//	std::vector<std::shared_ptr<sf::Music>>	m_music;
		//	std::map<std::string,int>	m_musicNames;

		//	std::vector<sf::SoundBuffer>	m_sound_buffers;
		//	std::map<std::string,int>	m_sound_map;

		public:
		//	ResourceSFMLTexture		textures;
		//	ResourceSFMLMusic		music;
		//	ResourceSFMLSeoundBuffer	sound_buffer;
			
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
//			
//			/**
//			 * Load texture.
//			 * @param	- path to image
//			 * @return	- created texture id. Returns -1 when loading failed.
//			 */
//			int			LoadTexture( std::string );
//
//			/**
//			 * Return true if image already loaded 
//			 * @param	- path to image
//			 * @return	- (bool)
//			 */
//			bool			IsTextureLoaded( std::string );
//
//			/**
//			 * Returns texture ID if you pass path to image.
//			 * @param	- path to image
//			 * @return	- texture ID. Returns -1 if image not loaded.
//			 */
//			int 			GetTextureId( std::string );
//		
//			/**
//			 * Returns pointer to texture
//			 * @param	- path to image
//			 */
//			sf::Texture*		GetTexturePtr( std::string );
//
//			/**
//			 * Returns texture pointer
//			 * @param	- texture ID
//			 */
//			sf::Texture* 		GetTexturePtr( int );
//
//			/**
//			 * Returns texure reference by ID. 
//			 * Texture reference is used by SFML Sprites.
//			 * @param	- texture ID
//			 * @return	- texture reference
//			 */
//			const sf::Texture&	GetTexture( int );
//			
//			/**
//			 * Returns texure reference by image path. 
//			 * Texture reference is used by SFML Sprites.
//			 * @param	- image path
//			 * @return	- texture reference
//			 */
//		       	const sf::Texture&	GetTexture( std::string );
//
//			/**
//			 * To delete?
//			 */
//			sf::Texture&		GetTextureRef( int );
//
//			/**
//			 * Load music. Music is different than sound. Music is lika stream, sound is from buffer. Check SFML documentation.
//			 * @param	- path to file
//			 * @return	- created music id. Returns -1 when loading failed.
//			 */
//			int			LoadMusic( std::string );
//			
//			/**
//			 * Returns music ID if you pass path to file.
//			 * @param	- path to file
//			 * @return	- texture ID. Returns -1 if image not loaded.
//			 */
//			int 			GetMusicId( std::string );
//
//			/**
//			 * Return true if music already loaded 
//			 * @param	- path to music file
//			 * @return	- (bool)
//			 */
//			bool			IsMusicLoaded( std::string );
//			
//			/**
//			 * Returns music by ID. 
//			 * @param	- music ID
//			 * @return	- music reference
//			 */
//			std::shared_ptr<sf::Music>	GetMusic( int t_id );
//
//			/**
//			 * Returns music by file path. 
//			 * @param	- relative music path
//			 * @return	- music reference
//			 */
//			std::shared_ptr<sf::Music>	GetMusic( std::string t_filepath );
//			
//			int			LoadSound( std::string );
//			int			GetSoundId( std::string );
//			bool			IsSoundLoaded( std::string );
//			sf::SoundBuffer		GetSoundBuffer( int );
//			sf::SoundBuffer		GetSoundBuffer( std::string );
//			
//			int			LoadFont( std::string );
//			bool			IsFontLoaded( std::string );
//			int			GetFontId( std::string );
//			sf::Font*		GetFontPtr( std::string );
//			sf::Font*		GetFontPtr( int );
//			sf::Font		GetFont( std::string );
//			sf::Font		GetFont( int );
//			sf::Font&		GetFontRef( int );
//			
//			/**
//			 * Free all assets
//			 */
			void 			Free();	
	}; // class Resources
}; // namespace n2d

#endif
