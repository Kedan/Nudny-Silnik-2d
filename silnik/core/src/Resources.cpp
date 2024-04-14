#include "Resources.h"

using namespace n2d;

Resources::Resources() {
	LOG.Time() << "Resources constructor\n";
	Free();
	m_textures.reserve(50);
//	m_music.reserve(50);
}

int Resources::LoadTexture( std::string name ) {
	LOG.Time() << "Resources LoadTexture( "<<name<<" ) - begin\n";
	int result = GetTextureId( name );
	if( result < 0 ) { // texture not loaded
		//sf::Texture t;
		m_textures.push_back( sf::Texture() );
		result = m_textures.size() - 1;
		if( !m_textures[result].loadFromFile( name.c_str() )) {
			std::cerr << "Resources::LoadTexture - Couldn't load texture: " << name << std::endl;
			m_textures.pop_back();
			result = -1;
		}
	}
	LOG.Time() << "Resources LoadTexture - end( "<<(result>-1?"ok":"failed")<<" )\n";
	return result;
}
bool Resources::IsTextureLoaded( std::string name ) {
	return m_textureNames.find( name ) == m_textureNames.end() ? false : true;	
}
sf::Texture* Resources::GetTexturePtr( int texture_id ) {
	return &m_textures[ texture_id ];
}
sf::Texture* Resources::GetTexturePtr( std::string name ) {
	int id = -1;
	if( !IsTextureLoaded( name ) ) {
		id = LoadTexture( name );
	}
	return &m_textures[ m_textureNames[ name ] ];
}

int Resources::GetTextureId( std::string name ) {
	return m_textureNames.find( name ) == m_textureNames.end() ?  -1 : m_textureNames[ name ];
}
const sf::Texture& Resources::GetTexture( int id ) {
	return m_textures[ id ];
}

const sf::Texture& Resources::GetTexture( std::string name ) {
	int id = -1;
	if( !IsTextureLoaded( name ) ) {
		id = LoadTexture( name );
	}
	return m_textures[ m_textureNames[ name ] ];
}

sf::Texture& Resources::GetTextureRef( int t_id ) {
	return m_textures[ t_id ];
}

//int Resources::LoadMusic( std::string t_filepath ) {
//	LOG.Time() << "Resources LoadMusic(" << t_filepath << ") - begin\n";
//	int result = GetMusicId( t_filepath );
//	if( result == -1 ) {
//	//	m_music.push_back( sf::Music() );
//	//	result = m_music.size() - 1;
//	//	if( !m_music[ result ].openFromFile( t_filepath.c_str() )) {
//	//		m_music.pop_back();
//	//		result = -1;
//	//	}
//	}
//	LOG.Time() << "Resources LoadTexture - end( "<<(result>-1?"ok":"failed")<<" )\n";
//	return result;
//}

//int Resources::GetMusicId( std::string t_path ) {
//	return m_musicNames.find( t_path ) == m_musicNames.end() ?  -1 : m_musicNames[ t_path ];
//}
//
//
//
//
//bool Resources::IsMusicLoaded( std::string t_filepath ) {
//	return m_musicNames.find( t_filepath ) == m_musicNames.end() ? false : true;	
//}
//
//const sf::Music& Resources::GetMusic( int t_id ) {
//	try {
//		return m_music[ t_id ];
//	} catch( const std::exception& e) {
//		LOG.Time() << "Resources GetMusic( ID: " << t_id << ") " << e.what() << "\n";
//	}
//}
//
//const sf::Music& Resources::GetMusic( std::string t_filepath ) {
//	int id = -1;
//	if( !IsMusicLoaded( t_filepath )) {
//		id = LoadMusic( t_filepath );
//	}
//	return GetMusic( id );
//}

int Resources::LoadFont( std::string t_font_path ) {
	sf::Font f;
	if( f.loadFromFile( t_font_path)) {
		m_fonts.push_back( f );
		m_fontNames[t_font_path] = m_fonts.size()-1;
	} else {
		std::cerr << "n2d::Resources::LoadFont - Could not load font " << t_font_path << "\n";
	}
	return m_fonts.size()-1;
}	

bool Resources::IsFontLoaded( std::string t_font ) {
	return m_fontNames.find( t_font ) == m_fontNames.end() ? false : true;
}

sf::Font* Resources::GetFontPtr( int t_id ) {
	return &m_fonts[ t_id ];
}
sf::Font* Resources::GetFontPtr( std::string name ) {
	int id = -1;
	if( !IsFontLoaded( name ) ) {
		id = LoadFont( name );
	}
	return &m_fonts[ m_fontNames[ name ] ];
}

int Resources::GetFontId( std::string name ) {
	return m_fontNames.find( name ) == m_fontNames.end() ?  -1 : m_fontNames[ name ];
}

sf::Font Resources::GetFont( int id ) {
	return m_fonts[ id ];
}

sf::Font Resources::GetFont( std::string name ) {
	int id = -1;
	if( !IsFontLoaded( name ) ) {
		id = LoadFont( name );
	}
	return m_fonts[ m_fontNames[ name ] ];
}

sf::Font& Resources::GetFontRef( int t_id ) {
	return m_fonts[ t_id ];
}

void Resources::Free() {
	m_textures.clear();
	m_textureNames.clear();
	m_fonts.clear();
//	m_music.clear();
//	m_musicNames.clear();
}
