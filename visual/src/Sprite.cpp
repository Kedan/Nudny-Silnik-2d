#include <Tool.h>
#include <Sprite.h>

using namespace nudny;

void Sprite::Print() {
	std::cout << "SPRITE: " 
		<< m_gid
		<< "\ttexture: " << mp_texture
		<< "\tsf::Sptite: " << &m_sprite
		<< "\n";
};

Sprite::Sprite( int t_gid ) {
	m_gid = t_gid;
	Reset();
	SetDensity();
	SetFriction();
	SetColor( 255,255,255,255);
	fixture.shape 		= &m_bound;
	InitAnimation();
	animation->SetSprite( m_sprite );
	m_shape.setFillColor(sf::Color(255,0,0,123));
}

Sprite::Sprite( const sf::Texture& t_texture,  int t_gid ) {
	m_gid = t_gid;	
	Reset();
	SetDensity();
	SetFriction();
	SetColor(255,255,255,255);
	SetTexture( t_texture );
      	SetTextureCoords();	
	fixture.shape 		= &m_bound;
	InitAnimation();
	animation->SetSprite( m_sprite );
	m_shape.setFillColor(sf::Color(255,0,0,123));
}

Sprite::Sprite( const sf::Texture* t_texture,  int t_gid ) {
	m_gid = t_gid;	
	Reset();
	SetDensity();
	SetFriction();
	SetColor(255,255,255,255);
	SetTexture( t_texture );
	SetTextureCoords();
	fixture.shape 		= &m_bound;
	InitAnimation();
	animation->SetSprite( m_sprite );
	m_shape.setFillColor(sf::Color(255,0,0,123));
}

Sprite::Sprite( const Sprite& t_sprite ) {
	Reset();
	m_gid		= t_sprite.m_gid;
	m_sprite 	= t_sprite.m_sprite;
	SetDensity(		t_sprite.fixture.density );
	SetFriction(		t_sprite.fixture.friction );
	SetTexture( 		t_sprite.mp_texture );
	SetTextureCoords( 	t_sprite.m_tex_coords );
	//SetSize( 		t_sprite.m_size.x, t_sprite.m_size.y );
	if( t_sprite.m_vertices.size() > 2 ) {
		SetVertices( t_sprite.m_vertices ); // ! before postion & rotation
	}
	SetPosition( t_sprite.m_position.x, t_sprite.m_position.y );
	SetRotation( t_sprite.m_rotation );
	SetColor( t_sprite.m_color );
	collide			= t_sprite.collide;
	fixture.shape 		= &m_bound;
	animation.reset( t_sprite.animation.get() );
	animation->SetSprite( m_sprite );
}

void Sprite::InitAnimation() {
	animation.reset( new SpriteAnimation() );
}

void Sprite::ShowCollisionShape( bool t_show ) {
	m_show_collision_shape = t_show;
}

int Sprite::GetGid() {
	return m_gid;
}

//const std::unique_ptr<SpriteAnimation>& Sprite::GetAnimation() const 
//	return animation;
//}

const sf::Sprite& Sprite::GetSprite() const {
	return m_sprite;
}

void Sprite::SetSize( float t_width, float t_height ) {
	m_size.x = t_width;
	m_size.y = t_height;
	m_sprite.setPosition( m_size.x * 0.5f, m_size.y * 0.5f );
}

void Sprite::SetSize( glm::vec2 t_size ) {
	SetSize( t_size.x, t_size.y );
}

glm::vec2 Sprite::GetSize() {
	return m_size;
}

Sprite*	Sprite::CloneStrict() {
	return new Sprite( *this );
}

Shape* Sprite::Clone() {
	return new Sprite( *this );
}

const sf::Drawable* Sprite::GetDrawable() const {
	return &m_sprite;
}

const sf::Transformable* Sprite::GetTransformable() const {
	return &m_sprite;
}

void Sprite::AddBodyCoords( float t_x, float t_y, float t_rotation ) {
	m_transform = sf::Transform::Identity;
	m_transform.translate( t_x, t_y );
	m_transform.rotate( t_rotation );
}

void Sprite::Draw( sf::RenderWindow& t_window ) {
	t_window.draw( m_sprite );
//	if( m_show_collision_shape )
		t_window.draw( m_shape );
//	t_window.draw( m_sprite, m_transform );
//	if( m_show_collision_shape )
//		t_window.draw( m_shape, m_transform );
}

void Sprite::Draw( sf::RenderWindow& t_window, sf::Transform& t_transform ) {
	//TODO m_transform + t_transform
	t_window.draw( m_sprite, t_transform );
//	if( m_show_collision_shape )
		t_window.draw( m_shape, t_transform );
}

void Sprite::SetColor( sf::Color& t_color ) {
	m_color = glm::vec4( t_color.r, t_color.g, t_color.b, t_color.a );
	m_sprite.setColor( t_color );
}

void Sprite::SetColor( int r, int g, int b, int a ) {	
	SetColor( glm::vec4(r,g,b,a ));
}

void Sprite::SetColor( glm::vec4 t_color ) {
	m_color = t_color;
	m_sprite.setColor( sf::Color( t_color.x, t_color.y, t_color.z, t_color.w ) );
}

void Sprite::SetAlpha( int t_alpha) {
	SetColor( m_color.a, m_color.y, m_color.z, t_alpha );
}

int Sprite::GetAlpha() {
	return m_color.w;
}

void Sprite::SetVisible( bool t_visible ) {
	SetAlpha( t_visible ? 256 : 0 );
}

glm::vec4 Sprite::GetColor() {
	return m_color;
}

glm::vec4 Sprite::GetRGBA() {
	return GetColor();
}

glm::vec3 Sprite::GetRGB() {
	return glm::vec3( m_color );
}

