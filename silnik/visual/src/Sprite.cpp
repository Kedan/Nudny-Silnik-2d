#include "Sprite.h"

using namespace n2d;

Sprite::Sprite() {
	Reset();
	SetDensity();
	SetFriction();
	SetColor();
	fixture.shape 		= &bound;
	animation.SetSprite( sprite );
}

Sprite::Sprite( int texture_id ) {
	Reset();
	SetDensity();
	SetFriction();
	SetColor();
	fixture.shape 		= &bound;
	animation.SetSprite( sprite );
}


Sprite::Sprite( const Sprite& t_sprite) {
	Reset();
	GID	= t_sprite.GID;
	sprite 	= t_sprite.sprite;
	SetDensity( t_sprite.fixture.density );
	SetFriction( t_sprite.fixture.friction );
	SetTextureCoords( t_sprite.tex_coords );
	SetSize( t_sprite.m_size.x, t_sprite.m_size.y );
	if( t_sprite.m_vertices.size() > 2 ) {
		SetVertices( t_sprite.m_vertices ); // ! before postion & rotation
	}
	SetPosition( t_sprite.position.x, t_sprite.position.y );
	SetRotation( t_sprite.rotation );
	SetColor( t_sprite.color );
	collide			= t_sprite.collide;
	fixture.shape 		= &bound;
	animation = t_sprite.animation;
	animation.SetSprite( sprite );
}

void Sprite::SetTexture( sf::Texture& t_texture ) {
	sprite.setTexture( t_texture );
}

void Sprite::SetTexture( int id ) {
	texture_id = id;
	sprite.setTexture( mp_resources->GetTextureRef( texture_id ));
}
void Sprite::SetTexture( std::string texture_path ) {
	if( !mp_resources->IsTextureLoaded( texture_path ) ) {
		texture_id = mp_resources->LoadTexture( texture_path );
	}
	if( texture_id >= 0 ) {
		SetTexture( texture_id );
	}
	//SetTextureCoords();
}

sf::Drawable* Sprite::GetDrawable()  {
	return (sf::Drawable*)&sprite;
}

sf::Transformable* Sprite::GetTransformable() {
	return (sf::Transformable*)&sprite;
}

Shape* Sprite::Clone() const  {
	return new Sprite( *this );
}

void Sprite::Draw( sf::RenderWindow& w ) {
	w.draw( sprite, m_transform );
//	w.draw( shape, m_transform );
}

void Sprite::Draw( sf::RenderWindow& w, sf::Transform& t ) {
	w.draw( sprite, t );
//	w.draw( shape, m_transform );
}

void Sprite::AddBodyCoords( float x, float y, float r ) {
	m_transform = sf::Transform::Identity;
	m_transform.translate( x, y );
	m_transform.rotate( r );
}
void Sprite::SetTextureCoords( glm::vec4 coords ) {
	if( texture_id > -1 && coords[0]==0 && coords[1]==0 && coords[2] == 0 && coords[3]==0 ) {
		coords[2] = mp_resources->GetTexture( texture_id ).getSize().x;
		coords[3] = mp_resources->GetTexture( texture_id ).getSize().y;
	}
	tex_coords = coords;
	sprite.setTextureRect( sf::IntRect( tex_coords[0], tex_coords[1], tex_coords[2], tex_coords[3] ));
	SetSize( tex_coords[2], tex_coords[3] );
	sprite.setOrigin( tex_coords[2]/2, tex_coords[3]/2 );
}

void Sprite::SetTextureCoords( float u0, float v0, float u1, float v1 ) {
	SetTextureCoords( glm::vec4( u0, v0, u1, v1 ));
}

void Sprite::SetRotation( float r ) {
	rotation = r;
	shape.setRotation( rotation );
	sprite.setRotation( -rotation );
	TransformVertices();
}

