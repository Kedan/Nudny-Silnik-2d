#include <Rectangle.h>

using namespace nudny;

Rectangle::Rectangle() {
	SetDensity();
	SetFriction();
	SetSize( 50.0f, 50.0f );
	SetPosition( 0, 0 );
	SetRotation( 0 );
	SetColor( 100, 250, 150, 255 );	
	fixture.shape = &m_bound;
}

Rectangle::Rectangle( const Rectangle& t_rectangle ) {
	fixture = t_rectangle.fixture;
	SetSize( t_rectangle.m_size );
	SetPosition( t_rectangle.m_position.x, t_rectangle.m_position.y );
	SetRotation( t_rectangle.m_rotation );
	SetColor( t_rectangle.m_color );
	if( t_rectangle.mp_texture ) {
		SetTexture( t_rectangle.mp_texture );
	}
	fixture.shape = &m_bound;
}

void Rectangle::SetSize( float t_width, float t_height ) {
	m_size.x = t_width;
	m_size.y = t_height;
	m_shape.setSize(sf::Vector2f(m_size.x, m_size.y));
	SetOrigin( m_size*0.5f );
}

void Rectangle::SetSize( glm::vec2 t_size) {
	SetSize( t_size.x, t_size.y );
}

glm::vec2 Rectangle::GetSize() {
	return m_size;
}

float Rectangle::GetWidth() {
	return m_size.x;
}

float Rectangle::GetHeight() {
	return m_size.y;
}

Rectangle* Rectangle::CloneStrict() const {
	return new Rectangle(*this);
}

const b2Shape* Rectangle::GetUpdatable() const {
	return &m_bound;
}

const sf::Drawable* Rectangle::GetDrawable() const {
	return &m_shape;
}

const sf::Transformable* Rectangle::GetTransformable() const {
	return &m_shape;
}

Shape* Rectangle::Clone() const {
	return new Rectangle(*this);
}

void Rectangle::AddBodyCoords( float t_x, float t_y, float t_rotation ) {
	m_transform = sf::Transform::Identity;
	m_transform.translate( t_x, t_y );
	m_transform.rotate( t_rotation );
	m_transform.translate( m_position.x, m_position.y );
	m_transform.rotate( m_rotation );
}

void Rectangle::FixToBody() {
	m_shape.setPosition( 0 ,0 );
	m_shape.setRotation( 0 );
	m_bound.SetAsBox( 
			Tool::Bf( m_size.x/2 ), Tool::Bf( m_size.y/2), 
			b2Vec2( Tool::Bf( m_position.x), Tool::Bf( m_position.y) ),
			Tool::rad( m_rotation ));
	fixture.shape = &m_bound;
}

void Rectangle::Draw( sf::RenderWindow& t_window ) {
	if( m_visible ) {
		t_window.draw( m_shape, m_transform );
	}
}

void Rectangle::Draw( sf::RenderWindow& t_window, sf::Transform& t_transform ) {
	if( m_visible ) {
		//TODO
		t_window.draw( m_shape, m_transform );
	}
}

void Rectangle::SetColor( sf::Color& t_color ) {
	m_shape.setFillColor( t_color );
	m_color = glm::vec4( t_color.r, t_color.g, t_color.b, t_color.a );
}

void Rectangle::SetColor( int r, int g, int b, int a ) {
	SetColor( glm::vec4(r,g,b,a ));
}

void Rectangle::SetColor( glm::vec4 t_color ) {
	m_color = t_color;
	m_shape.setFillColor( sf::Color( t_color.x, t_color.y, t_color.z, t_color.w ) );
}

void Rectangle::SetAlpha( int t_alpha) {
	SetColor( m_color.a, m_color.y, m_color.z, t_alpha );
}

int Rectangle::GetAlpha() {
	return m_color.w;
}

void Rectangle::SetVisible( bool t_visible ) {
	SetAlpha( t_visible ? 256 : 0 );
}

glm::vec4 Rectangle::GetColor() {
	return m_color;
}

