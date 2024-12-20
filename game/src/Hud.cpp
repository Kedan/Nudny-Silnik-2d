#include "core/Input.hpp"
#include "core/Config.hpp"
#include "game/Hud.hpp"

ns::Hud::Hud() {
	mPipeline = std::make_shared<ns::Pipeline>(ns::Pipeline());
	mResources = std::make_shared<ns::Resources>(ns::Resources());
	mView.setViewport( sf::FloatRect(0,0,1,1));
	mView.setSize(256,128);
	mView.setCenter(128,64);
				
	std::string f = ns::Config::getInstance().json()["font"];
	mResources->fonts.load(f);
	mFontStyle.font = mResources->fonts.get(f);
	mFontStyle.size = 10;
	mFontStyle.color = sf::Color::White;
	//std::cout << mFontStyle.font << std::endl;	
	mText->setStyle( mFontStyle );
}

void ns::Hud::setupPipeline() {
	int x = ns::mx();
	int y = ns::my();
	mMsg = "Mouse position: ["+std::to_string(x)+", "+std::to_string(y)+"]";
	mText->print( mMsg );
	mPipeline->draw->push( mText );
}

void ns::Hud::draw( sf::RenderWindow& tWindow ) {
	tWindow.setView( mView );
	mPipeline->draw->execute( tWindow );
}

void ns::Hud::update( const sf::Time& tTime ) {
	mPipeline->update->execute( tTime );
}

void ns::Hud::handleEvents( const sf::Event& tEvent ) {
	mPipeline->interactive->execute( tEvent );
}
