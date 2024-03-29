#include "Rect.h"

using namespace n2d;

Rect::Rect() {
	SetDensity();
	SetFriction();
	SetSize();
	SetPosition();
	SetRotation();
	SetColor();
}

Rect::Rect( const Rect& rect ) {
	SetDensity( rect.fixture.density );
	SetFriction( rect.fixture.friction );
	SetSize( rect.size );
	SetPosition( rect.position.x + rect.size.x + 10.0f, rect.position.y );
	SetRotation( rect.rotation );
	SetColor( rect.color );
}

Shape* Rect::Clone() const {
	return new Rect( *this );
}

b2Shape* Rect::GetUpdatable() {
	return (b2Shape*)&bound;
}

sf::Drawable* Rect::GetDrawable()  {
	return (sf::Drawable*)&shape;
}

sf::Transformable* Rect::GetTransformable() {
	return (sf::Transformable*)&shape;
}

void Rect::Draw( sf::RenderWindow& w ) {
	w.draw( shape, m_transform );
}

void Rect::Draw( sf::RenderWindow& w, sf::Transform& t ) {
	w.draw( shape, t );
}

void Rect::AddBodyCoords( float x, float y, float r ) {
	m_transform = sf::Transform::Identity;
	m_transform.translate( x, y );
	m_transform.rotate( r );
	m_transform.translate( position.x, position.y );
	m_transform.rotate( rotation );
}

void Rect::FixToBody() {
	shape.setPosition( 0 ,0 );
	shape.setRotation( 0 );
	bound.SetAsBox( 
			Tool::Bf( size.x/2 ), Tool::Bf(size.y/2), 
			b2Vec2( Tool::Bf( position.x), Tool::Bf( position.y) ),
			Tool::rad( rotation ));
	fixture.shape = &bound;
}

void Rect::SetSize( float w, float h ) {
	size.x = w;
	size.y = h;
	shape.setSize(sf::Vector2f(size.x, size.y));
	SetOrigin( size*0.5f );
}

void Rect::SetSize( glm::vec2 size) {
	SetSize( size.x, size.y );
}

void Rect::SetRotation( float r ) {
	rotation = r;
	shape.setRotation( rotation );
	SetOrigin( size*0.5f );
}

void Rect::SetPosition( float x, float y ) {
	position.x = x;
	position.y = y;
	shape.setPosition( position.x, position.y );
}

void Rect::SetPosition( glm::vec2 pos ) {
	SetPosition( pos.x, pos.y );
}

void Rect::SetOrigin( float x, float y ) {
	origin.x = x;
	origin.y = y;
	shape.setOrigin( origin.x, origin.y );
}

void Rect::SetOrigin( glm::vec2 origin ) {
	if( Shape::origin != origin )
		SetOrigin( origin.x, origin.y );
}

void Rect::SetColor( glm::vec4 color ) {
	Rect::color = color;
	shape.setFillColor( sf::Color( color[0], color[1], color[2], color[3] ));
}

void Rect::SetColor( int r, int g, int b, int a ) {
	SetColor( glm::vec4(r,g,b,a ));
}

void Rect::SetColor( sf::Color color ) {
	Rect::color[0] = color.r;
	Rect::color[1] = color.b;
	Rect::color[2] = color.b;
	Rect::color[3] = color.a;
	shape.setFillColor( color );
}	

void Rect::SetTexture( int id ) {
	texture_id = id;
	shape.setTexture( mp_resources->GetTexturePtr( texture_id) );
	SetTextureCoords(0,0, mp_resources->GetTexturePtr( texture_id )->getSize().x, mp_resources->GetTexturePtr( texture_id )->getSize().y );
}

void Rect::SetTexture( sf::Texture& t_texture ) {
	shape.setTexture( &t_texture );
}

void Rect::SetTexture( std::string texture_path ) {
	texture_id = mp_resources->LoadTexture( texture_path );
	SetTexture( texture_id );
}

void Rect::SetTextureCoords( glm::vec4 coords ) {
	if( texture_id > -1 && coords[0]==0 && coords[1]==0 && coords[2] == 0 && coords[3]==0 ) {
		coords[2] = mp_resources->GetTexture( texture_id ).getSize().x;
		coords[3] = mp_resources->GetTexture( texture_id ).getSize().y;
	}
	tex_coords = coords;
	shape.setTextureRect( sf::IntRect( tex_coords[0], tex_coords[1], tex_coords[2], tex_coords[3] ));
}

void Rect::SetTextureCoords( float u0, float v0, float u1, float v1 ) {
	SetTextureCoords( glm::vec4( u0, v0, u1, v1 ));
}

void Rect::Animate( float t_dt ) {
}

void Rect::ClearAnimation() {
}

void Rect::Play() {
}

void Rect::Pause() {
}

void Rect::Stop() {
}
