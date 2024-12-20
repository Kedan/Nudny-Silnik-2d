#include <core/App.hpp>
#include <core/Input.hpp>

namespace ns {

App::App( const std::string& tConfig, const GameStateFactory& tFactory ) : mFactory( &tFactory ) {
	Config::getInstance().load( tConfig );
	mConfig.load();
		
	mWindow.create( sf::VideoMode( mConfig.screenWidth, mConfig.screenHeight ), mConfig.name, mConfig.fullscreen ? sf::Style::Fullscreen : sf::Style::Default );
	mWindow.setVerticalSyncEnabled( mConfig.vsync );
	if( mConfig.fps > 0 ) {
		mWindow.setFramerateLimit( mConfig.fps );
	}
	
	if( mFactory ) {
		mCurrentState = std::move(mFactory->create(0));
		//mCurrentState = mFactory->create(0);
		mCurrentState->enter();
		mExit = false;
	}
	mTime = mClock.restart();
}

bool App::run() {
	if(mExit) {
		mWindow.close();
		return EXIT_FAILURE;
	}
	
	while( !mExit && mWindow.isOpen() ) {
		mTime = mClock.restart();
		Input::getInstance().reset();
		mCurrentState->initPipeline();
		mCurrentState->simulate( mTime );
		while( mWindow.pollEvent(mEvent)) {
			Input::getInstance().dispatch( mEvent, mWindow );
			if( mFactory && mCurrentState ) {
				std::unique_ptr<GameState> new_state = mCurrentState->dispatch( mEvent );
				if( new_state ) {
					mCurrentState->exit();
					mCurrentState = std::move( new_state );
					mCurrentState->enter();
				}
				mExit = Input::getInstance().isHeld( sf::Keyboard::Escape) || mEvent.type == sf::Event::Closed; 
			}
		}
		mWindow.clear( sf::Color::Black );
		mCurrentState->handleEvents( mEvent );
		mCurrentState->update( mTime );
		mCurrentState->draw( mWindow );
		mWindow.display();	
	}
	
	return EXIT_SUCCESS;
}

}; // namespace ns
