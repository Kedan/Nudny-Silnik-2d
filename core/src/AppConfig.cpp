#include "core/AppConfig.hpp"

namespace ns {
	bool AppConfig::load() {
		if( Config::getInstance().isLoaded() ) {
			screenWidth 	= Config::getInstance().json()["resolution"][0];
			screenHeight	= Config::getInstance().json()["resolution"][1];
			fullscreen 		= Config::getInstance().json()["fullscreen"];
			vsync 			= Config::getInstance().json()["vsync"];
			fps 			= Config::getInstance().json()["fps"];
			masterVolume 	= Config::getInstance().json()["master_volume"];
			musicVolume		= Config::getInstance().json()["music_volume"];
			sfxVolume 		= Config::getInstance().json()["sfx_volume"];
			name 			= Config::getInstance().json()["name"];
			return true;
		}
		return false;
	};

	AppConfig& AppConfig::operator=( const AppConfig& tConfig ) {
		screenWidth 	= tConfig.screenWidth; 
		screenHeight	= tConfig.screenHeight;
		fullscreen 	 	= tConfig.fullscreen;
		vsync 		 	= tConfig.vsync; 
		fps 		 	= tConfig.fps;
		masterVolume 	= tConfig.masterVolume;
		musicVolume  	= tConfig.musicVolume;
		sfxVolume 	 	= tConfig.sfxVolume;
		name 		 	= tConfig.name;
		return *this;
	};
}; // namespace
