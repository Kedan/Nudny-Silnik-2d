#include "Interfaces.h"
#include "Keyboard.h"
#include "App.h"

using namespace nudny;

App::App(){
	LOG.Time();
	LOG << "App constructor\n";
}

App::App( std::string t_name ) {
	m_name = t_name;
	LOG.Time() << "App " << t_name << " constructor\n";
}

App::~App() { 
	LOG.Time() << "App " << m_name << " destructor\n";
}

void App::Load( std::string t_conf_file ) {

	LOG.Time() << "App Load";	

	JSONLoader loader( t_conf_file );
	m_conf = loader.GetData();

	m_name = m_conf["AppName"];

	SetScreenSize( (float)m_conf["resolution"][0], (float)m_conf["resolution"][1] );
	SetFullscreen( (bool)m_conf["fullscreen"] );
	SetVsync( JSONLoader::Find("vsync",m_conf) ? (bool)m_conf["vsync"] : false );
	SetFPS( JSONLoader::Find( "FPS", m_conf ) ? (float)m_conf["FPS"] : -1.0f );
 	
	LOG << " - done\n";
	Reset();
}

void App::Reset() {
	LOG.Time() << "App Reset";
	m_time_step = 1/60.0f;
	m_clock.restart();
	m_view.setViewport( sf::FloatRect( 0.0f, 0.0f, 1.0f, 1.0f ));
	m_view.setSize( m_window_size.x, m_window_size.y );
	m_view.setCenter( m_window_size.x/2, m_window_size.y/2 );

	m_window.create( sf::VideoMode( m_window_size.x, m_window_size.y ), m_name, m_fullscreen ? sf::Style::Fullscreen : sf::Style::Default );
	m_window.setVerticalSyncEnabled( m_vsync );
	if( m_fps > 0 ) {
		m_window.setFramerateLimit( m_fps );
		m_time_step = 1/m_fps;
	}
	m_window.setView( m_view );	

	LOG << " - done\n";
}

int App::Run() {
	LOG.Time();
	LOG << "App Run()......\n";
	//layers.creatables.Create( m_world );
	while( m_window.isOpen() && !m_exit ) {
		m_time = m_clock.restart();
		m_game_state->Simulate();
		while( m_window.pollEvent( m_event )) {
			Keyboard::Instance().Clear();
			Keyboard::Instance().Dispatch( m_event );
			DispatchGameState();
			if( sf::Keyboard::isKeyPressed( sf::Keyboard::Escape ) || m_event.type == sf::Event::Closed ) {
				LOG.Time();
				LOG << "App Run - Exiting event triggered..\n";
				m_exit = true;
			}
			m_game_state->Events( m_event );
		}
		m_window.clear( sf::Color::Black );
		m_game_state->Update( m_time );
		m_window.setView( m_view );
		m_game_state->Draw( m_window );
		m_window.display();
	}
	m_window.close();
	LOG.Time();
	LOG << "App Exiting\n";
	return EXIT_SUCCESS;
}

void App::DispatchGameState() {
	if( m_game_state && m_game_state_factory ) {	
		std::unique_ptr<GameState> tmp_game_state = m_game_state->Dispatch( *this, m_event );
		if( tmp_game_state ) {
			LOG.Time() << "App DispatchGameState()\n";
			SetGameState( std::move( tmp_game_state ) );
		}
	}
}

