#ifndef NUDNY_MAP_LAYER_H
#define NUDNY_MAP_LAYER_H

#include "tileson/tileson.h"
#include "Interfaces.h"
#include "Tool.h"
#include "Log.h"
#include "Resources.h"
#include "Shape.h"
#include "Circle.h"
#include "Rect.h"
#include "Poly.h"
#include "Sprite.h"
#include "Body.h"
#include "Entity.h"
#include "Animation.h"
#include "Tileset.h"
#include "EntityFactory.h"
#include "Actor.h"

namespace n2d {
	class Layer : public Drawable, public Updatable, public Interactive { 
		protected:
			bool		m_loaded = false;
			Resources*	mp_resources;
			Tileset*	mp_tileset;
			glm::vec2	m_grid_size;
			void SetDefaultData( tson::Layer& );
		public:
			Logger		log;
			int 		id;
			std::string 	name;
			bool		visible;
			glm::vec2	position;
			
			Layer();
			virtual bool Load( std::string, tson::Layer& ) = 0;
			virtual void Create( b2World& ) = 0;
			void SetResources( Resources& t_resources ) {
				mp_resources = &t_resources;
			};
			void SetTileset( Tileset& t_tileset) {
				mp_tileset = &t_tileset;
			};
			void SetGrid( glm::vec2 t_grid_size ) {
				m_grid_size = t_grid_size;
			}
			/**
			 *
			 * IF you use tiles with size ( i.e. 64x80 pixels ) different than map grid ( i.e. 16x16 pixels ),
			 * tson::Object.getPosition() gives you shit becouse it multiplies tile size, not the map grid size,
			 * so when tile is position ( 1, 1 tiles) - it gives (1*64, 1*80 pixels ) instead of (1*16, 1*16)
			 *
			 * @param t_obj_position [tson::Vector2f]. Tileson object position - tson::Object::getPosition() in pixels
			 * @param t_tile_size [glm::vec2] actual tile size in pixels
			 * @return (glm::vec2) Corrected tile position, calculates using actual map grid size.
			 *
			 */
			glm::vec2 GetCorrectTilePosition( tson::Vector2f t_obj_position, glm::vec2 t_tile_size );
	};// class Layer
	
	class ImageLayer : public Layer {
		protected:
			int	m_texture_id;
			Rect	m_rect;
			Body	m_body;
		public:
			ImageLayer();
			void Draw( sf::RenderWindow& );
			void Draw( sf::RenderWindow&, sf::Transform& );
			void Update( float );
			bool Load( std::string, tson::Layer&);
			void Create( b2World& );
			void Events( sf::Event& );
	}; // class Image Layer
	
	class TileLayer : public Layer {
		protected:
			glm::vec2		m_pos_correction;
			std::vector<Sprite*> 	m_tiles;
			Body			m_body;
		public:
			TileLayer();
			void Draw( sf::RenderWindow& );
			void Draw( sf::RenderWindow&, sf::Transform& );
			void Update( float );
			bool Load( std::string, tson::Layer&);
			void Create( b2World& );
			void Events( sf::Event& );
	}; // class Tile Layer
//	   
	class EntityLayer : public Layer {
		protected:
			glm::vec2		m_pos_correction;
			EntityFactory*		mp_factory;
			std::vector<Entity*>	m_entities;
		public:
			EntityLayer( EntityFactory* );
			void Draw( sf::RenderWindow& );
			void Draw( sf::RenderWindow&, sf::Transform& );
			void Update( float );
			bool Load( std::string, tson::Layer& );
			void Create( b2World& );
			void Events( sf::Event& );
	}; // class Entity Layer
	
	class LayerFactory {
		public:
			LayerFactory(){};
			Layer* Create( tson::Layer& t_layer, EntityFactory* t_entity_factory );
	};
}; // namespace n2d

#endif
