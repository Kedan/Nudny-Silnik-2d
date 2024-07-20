#ifndef NUDNY_SILNIK_2D_VISUAL_TILESET_H
#define NUDNY_SILNIK_2D_VISUAL_TILESET_H

#include <memory>
#include <glm/glm.hpp>
#include <tileson/tileson.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <Interfaces.h>
#include "Interfaces.h"
#include "Resources.h"
#include "Sprite.h"

namespace nudny {
	class Tileset : public Drawable {
		public:
			Tileset();
			Tileset( Tileset& ) = delete;
			~Tileset();
			
			void	operator=( const Tileset& ) = delete;
			//void	SetResources( std::shared_ptr<Resources> );
			void	SetGridSize( glm::vec2 );
			bool	AddTile( Sprite*, std::string = "" );
			bool	AddSprite( Sprite*, std::string );
			Sprite*	GetTile( int );
			Sprite*	GetTile( std::string );
			bool	IsTileExists( int );
			bool	AddAlias( int, std::string = "" );
			bool	AddTileAnimation( std::string, std::map<std::string,float> );
			void	Draw( sf::RenderWindow& );
			void	Draw( sf::RenderWindow&, sf::Transform& );
			bool	LoadTilesetFromTexture( const sf::Texture&, int, int, int, int, std::string = "" );
			bool 	LoadTileFromTexture( const sf::Texture&, int, int, int, int, std::string = "" );
		protected:
			glm::vec2				m_grid_size;
			//std::shared_ptr<Resources>		mp_resources;
			std::map<int,std::unique_ptr<Sprite>> 	m_sprites;	
			std::map<std::string,int> 		m_sprite_names;
	}; // class Tileset
}; // namespace 

#endif
