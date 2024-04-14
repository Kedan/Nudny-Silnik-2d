#ifndef NUDNY_TILESET_H
#define NUDNY_TILESET_H

#include <iostream>
#include <mutex>
#include <vector>
#include <map>
#include <tileson/tileson.h>
#include <Interfaces.h>
#include <Log.h>
#include <Resources.h>
#include <Sprite.h>
#include <Entity.h>

namespace n2d {
	class Tileset : public Drawable {
		protected:
			glm::vec2			m_grid_size;
			Resources*			mp_resources;
			std::map<int,Sprite> 		m_sprites;
			std::map<std::string,int> 	m_sprite_names;
		public:
			Logger			log;	
			//glm::vec2		tilesize;
			Tileset();
			Tileset( Tileset& ) = delete;
			~Tileset();
			void operator=( const Tileset& ) = delete;
			
			void 	SetResources( Resources& t_resources ) {
				mp_resources = &t_resources;
			}	
			bool		Load( tson::Tileset&, std::string="" );
			bool		Load( std::string, std::string );
			Sprite*		GetTile( int );
			Sprite*		GetTile( std::string );
			bool		IsTileExists( int );
			void		Free();	
			void		SetGridSize( glm::vec2 );
			void 		Draw(sf::RenderWindow& );
			void		Draw( sf::RenderWindow&, sf::Transform& );
		protected:
			tson::Rect	GetCorrectedDrawingRect( tson::Rect );
			glm::vec2 	GetCorrectTileSize( tson::Rect, tson::Vector2i );
	}; // class Tileset
}; // namespace n2d

#endif
