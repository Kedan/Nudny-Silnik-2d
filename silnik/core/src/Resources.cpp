#include "Resources.h"

using namespace n2d;

Resources::Resources() {
	LOG.Time() << "Resources constructor\n";
	Free();
//	m_textures.reserve(50);
	textures.ReserveMemory( 50 );

}

Resources::~Resources() {
	Free();
}

//int Resources::LoadTexture( std::string name ) {
//	LOG.Time() << "Resources LoadTexture( "<<name<<" ) - begin\n";
//	int result = GetTextureId( name );
//	if( result < 0 ) { // texture not loaded
//		//sf::Texture t;
//		m_textures.push_back( sf::Texture() );
//		result = m_textures.size() - 1;
//		if( !m_textures[result].loadFromFile( name.c_str() )) {
//			std::cerr << "Resources::LoadTexture - Couldn't load texture: " << name << std::endl;
//			m_textures.pop_back();
//			result = -1;
//		} else {
//			m_textureNames[ name ] = result;
//		}
//	}
//	LOG.Time() << "Resources LoadTexture - end( "<<(result>-1?"ok":"failed")<<" )\n";
//      	textures.Load( name );
//	return result;
//}
//bool Resources::IsTextureLoaded( std::string name ) {
////	return m_textureNames.find( name ) == m_textureNames.end() ? false : true;	
//	return textures.IsLoaded( name );
//}
//sf::Texture* Resources::GetTexturePtr( int texture_id ) {
////	return &m_textures[ texture_id ];
//	return textures.GetPtr( texture_id );
//}
//sf::Texture* Resources::GetTexturePtr( std::string name ) {
////	int id = -1;
////	if( !IsTextureLoaded( name ) ) {
////		id = LoadTexture( name );
////	}
////	return &m_textures[ m_textureNames[ name ] ];
//	return textures.GetPtr( name );
//}
//
//int Resources::GetTextureId( std::string name ) {
////	return m_textureNames.find( name ) == m_textureNames.end() ?  -1 : m_textureNames[ name ];
//	return textures.GetId( name );
//}
//const sf::Texture& Resources::GetTexture( int id ) {
////	return m_textures[ id ];
//	return textures.GetCRef( id );
//}
//
//const sf::Texture& Resources::GetTexture( std::string name ) {
////	int id = -1;
////	if( !IsTextureLoaded( name ) ) {
////		id = LoadTexture( name );
////	}
////	return m_textures[ m_textureNames[ name ] ];
//	return textures.GetCRef( name );
//}
//
//sf::Texture& Resources::GetTextureRef( int t_id ) {
////	return m_textures[ t_id ];
//	return textures.GetRef( t_id );
//}
//
//int Resources::LoadMusic( std::string t_filepath ) {
////	LOG.Time() << "Resources LoadMusic(" << t_filepath << ") - begin\n";
////	int result = GetMusicId( t_filepath );
////	if( result == -1 ) {
////		m_music.push_back(std::shared_ptr<sf::Music>( new sf::Music() ));
////		result = m_music.size() - 1;
////		if( !m_music[ result ]->openFromFile( t_filepath )) {
////			m_music.pop_back();
////			result = -1;
////		} else {
////			m_musicNames[ t_filepath ] = result;
////		}
////	}
////	LOG.Time() << "Resources LoadMusic - end( "<<(result>-1?"ok":"failed")<<" )\n";
////	return result;
//	return music.Load( t_filepath );
//}
//
//int Resources::GetMusicId( std::string t_path ) {
////	return m_musicNames.find( t_path ) == m_musicNames.end() ?  -1 : m_musicNames[ t_path ];
//	return music.GetId( t_path );
//}
// 
//bool Resources::IsMusicLoaded( std::string t_filepath ) {
////	return m_musicNames.find( t_filepath ) == m_musicNames.end() ? false : true;	
//	return music.IsLoaded( t_filepath );
//}
//
//std::shared_ptr<sf::Music> Resources::GetMusic( int t_id ) {
////	try {
////		return m_music[ t_id ];
////	} catch( const std::exception& e) {
////		LOG.Time() << "Resources GetMusic( ID: " << t_id << ") " << e.what() << "\n";
////	}
//	return music.Get( t_id );
//}
//
//std::shared_ptr<sf::Music> Resources::GetMusic( std::string t_filepath ) {
////	int id = GetMusicId( t_filepath );
////	if( !IsMusicLoaded( t_filepath )) {
////		id = LoadMusic( t_filepath );
////	}	
////	return GetMusic( id );
//	return music.Get( t_filepath );
//}
//
//// sounds
//
//int Resources::LoadSound( std::string t_filepath ) {
//	LOG.Time() << "Resources Load Sound ("<< t_filepath <<")\n";
//	int result = GetSoundId( t_filepath );
//	if( result < 0 ) {
//		m_sound_buffers.push_back(sf::SoundBuffer());
//		result = m_sound_buffers.size() - 1;
//		if( m_sound_buffers[ result ].loadFromFile( t_filepath )) {
//			m_sound_map[ t_filepath ] = result;
//		} else {
//			m_sound_buffers.pop_back();
//			result = -1;
//		}
//	}
//	LOG.Time() << "Resources Load Sound - end( "<<(result>-1?"ok":"failed")<<" )\n";
//	return result;
//}
//
//int Resources::GetSoundId( std::string t_path ) {
//	return m_sound_map.find( t_path ) == m_sound_map.end() ?  -1 : m_sound_map[ t_path ];
//}
//
//bool Resources::IsSoundLoaded( std::string t_filepath ) {	
//	return m_sound_map.find( t_filepath ) == m_sound_map.end() ? false : true;	
//}
//
//sf::SoundBuffer	Resources::GetSoundBuffer( int t_id ) {
//	return m_sound_buffers[ t_id ];
//}
//
//sf::SoundBuffer	Resources::GetSoundBuffer( std::string t_filepath ) {
//	int id = GetSoundId( t_filepath );
//	return m_sound_buffers[ id ];
//}
//
//// fonts
//
//int Resources::LoadFont( std::string t_font_path ) {
//	sf::Font f;
//	if( f.loadFromFile( t_font_path)) {
//		m_fonts.push_back( f );
//		m_fontNames[t_font_path] = m_fonts.size()-1;
//	} else {
//		std::cerr << "n2d::Resources::LoadFont - Could not load font " << t_font_path << "\n";
//	}
//	return m_fonts.size()-1;
//}	
//
//
//bool Resources::IsFontLoaded( std::string t_font ) {
//	return m_fontNames.find( t_font ) == m_fontNames.end() ? false : true;
//}
//
//sf::Font* Resources::GetFontPtr( int t_id ) {
//	return &m_fonts[ t_id ];
//}
//sf::Font* Resources::GetFontPtr( std::string name ) {
//	int id = -1;
//	if( !IsFontLoaded( name ) ) {
//		id = LoadFont( name );
//	}
//	return &m_fonts[ m_fontNames[ name ] ];
//}
//
//int Resources::GetFontId( std::string name ) {
//	return m_fontNames.find( name ) == m_fontNames.end() ?  -1 : m_fontNames[ name ];
//}
//
//sf::Font Resources::GetFont( int id ) {
//	return m_fonts[ id ];
//}
//
//sf::Font Resources::GetFont( std::string name ) {
//	int id = -1;
//	if( !IsFontLoaded( name ) ) {
//		id = LoadFont( name );
//	}
//	return m_fonts[ m_fontNames[ name ] ];
//}
//
//sf::Font& Resources::GetFontRef( int t_id ) {
//	return m_fonts[ t_id ];
//}

void Resources::Free() {
//	m_textures.clear();
//	m_textureNames.clear();
//	m_fonts.clear();
//	for( auto music : m_music ) {
//		music->stop();
//	}
//	m_music.clear();
//	m_musicNames.clear();

	textures.Free();
	fonts.Free();
	sound_buffers.Free();
	music.Free();
}
