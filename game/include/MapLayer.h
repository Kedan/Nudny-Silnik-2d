#ifndef NUDNY_SILNIK_2D_GAME_MAP_LAYER_H
#define NUDNY_SILNIK_2D_GAME_MAP_LAYER_H

#include <iostream>
#include <memory>
#include <glm/glm.hpp>
#include <Interfaces.h>
#include <Resources.h>
#include <Tileset.h>

namespace nudny {
	class MapLayer : 
		public Drawable, 
		public Updatable, 
		public Interactive
		// public Transformable,
		// public Visual ??
	{
		public:
			MapLayer();
			int		GetId();
			std::string 	GetName();
			bool		IsVisible();
			glm::vec2	GetPosition();
			float		GetX();
			float		GetY();
			glm::vec2	GetGridSize();
			float		GetGridWidth();
			float		GetGridHeight();

			void		SetPosition( float, float );
			void		SetPosition( glm::vec2 );
			void		SetVisible( bool );
			void		SetGridSize( float, float );
			void 		SetGridSize( glm::vec2 );

			void Draw( sf::RenderWindow& );
			void Draw( sf::RenderWindow&, sf::Transform& );
			void Update( sf::Time& );
			void Events( sf::Event& );
		protected:
			int				m_id;
			std::string 			m_name;
			bool				m_visible;
			glm::vec2			m_position;
			bool				m_is_loaded = false;
			std::shared_ptr<Resources>	mp_resources;
			std::shared_ptr<Tileset>	mp_tileset;
			glm::vec2			m_grid_size;	
	}; // class
}; // namespace

#endif