void Sprite::SetPosition( float x, float y ) {
	position.x = x;
	position.y = y;
	shape.setPosition( position.x, position.y );
	sprite.setPosition( position.x, position.y );
	TransformVertices();
}

void Sprite::SetPosition( glm::vec2 pos ) {
	SetPosition( pos.x, pos.y );
}

void Sprite::SetColor( glm::vec4 color ) {
	Sprite::color = color;
	sprite.setColor( sf::Color( color[0], color[1], color[2], color[3] ));
	//shape.setFillColor( sf::Color( color[0], color[1], color[2], 100  ));
}

void Sprite::SetColor( int r, int g, int b, int a ) {
	SetColor( glm::vec4(r,g,b,a ));
}

void Sprite::SetColor( sf::Color color ) {
	Sprite::color[0] = color.r;
	Sprite::color[1] = color.b;
	Sprite::color[2] = color.b;
	Sprite::color[3] = color.a;
	sprite.setColor( color );
	//shape.setFillColor( sf::Color( color.r, color.g, color.b, 100  ));

}

void Sprite::SetSize( float width , float height ) {
	m_size = glm::vec2( width, height );
	sprite.setPosition( m_size.x/2,m_size.y/2);
}

void Sprite::SetOrigin( float x, float y ) {
	origin.x = x;
	origin.y = y;
	sprite.setOrigin( origin.x, origin.y );
}

void Sprite::SetOrigin( glm::vec2 origin ) {
	if( Shape::origin != origin )
		SetOrigin( origin.x, origin.y );
}

glm::vec2 Sprite::GetSize() {
	return m_size;
}

void Sprite::FlipHorizontal() {
	//sf::intrect r = sprite.gettexturerect();
	//sprite.settexturerect( sf::intrect( r.left+r.width, r.top, -r.width, r.height ));
	sf::Vector2f tmp_scale = sprite.getScale();
	sprite.setScale( -tmp_scale.x, tmp_scale.y );
}

void Sprite::FlipVertical() {
	sf::Vector2f tmp_scale = sprite.getScale();
	sprite.setScale( tmp_scale.x, -tmp_scale.y );
}

void Sprite::FlipDiagonal() {
	sprite.setRotation( 90 );
}


/* 	animation 	*/

bool Sprite::IsAnimated() {
	return animation.CountFrames() > 0;
}

void Sprite::Animate( float t_dt ) {
	if( animation.CountFrames() > 0 ) {
		animation.Animate( t_dt );
	}
}

void Sprite::ClearAnimation() {
	animation.ClearAnimation();
}

void Sprite::Play() {
	animation.Play();
}

void Sprite::Pause() {
	animation.Pause();
}

void Sprite::Stop() {
	animation.Stop();
}
//bool Sprite::IsAnimated() {
//	return m_frames.size() > 0;
//}
//
//void Sprite::Animate( float t_dt ) {
//	if( m_play && !m_pause ) {
//		if( m_current_frame_index < m_frames.size() ) {
//			m_elapsed_time += t_dt;
//			if( m_elapsed_time > animation_speed * std::get<0>( m_frames[ m_current_frame_index ] )) {
//				m_current_frame_index++;
//			}
//		} else {
//			if( !loop ) {
//				m_play = false;
//				m_pause = false;
//			}
//			m_current_frame_index 	= 0;
//			m_elapsed_time		= 0;
//		}
//		SetTextureCoords( std::get<1>( m_frames[ m_current_frame_index ] ));
//	}
//}
//
//void Sprite::ClearAnimation() {
//	m_frames.clear();
//}
//
//void Sprite::AddFrame( float t_duration, glm::vec4 t_tex_coords ) {
//	m_frames.push_back( {t_duration, t_tex_coords } );
//}
//
//void Sprite::Play() {
//	m_play = true;
//	m_pause = false;
//}
//
//void Sprite::Pause() {
//	m_pause = true;
//}
//
//void Sprite::Stop() {
//	m_play = false;
//	m_pause = false;
//}