glm::vec4 Rectangle::GetRGBA() {
	return GetColor();
}

glm::vec3 Rectangle::GetRGB() {
	return glm::vec3( m_color );
}

const sf::Color& Rectangle::GetColorsf() {
	return m_shape.getFillColor();
}

void Rectangle::SetTexture( const sf::Texture* t_texture ) {
	mp_texture = t_texture;
	m_shape.setTexture( t_texture );
}

void Rectangle::SetTextureCoords( glm::vec4 t_coords ) {
	if( t_coords[0]==0 && t_coords[1]==0 && t_coords[2] == 0 && t_coords[3]==0 ) {
		t_coords[2] = mp_texture->getSize().x;
		t_coords[3] = mp_texture->getSize().y;
	}
	m_tex_coords = t_coords;
	m_shape.setTextureRect( sf::IntRect( m_tex_coords[0], m_tex_coords[1], m_tex_coords[2], m_tex_coords[3] ));
}

void Rectangle::SetTextureCoords( const sf::IntRect& t_rect ) {
	m_shape.setTextureRect( t_rect );
	m_tex_coords.x = t_rect.left;
	m_tex_coords.y = t_rect.top;
	m_tex_coords.z = t_rect.width;
	m_tex_coords.w = t_rect.height;
}

void Rectangle::SetTextureCoords( float u0, float v0, float u1, float v1 ) {
	SetTextureCoords( glm::vec4( u0, v0, u1, v1 ));
}

const sf::Texture* Rectangle::GetTexture() {
	return m_shape.getTexture();
}

glm::vec4 Rectangle::GetTextureCoords() {
	return m_tex_coords;
}

const sf::IntRect& Rectangle::GetTextureCoordssf() {
	return m_shape.getTextureRect();
}

void Rectangle::SetOrigin( float t_x, float t_y ) {
	m_origin.x = t_x;
	m_origin.y = t_y;
	m_shape.setOrigin( m_origin.x, m_origin.y );
}

void Rectangle::SetOrigin( glm::vec2 t_origin ) {
	if( m_origin != t_origin )
		SetOrigin( t_origin.x, t_origin.y );
}

void Rectangle::SetPosition( float t_x, float t_y ) {
	m_position.x = t_x;
	m_position.y = t_y;
	m_shape.setPosition( m_position.x, m_position.y );
}

void Rectangle::SetPosition( glm::vec2 t_position ) {
	SetPosition( t_position.x, t_position.y );
}

void Rectangle::SetRotation( float t_rotation ) {
	m_rotation = t_rotation;
	m_shape.setRotation( m_rotation );
	SetOrigin( m_size*0.5f );
}

void Rectangle::SetScale( float t_x, float t_y ) {
	m_scale.x = t_x;
	m_scale.y = t_y;
	m_shape.setScale( sf::Vector2f( t_x, t_y ));
}

void Rectangle::SetScale( glm::vec2 t_scale ) {
	SetScale( t_scale.x, t_scale.y );	
}

glm::vec2 Rectangle::GetOrigin() {
	return m_origin;
}

glm::vec2 Rectangle::GetPosition() {
	return m_position;
}

float Rectangle::GetRotation() {
	return m_rotation;
}

glm::vec2 Rectangle::GetScale() {
	return m_scale;
}

void Rectangle::FlipHorizontal() {
	m_scale.x = -m_scale.x;
	m_shape.setScale( sf::Vector2f( m_scale.x, m_scale.y ));
}

void Rectangle::FlipVertical() {
	m_scale.y = -m_scale.y;
	m_shape.setScale( sf::Vector2f( m_scale.x, m_scale.y ));
}

void Rectangle::FlipDiagonal() {
	m_scale.x = -m_scale.x;
	m_scale.y = -m_scale.y;
	m_shape.setScale( sf::Vector2f( m_scale.x, m_scale.y ));}

void Rectangle::Animate( sf::Time& t_dt ) {
}

