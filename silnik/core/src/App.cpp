#include "Interfaces.h"
#include "Keyboard.h"
#include "App.h"

using namespace n2d;

App::App(){
	LOG.Time();
	LOG << "\tApp constructor\n";
}

App::App( std::string t_name ) {
	m_name = t_name;
	LOG.Time();
	LOG << "\tApp " << t_name << " constructor\n";
}

App::~App() { 
	LOG.Time();
	LOG << "App " << m_name << " destructor\n";
}

void App::Load( std::string t_conf_file ) {

	LOG.Time();
	LOG << "\tApp Load";	

	JSONLoader loader( t_conf_file );
	m_conf = loader.GetData();

	m_name = m_conf["AppName"];

	SetScreenSize( (float)m_conf["resolution"][0], (float)m_conf["resolution"][1] );
	SetFullscreen( (bool)m_conf["fullscreen"] );
	SetVsync( JSONLoader::Find("vsync",m_conf) ? (bool)m_conf["vsync"] : false );
	SetFPS( JSONLoader::Find( "FPS", m_conf ) ? (float)m_conf["FPS"] : -1.0f );

	SetGravity( m_conf["physics"]["gravity"][0], m_conf["physics"]["gravity"][1] );
	SetDefaultFont( m_conf["default_font"] );

	//LoadScenario();
 	
	LOG << " - done\n";
	Reset();
}

void App::Reset() {
	LOG.Time();
	LOG << "\tApp Reset";
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
	world.SetGravity( m_gravity );

	LOG << " - done\n";
}

int App::AddUpdatable( Updatable* t_p_obj ) {
	LOG.Time();
	LOG << "\tApp AddUpdatable( " << t_p_obj << " )\n";
	m_update_list.push_back( t_p_obj );
	return m_update_list.size() - 1;
}

int App::AddDrawable( Drawable* t_p_obj ) {
	LOG.Time();
	LOG << "\tApp AddDrawable( "<< t_p_obj <<" )\n";
	m_draw_list.push_back( t_p_obj );
	return m_draw_list.size() - 1;
}

int App::AddInteractive( Interactive* t_obj ) {
	int size = m_interactive_list.size();
	m_interactive_list[ size ] = t_obj;
	return size;
}

bool App::RemoveInteractive( int t_id ) {
	auto f = m_interactive_list.find( t_id );
	if( f != m_interactive_list.end() ) {
		m_interactive_list.erase( f );
		return true;
	}
	return false;
}

int App::AddTexture( std::string t_name ) {
 	return src.LoadTexture( t_name );
}

const sf::Texture* App::GetTexturePtr( int t_texture_id ) {
	return src.GetTexturePtr( t_texture_id );
}	

int App::Run() {
	LOG.Time();
	LOG << "\tApp Run()......\n";
	//layers.creatables.Create( m_world );
	while( m_window.isOpen() && !m_exit ) {
		m_time = m_clock.restart();
		while( m_window.pollEvent( m_event )) {
			Keyboard::Instance()->Clear();
			Keyboard::Instance()->Dispatch( m_event );
			DispatchGameState();
			if( sf::Keyboard::isKeyPressed( sf::Keyboard::Escape ) || m_event.type == sf::Event::Closed ) {
				LOG.Time();
				LOG << "\tApp Run - Exiting event triggered..\n";
				m_exit = true;
			}
			for( auto interactive_obj : m_interactive_list ) {
				interactive_obj.second->Events( m_event );
			}
		}
		m_window.clear( sf::Color::Black );
		world.Step( m_time_step, m_velocity_iterations, m_position_iterations );
		for( auto uobj : m_update_list ) {
			uobj->Update( m_time.asSeconds() );
		}
		m_window.setView( m_view );
		for( auto dobj : m_draw_list ) {
			dobj->Draw( m_window );
		}
		m_window.display();
	}
	m_window.close();
	LOG.Time();
	LOG << "\tExiting App\n";
	return EXIT_SUCCESS;
}

void App::DispatchGameState() {
	if( m_game_state && m_game_state_factory ) {	
		GameState* tmp_game_state = m_game_state->Dispatch( *this, m_event );
		if( tmp_game_state != nullptr ) {
			SetGameState( tmp_game_state );
		}
	}
}

void App::ClearLists() {
	m_draw_list.clear();
	m_update_list.clear();
	m_interactive_list.clear();
	m_creatable_list.clear();
}

void App::LoadScenario() {
	if( m_game_state_factory ) {
		m_game_state_factory->SetScenario( m_conf["scenario"]);
		m_game_state = m_game_state_factory->CreateFromScenario( m_conf["scenario"]["current"] );
	}
}