const sf::Color& Sprite::GetColorsf() {
	return m_sprite.getColor();
}

void Sprite::SetTexture( const sf::Texture* t_texture ) {
	mp_texture = t_texture;
	m_sprite.setTexture( *mp_texture );
}

void Sprite::SetTexture( const sf::Texture& t_tex ) {
	mp_texture = &t_tex;
	m_sprite.setTexture( *mp_texture );
}

void Sprite::SetTextureCoords( void ) {
	SetTextureCoords(0,0,0,0);
}

void Sprite::SetTextureCoords( glm::vec4 t_coords ) {
	if( mp_texture && t_coords[0]==0 && t_coords[1]==0 && t_coords[2] == 0 && t_coords[3]==0 ) {
		t_coords[2] = mp_texture->getSize().x;
		t_coords[3] = mp_texture->getSize().y;
	}
	m_tex_coords = t_coords;
	m_sprite.setTextureRect( sf::IntRect( m_tex_coords[0], m_tex_coords[1], m_tex_coords[2], m_tex_coords[3] ));
	SetSize( m_tex_coords[2], m_tex_coords[3] );
	m_sprite.setOrigin( m_tex_coords[2]/2, m_tex_coords[3]/2 );
}

void Sprite::SetTextureCoords( const sf::IntRect& t_rect ) {
	m_sprite.setTextureRect( t_rect );
	m_tex_coords.x = t_rect.left;
	m_tex_coords.y = t_rect.top;
	m_tex_coords.z = t_rect.width;
	m_tex_coords.w = t_rect.height;
}

void Sprite::SetTextureCoords( float u0, float v0, float u1, float v1 ) {
	SetTextureCoords( glm::vec4( u0, v0, u1, v1 ));
}

const sf::Texture* Sprite::GetTexture() {
	return m_sprite.getTexture();
}

glm::vec4 Sprite::GetTextureCoords() {
	return m_tex_coords;
}

const sf::IntRect& Sprite::GetTextureCoordssf() {
	return m_sprite.getTextureRect();
}

void Sprite::SetOrigin( float t_x, float t_y ) {
	m_origin.x = t_x;
	m_origin.y = t_y;
	m_sprite.setOrigin( m_origin.x, m_origin.y );
}

void Sprite::SetOrigin( glm::vec2 t_origin ) {
	SetOrigin( t_origin.x, t_origin.y );
}
//
void Sprite::SetPosition( float t_x, float t_y ) {
	m_position.x = t_x;
	m_position.y = t_y;
	m_shape.setPosition( m_position.x, m_position.y );
	m_sprite.setPosition( m_position.x, m_position.y );
	TransformVertices();
}

void Sprite::SetPosition( glm::vec2 t_position ) {
	SetPosition( t_position.x, t_position.y );
}
//
void Sprite::SetRotation( float t_rotation ) {
	m_rotation = t_rotation;
	m_shape.setRotation( t_rotation );
	m_sprite.setRotation( -t_rotation );
	TransformVertices();
}
//
void Sprite::SetScale( float t_x, float t_y ) {
//	m_scale.x = t_x;
//	m_scale.y = t_y;
//	m_shape.setScale( sf::Vector2f( t_x, t_y ));
//	m_sprite.setScale( sf::Vector2f( t_x, t_y ));
//	//TODO
//	TransformVertices();
}

void Sprite::SetScale( glm::vec2 t_scale ) {
	SetScale( t_scale.x, t_scale.y );	
}

glm::vec2 Sprite::GetOrigin() {
	return m_origin;
}

glm::vec2 Sprite::GetPosition() {
	return m_position;
}

float Sprite::GetRotation() {
	return m_rotation;
}

glm::vec2 Sprite::GetScale() {
	return m_scale;
}

void Sprite::FlipHorizontal() {
	m_scale.x = -m_scale.x;
	m_shape.setScale( sf::Vector2f( m_scale.x, m_scale.y ));
	m_sprite.setScale( sf::Vector2f( m_scale.x, m_scale.y ));
	m_vertices_transformed = FlipVerticesHorizontal( m_vertices_transformed, 0.0f );
	SetVertices( m_vertices_transformed );
}
//
void Sprite::FlipVertical() {
	m_scale.y = -m_scale.y;
	m_shape.setScale( sf::Vector2f( m_scale.x, m_scale.y ));
	m_sprite.setScale( sf::Vector2f( m_scale.x, m_scale.y ));
	m_vertices_transformed = FlipVerticesVertical( m_vertices_transformed, 0.0f );
	SetVertices( m_vertices_transformed );
}
//
void Sprite::FlipDiagonal() {
	m_scale.x = -m_scale.x;
	m_scale.y = -m_scale.y;
	m_shape.setScale( sf::Vector2f( m_scale.x, m_scale.y ));
	m_sprite.setScale( sf::Vector2f( m_scale.x, m_scale.y ));
	m_vertices_transformed = FlipVerticesDiagonal( m_vertices_transformed, glm::vec2(0,0) );
	SetVertices( m_vertices_transformed );
}

void Sprite::Play() {
	animation->Play();
}

void Sprite::Pause() {
	animation->Pause();
}

void Sprite::Stop() {
	animation->Stop();
}

void Sprite::Loop( bool t_loop ) {
	animation->Loop( t_loop );
}

bool Sprite::IsPaused() {
	return animation->IsPaused();
}

bool Sprite::IsPlaying() {
	return animation->IsPlaying();
}

bool Sprite::IsLooped() {
	return animation->IsLooped();
}
void Sprite::Animate( sf::Time& t_dt ) {
	if( animation->CountFrames() > 0 ) {
		animation->Animate( t_dt );
	}
}
