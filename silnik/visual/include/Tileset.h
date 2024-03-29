#ifndef NUDNY_TILESET_H
#define NUDNY_TILESET_H

#include <iostream>
#include <mutex>
#include <vector>
#include <map>
#include <tileson/tileson.h>
#include <Interfaces.h>
#include <Resources.h>
#include <Sprite.h>
#include <Entity.h>

namespace n2d {
	class Tileset : public Drawable {
		protected:
			glm::vec2		m_grid_size;
			Resources*		mp_resources;
			std::map<int,Sprite> 	m_sprites;	
		public:
			//glm::vec2		tilesize;
			Tileset();
			Tileset( Tileset& ) = delete;
			void operator=( const Tileset& ) = delete;
			
			void 	SetResources( Resources& t_resources ) {
				mp_resources = &t_resources;
			}	
			void	Load( tson::Tileset&, std::string="" );
			void	Load( std::string, std::string );
			Sprite*	GetTile( int );
			bool	IsTileExists( int );
			void	Free();	
			void	SetGridSize( glm::vec2 );
			void 	Draw(sf::RenderWindow& );
			void	Draw( sf::RenderWindow&, sf::Transform& );
		protected:
			glm::vec4 GetCorrectedDrawingRect( tson::Rect, glm::vec2 );
			glm::vec2 GetCorrectTileSize( tson::Rect, tson::Vector2i );
	}; // class Tileset
}; // namespace n2d

#endif
