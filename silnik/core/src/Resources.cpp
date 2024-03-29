#include "Resources.h"

using namespace n2d;

Resources::Resources() {
	Free();
	m_textures.reserve(50);
}

int Resources::LoadTexture( std::string name ) {
	//std::cout << "Resources::LoadTexture\n";
	int result = GetTextureId( name );
	if( result < 0 ) { // texture not loaded
		//sf::Texture t;
		m_textures.push_back( sf::Texture() );
		result = m_textures.size() - 1;
		if( !m_textures[result].loadFromFile( name.c_str() )) {
			std::cerr << "Resources::LoadTexture - Couldn't load texture: " << name << std::endl;
			m_textures.pop_back();
			result = -1;
		} else {
			//m_textures.push_back( t );
			//result = m_textures.size() - 1;
			m_textureNames[ name ] = result;
			sf::Texture* 	ptr0 	= GetTexturePtr( result );
			sf::Texture* 	ptr1 	= GetTexturePtr( name );
			sf::Texture& 	ref	= GetTextureRef( result );
			sf::Texture	tex0	= GetTexture( result );
			sf::Texture	tex1	= GetTexture( name );
	//		std::cout 
	//			<< "LOAD " 
	//			<< name 
	//			<< " "
	//			<< result 
	//			<< " vRef:" << &m_textures[ result ] 
	//			<< " GetPtr:" << ptr0 << "|" << ptr1
	//			<< " Get Ref:" << &ref
	//			<< " Get Tex: " << &tex0  << "|" << &tex1
	//			<<  "\n";
			}
	} 
//	else {
//		sf::Texture* 	ptr0 	= GetTexturePtr( result );
//		sf::Texture* 	ptr1 	= GetTexturePtr( name );
//		sf::Texture& 	ref	= GetTextureRef( result );
//		sf::Texture	tex0	= GetTexture( result );
//		sf::Texture	tex1	= GetTexture( name );
//		std::cout 
//			<< "GET" 
//			<< name 
//			<< "  " 
//			<< result 
//			<< " vRef:" << &m_textures[ result ] 
//			<< " GetPtr:" << ptr0 << "|" << ptr1
//			<< " Get Ref:" << &ref
//			<< " Get Tex: " << &tex0  << "|" << &tex1
//			<<  "\n";
//	}
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
}
