#ifndef NUDNY_RESOURCES_H
#define NUDNY_RESOURCES_H

#include <iostream>
#include <mutex>
#include <vector>
#include <map>
#include <SFML/Graphics.hpp>
#include "box2d/box2d.h"
#include "tileson/tileson.h"
#include "JSONLoader.h"

namespace n2d {
	class Resources {
		protected:
			std::vector<sf::Font>		m_fonts;
			std::map<std::string,int> 	m_fontNames;
			
			std::vector<sf::Texture>	m_textures;
			std::map<std::string,int>	m_textureNames;
		public:
			Resources();

			int			LoadTexture( std::string );
			bool			IsTextureLoaded( std::string );
			int 			GetTextureId( std::string );
			sf::Texture*		GetTexturePtr( std::string );
			sf::Texture* 		GetTexturePtr( int );
			const sf::Texture&	GetTexture( int );
		       	const sf::Texture&	GetTexture( std::string );
			sf::Texture&		GetTextureRef( int );
			
			int			LoadFont( std::string );
			bool			IsFontLoaded( std::string );
			int			GetFontId( std::string );
			sf::Font*		GetFontPtr( std::string );
			sf::Font*		GetFontPtr( int );
			sf::Font		GetFont( std::string );
			sf::Font		GetFont( int );
			sf::Font&		GetFontRef( int );

			void 			Free();	
	}; // class Resources
}; // namespace n2d

#endif
