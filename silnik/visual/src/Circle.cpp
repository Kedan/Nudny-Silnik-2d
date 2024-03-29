#include "Circle.h"

using namespace n2d;

Circle::Circle() {
	SetDensity();
	SetFriction();
	SetRadius();
	SetPosition();
	SetColor();
	fixture.shape = &bound;
}

Circle::Circle( const Circle& circle ) {
	SetDensity( circle.fixture.density );
	SetFriction( circle.fixture.friction );
	SetRadius( circle.radius );
	SetPosition( circle.position.x + circle.radius + 10.0f, circle.position.y );
	SetColor( circle.color );
	SetTexture( circle.texture_id );
	fixture.shape = &bound;
}

Shape* Circle::Clone() const {
	return new Circle(*this);
}

b2Shape* Circle::GetUpdatable() {
	return (b2Shape*)&bound;
}

sf::Drawable* Circle::GetDrawable()  {
	return (sf::Drawable*)&shape;
}

sf::Transformable* Circle::GetTransformable() {
	return (sf::Transformable*)&shape;
}

void Circle::Draw( sf::RenderWindow& w ) {
	w.draw( shape );
}

void Circle::Draw( sf::RenderWindow& w, sf::Transform& t ) {
	w.draw( shape, t );
}

void Circle::AddBodyCoords( float x, float y, float rotation ) {
	shape.setPosition( x, y );
	shape.setRotation( rotation + Shape::rotation );
}

void Circle::FixToBody() {
	SetOrigin( origin-position );
	bound.m_radius = Tool::Bf( radius );
	bound.m_p.Set( Tool::Bf( position.x ) , Tool::Bf( position.y ) );
}

void Circle::SetRadius( float r ) {
	radius = r;
	shape.setRadius( radius );
	SetOrigin( radius, radius );
}

void Circle::SetPosition( float x, float y ) {
	position.x = x;
	position.y = y;
	shape.setPosition( position.x, position.y );
}

void Circle::SetPosition( glm::vec2 pos ) {
	SetPosition( pos.x, pos.y );
}

void Circle::SetOrigin( float x, float y ) {
	origin.x = x;
	origin.y = y;
	shape.setOrigin( x, y );
}

void Circle::SetOrigin( glm::vec2 origin ) {
	SetOrigin( origin.x, origin.y );
}

void Circle::SetColor( glm::vec4 color ) {
	Circle::color = color;
	shape.setFillColor( sf::Color( color[0], color[1], color[2], color[3] ));
}

void Circle::SetColor( int r, int g, int b, int a ) {
	SetColor( glm::vec4(r,g,b,a ));
}

void Circle::SetColor( sf::Color color ) {
	Circle::color[0] = color.r;
	Circle::color[1] = color.b;
	Circle::color[2] = color.b;
	Circle::color[3] = color.a;
	shape.setFillColor( color );
}	

void Circle::SetTexture( int id ) {
	texture_id = id;
	shape.setTexture( mp_resources->GetTexturePtr( texture_id ));
}

void Circle::SetTexture( sf::Texture& t_texture ) {
	shape.setTexture( &t_texture );
}

void Circle::SetTexture( std::string texture_path ) {
	if( !mp_resources->IsTextureLoaded( texture_path ) ) {
		texture_id = mp_resources->LoadTexture( texture_path );
	}
	if( texture_id >= 0 ) {
		SetTexture( texture_id );
	}
	SetTextureCoords();
}

void Circle::SetTextureCoords( glm::vec4 coords ) {
	if( texture_id > -1 && coords[0]==0 && coords[1]==0 && coords[2] == 0 && coords[3]==0 ) {
		coords[2] = mp_resources->GetTexture( texture_id ).getSize().x;
		coords[3] = mp_resources->GetTexture( texture_id ).getSize().y;
	}
	tex_coords = coords;
	shape.setTextureRect( sf::IntRect( tex_coords[0], tex_coords[1], tex_coords[2], tex_coords[3] ));
}

void Circle::SetTextureCoords( float u0, float v0, float u1, float v1 ) {
	SetTextureCoords( glm::vec4( u0, v0, u1, v1 ));
}


void Circle::Animate( float t_dt ) {
}

void Circle::ClearAnimation() {
}

void Circle::Play() {
}

void Circle::Pause() {
}

void Circle::Stop() {
}

