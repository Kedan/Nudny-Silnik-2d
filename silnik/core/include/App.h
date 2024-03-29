#ifndef NUDNY_APP_H
#define NUDNY_APP_H

#include <iostream>
#include <unordered_map>
#include <glm/glm.hpp>
#include <memory>
#include <list>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include "box2d/box2d.h"
#include "tileson/tileson.h"
#include "Interfaces.h"
#include "JSONLoader.h"
#include "Resources.h"
#include "Log.h"
//#include "Map.h"

// app class should be singleton
// or resource manager should be singleton

namespace n2d {
	/**
	 * This is MAIN application class. The Core. The Meritum. The thing. 
	 * It do, what has to be done.
	 * Amen.
	 */ 
	class App {
		protected:
			Logger log;

			/** Application configuration. All App properties are in this file. */
			json			m_conf;

			/** Application name */
			std::string		m_name;

			/** Window size */
			glm::vec2 		m_window_size;

			/** Window framerate. Value -1 means that VSYNC is ON */
			float 			m_fps 		= -1.0f;

			/** Fullscreen yes/no flag */
			bool 			m_fullscreen 	= false;

			/** VSYNC flag. If set on true, framerate is set on -1 */
			bool 			m_vsync 	= true;

			/** Application exit flag. Used to break main loop. */
			bool 			m_exit 		= false;
			
			/** Application timer */
			sf::Clock 		m_clock;

			/** Application time, calculated by m_clock */
			sf::Time 		m_time;

			/** Application event handler */
			sf::Event 		m_event;

			/** Drawing view */
			sf::View 		m_view;

			/** Application main drawing window */
			sf::RenderWindow	m_window;
			
			/** Number of velocity calculation iterations. Used by Box2D system. */ 
			int 			m_velocity_iterations 	= 6;

			/** Number of position calculation iterations. Used by Box2D system. */
			int 			m_position_iterations 	= 2;

			/** Default, hardcoded time step, in case when some sh*t happend to m_clock, or m_time. Also lock framerate to 60 FPS. */
			float 			m_time_step 		= 1 / 60.0f;

			/** Default gravity vector, in case when there is no defined in configuration file. Used by Box2D system. */
			b2Vec2 			m_gravity 		= b2Vec2( 0, -9.81f );
			
			/** List of Updatable objects. All of them ara called in main loop. */
			std::list<Updatable*>		m_update_list;

			/** List of Drawable objects. All of them are called in main loop. */
			std::list<Drawable*> 		m_draw_list;

			/** List of Interactive objects. All of them are called int main loop. */
			std::map<int,Interactive*>	m_interactive_list;
			
			/** Need to delete this */
			std::string		m_default_font;
		public:
			/** Box2D physics world. It creates all physically simulated bodies. */	
			b2World			world = b2World( b2Vec2( 0, 9.81f ));

			/** Top resources, that need to be shared in all application.
			 * IT IS NOT ALL RESOURCES!
			 * Each Map has it's own Resources, which are freed when map is unloaded.
			 */
			Resources		src;
			
			/** Default constructor */
			App();

			/** Constructor
			 * @param	t_name Path to configuration file. */
			App( std::string t_name );
			
			/**
			 * Loading method.
			 * @param	Path to configuration file. 
			 */
			void 			Load( std::string );

			/**
			 * Reset all properties to default state
			 */
			void 			Reset();

			/**
			 * Runs the application. Main Loop.
			 */
			int 			Run();

			/**
			 * Adding Updatable object to list.
			 * @param	*tp_obj	Pointer to object.
			 * @return	Object index on list.
			 */
			int 			AddUpdatable( Updatable* tp_obj );
			int 			AddDrawable( Drawable* tp_obj );
			int			AddInteractive( Interactive* );
			bool			RemoveInteractive( int );
			int	 		AddTexture( std::string );
			const sf::Texture*	GetTexturePtr( int );

			inline void SetScreenSize( float t_width, float t_height ) {
				m_window_size = glm::vec2( t_width, t_height );
			}

			inline void SetFullscreen( bool t_fullstreen = false ) {
				m_fullscreen = t_fullstreen;
			}

			inline void SetVsync( bool t_vsync = true ) {
				m_vsync = t_vsync;
				if( m_vsync ) 
					m_fps = -1;
			}

			inline void SetFPS( float t_fps = -1.0f ) {
				m_fps = t_fps;
				if( m_fps > 0 )
					m_vsync = false;
			}

			inline void SetGravity( float t_x, float t_y ) {
				m_gravity.x = t_x;
				m_gravity.y = t_y;
			}

			inline void SetDefaultFont( std::string t_font ) {
				m_default_font = t_font;
			}

			inline float GetFPS(){
				return m_fps;
			}

			void Draw( sf::RenderWindow& );

	};
}; // namespace n2d

#endif
