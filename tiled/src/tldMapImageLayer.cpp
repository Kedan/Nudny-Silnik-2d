#include <tldMapImageLayer.h>

using namespace nudny;

bool tldMapImageLayer::Load( tson::Layer& t_layer, std::string t_dir ) {
	if( mp_resources ) {
		m_layer = t_layer;
		
		m_id	= m_layer.getId();
		m_name 	= m_layer.getName();
		m_visible = m_layer.isVisible();
		m_position.x = m_layer.getX() * 16;
		m_position.y = m_layer.getY() * 16;
	
		std::string tmp = t_dir;
		tmp.append( m_layer.getImage() );
		m_texture_id = mp_resources->textures.Load( tmp );
		glm::vec2 tex_size;
		tex_size.x = mp_resources->textures.GetPtr( m_texture_id )->getSize().x;
		tex_size.y = mp_resources->textures.GetPtr( m_texture_id )->getSize().y;
		glm::vec2 lyr_pos;
		lyr_pos.x = m_position.x + m_layer.getOffset().x;
		lyr_pos.y = m_position.y + m_layer.getOffset().y;
	
		m_body.SetPosition( m_position.x + m_layer.getOffset().x + tex_size.x/2, m_position.y + m_layer.getOffset().y + tex_size.y/2) ;
		m_rectangle.SetTexture( mp_resources->textures.GetPtr( m_texture_id ));
		m_rectangle.SetSize( tex_size );
		m_rectangle.SetOrigin( tex_size.x/2, tex_size.y/2 );
		m_rectangle.SetPosition(0,0);
		m_body.Add( &m_rectangle );
		m_is_loaded = true;
	}
	return m_is_loaded;
}
