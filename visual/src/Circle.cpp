#include "Circle.h"

using namespace nudny;

Circle::Circle() {
	SetDensity();
	SetFriction();
	SetRadius();
	SetPosition( 0, 0 );
	SetColor( 120, 120, 250, 255 );
	fixture.shape = &m_bound;
};

Circle::Circle( const Circle& circle ) {
	fixture = circle.fixture;
	SetRadius( circle.m_radius );
	SetPosition( circle.m_position );
	SetColor( circle.m_color );
	if( circle.mp_texture ) {
		SetTexture( circle.mp_texture );
	}
	fixture.shape = &m_bound;
}

void Circle::SetRadius( const float& t_radius ) {
	m_radius = t_radius;
	m_shape.setRadius( m_radius );
	SetOrigin( m_radius, m_radius );
}

Circle* Circle::CloneStrict() const {
	return new Circle( *this );
}

Shape* Circle::Clone() const {
	return new Circle( *this );
}

float Circle::GetRadius() {
	return m_radius;
}

const b2Shape* Circle::GetUpdatable() const {
	return &m_bound;
}

const sf::Drawable* Circle::GetDrawable() const {
	return &m_shape;
}

const sf::Transformable* Circle::GetTransformable() const {
	return &m_shape;
}

void Circle::AddBodyCoords( float t_x, float t_y, float t_rotation ) {
	m_shape.setPosition( t_x, t_y );
	m_shape.setRotation( t_rotation + m_rotation );
}

void Circle::FixToBody() {
	SetOrigin( m_origin - m_position );
	m_bound.m_radius = Tool::Bf( m_radius );
	m_bound.m_p.Set( Tool::Bf( m_position.x ), Tool::Bf( m_position.y ));
}

void Circle::Draw( sf::RenderWindow& t_window ) {
	t_window.draw( m_shape );
}

void Circle::Draw( sf::RenderWindow& t_window, sf::Transform& t_transform ) {
	t_window.draw( m_shape, t_transform );
}

void Circle::SetColor( sf::Color& t_color ) {
	m_shape.setFillColor( t_color );
	m_color = glm::vec4( t_color.r, t_color.g, t_color.b, t_color.a );
}

void Circle::SetColor( int r, int g, int b, int a ) {
	SetColor( glm::vec4(r,g,b,a ));
}

void Circle::SetColor( glm::vec4 t_color ) {
	m_color = t_color;
	m_shape.setFillColor( sf::Color( t_color.x, t_color.y, t_color.z, t_color.w ) );
}

void Circle::SetAlpha( int t_alpha) {
	SetColor( m_color.a, m_color.y, m_color.z, t_alpha );
}

int Circle::GetAlpha() {
	return m_color.w;
}

void Circle::SetVisible( bool t_visible ) {
	SetAlpha( t_visible ? 256 : 0 );
}

glm::vec4 Circle::GetColor() {
	return m_color;
}

glm::vec4 Circle::GetRGBA() {
	return GetColor();
}

glm::vec3 Circle::GetRGB() {
	return glm::vec3( m_color );
}

const sf::Color& Circle::GetColorsf() {
	return m_shape.getFillColor();
}

void Circle::SetTexture( const sf::Texture* t_texture ) {
	mp_texture = t_texture;
	m_shape.setTexture( t_texture );
}

void Circle::SetTextureCoords( glm::vec4 t_coords ) {
	if( t_coords[0]==0 && t_coords[1]==0 && t_coords[2] == 0 && t_coords[3]==0 ) {
		t_coords[2] = mp_texture->getSize().x;
		t_coords[3] = mp_texture->getSize().y;
	}
	m_tex_coords = t_coords;
	m_shape.setTextureRect( sf::IntRect( m_tex_coords[0], m_tex_coords[1], m_tex_coords[2], m_tex_coords[3] ));
}

void Circle::SetTextureCoords( const sf::IntRect& t_rect ) {
	m_shape.setTextureRect( t_rect );
	m_tex_coords.x = t_rect.left;
	m_tex_coords.y = t_rect.top;
	m_tex_coords.z = t_rect.width;
	m_tex_coords.w = t_rect.height;
}

void Circle::SetTextureCoords( float u0, float v0, float u1, float v1 ) {
	SetTextureCoords( glm::vec4( u0, v0, u1, v1 ));
}

const sf::Texture* Circle::GetTexture() {
	return m_shape.getTexture();
}

glm::vec4 Circle::GetTextureCoords() {
	return m_tex_coords;
}

const sf::IntRect& Circle::GetTextureCoordssf() {
	return m_shape.getTextureRect();
}

void Circle::SetOrigin( float t_x, float t_y ) {
	m_origin.x = t_x;
	m_origin.y = t_y;
	m_shape.setOrigin( m_origin.x, m_origin.y );
}

void Circle::SetOrigin( glm::vec2 t_origin ) {
	SetOrigin( t_origin.x, t_origin.y );
}

void Circle::SetPosition( float t_x, float t_y ) {
	m_position.x = t_x;
	m_position.y = t_y;
	m_shape.setPosition( m_position.x, m_position.y );
}

void Circle::SetPosition( glm::vec2 t_position ) {
	SetPosition( t_position.x, t_position.y );
}

void Circle::SetRotation( float t_rotation ) {
	m_rotation = t_rotation;
	m_shape.setRotation( t_rotation );
}

void Circle::SetScale( float t_x, float t_y ) {
	m_scale.x = t_x;
	m_scale.y = t_y;
	m_shape.setScale( sf::Vector2f( t_x, t_y ));
}

void Circle::SetScale( glm::vec2 t_scale ) {
	SetScale( t_scale.x, t_scale.y );	
}

glm::vec2 Circle::GetOrigin() {
	return m_origin;
}

glm::vec2 Circle::GetPosition() {
	return m_position;
}

float Circle::GetRotation() {
	return m_rotation;
}

glm::vec2 Circle::GetScale() {
	return m_scale;
}

void Circle::FlipHorizontal() {
	m_scale.x = -m_scale.x;
	m_shape.setScale( sf::Vector2f( m_scale.x, m_scale.y ));
}

void Circle::FlipVertical() {
	m_scale.y = -m_scale.y;
	m_shape.setScale( sf::Vector2f( m_scale.x, m_scale.y ));
}

void Circle::FlipDiagonal() {
	m_scale.x = -m_scale.x;
	m_scale.y = -m_scale.y;
	m_shape.setScale( sf::Vector2f( m_scale.x, m_scale.y ));}

void Circle::Animate( sf::Time& t_dt ) {
}
