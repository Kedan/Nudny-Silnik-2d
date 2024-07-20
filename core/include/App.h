#ifndef NUDNY_SILNIK_2D_CORE_APP_H
#define NUDNY_SILNIK_2D_CORE_APP_H

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
#include "Tool.h"
#include "Interfaces.h"
#include "Resources.h"
#include "GameState.h"
#include "GameStateFactory.h"

namespace nudny {
	class App {
		protected:
			json			m_conf;
			std::string		m_name;
			glm::vec2 		m_window_size;
			float 			m_fps 		= -1.0f;
			bool 			m_fullscreen 	= false;
			bool 			m_vsync 	= true;
			float			m_master_volume	= 100.0f;
			float			m_music_volume 	= 100.0f;
			float			m_sound_volume	= 100.0f;
			bool 			m_exit 		= false;
		
			float			m_time_step	= 1/60.f;	
			sf::Clock 		m_clock;
			sf::Time 		m_time;

			sf::Event 		m_event;
			sf::View 		m_view;
			sf::RenderWindow	m_window;

			std::unique_ptr<GameState>	m_game_state;
			GameStateFactory*	m_game_state_factory;	
		public:
			Resources		src;
			
			App();
			App( std::string t_name );
			~App();
			void 			Load( std::string );
			void			Save( std::string );
			void 			Reset();
			int 			Run();
			
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
			
			inline float CheckVolume( float t_volume ) {
				return ( t_volume <= 100.0f && t_volume >= 0.0f ) ? t_volume : 75.0f;
			}

			inline void SetAudioMasterVolume( float t_volume = 100.0f ) {
				m_master_volume = CheckVolume( t_volume );
			}

			inline void SetAudioMusicVolume( float t_volume = 100.0f ) {
				m_music_volume = CheckVolume( t_volume );
			}

			inline void SetAudioSoundVolume( float t_volume = 100.0f ) {
				m_sound_volume = CheckVolume( t_volume );
			}

			inline void SetVolume( float t_master_volume = 100.0f, float t_sound_volume = 100.0f, float t_music_volume = 100.0f ) {
				SetAudioMasterVolume( t_master_volume );
				SetAudioSoundVolume( t_sound_volume );
				SetAudioMusicVolume( t_music_volume );
			}
				
			inline void SetGameState( std::unique_ptr<GameState> t_game_state ) {
				LOG.Time() << "App SetGameState() - changeing game state from "<< m_game_state.get() << " to " << t_game_state.get() << "\n";
				if( m_game_state ) {
					m_game_state->Exit( *this );
				}			
				m_game_state = std::move(t_game_state);
				m_game_state->Enter( *this );
			}
			
			inline void SetGameStateFactory( GameStateFactory& t_game_state_factory ) {
				m_game_state_factory = &t_game_state_factory;
			}	
			
			inline float GetFPS(){
				return m_fps;
			}

			void Draw( sf::RenderWindow& );
		protected:
			void DispatchGameState();

	};
}; // namespace n2d

#endif
