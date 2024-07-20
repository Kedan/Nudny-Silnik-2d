#include <Polygon.h>

using namespace nudny;

Polygon::Polygon() {
//	fixture.shape = &m_bound;
}

Polygon::Polygon( std::vector<glm::vec2> t_vertices ) {
//	Reset();
	SetDensity();
	SetFriction();
	SetVertices( t_vertices ); // before position & rotation
	SetPosition( 0, 0);
	SetRotation( 0 );
	SetColor( 255,255,255,255);
	fixture.shape 		= &m_bound;
}

Polygon::Polygon( const Polygon& t_poly ) {
//	Reset();
	SetDensity( t_poly.fixture.density );
	SetFriction( t_poly.fixture.friction );
	//SetOrigin( t_poly.m_origin );
	SetVertices( t_poly.m_vertices ); // ! before postion & rotation
	SetPosition( t_poly.m_position.x, t_poly.m_position.y );
	SetRotation( t_poly.m_rotation );
	if( t_poly.mp_texture ) {
		SetTexture( t_poly.mp_texture );
	}
	SetColor( t_poly.m_color );
	fixture.shape 		= &m_bound;

}

void Polygon::Print() {
	int i = 0;
	std::cout << "Vertices:\n";
	for( auto v : m_vertices ) {
		std::cout << i << "["<< v.x <<","<< v.y <<"]\n";
	}
	std::cout << "Transformed Vertices:\n";
	for( auto v : m_vertices_transformed ) {
		std::cout << i << "["<< v.x <<","<< v.y <<"]\n";
	}
}

void Polygon::SetVertices( std::vector<glm::vec2> t_vertices ) {
	if( collide && t_vertices.size() > 2 ) {
		m_vertices = t_vertices;
		m_vertices_transformed = m_vertices;
		TransformVertices();
	} 
}

void Polygon::TransformVertices() {
	if( m_vertices.size()>2 ) {
		Reset();
		m_shape.setPointCount(m_vertices.size());
		if( !(m_position.x==0 && m_position.y==0 && m_rotation==0 )) {
			m_vertices_transformed = Tool::Transform( m_vertices, m_position, m_rotation );
			int i=0;
			for( auto& vertex : m_vertices_transformed ) {
				m_shape.setPoint( i, sf::Vector2f( vertex.x, vertex.y ));
				m_b2_vertices.push_back( b2Vec2( Tool::Bf( vertex.x), Tool::Bf(vertex.y )));
				i++;
			}
		} else {
			m_vertices_transformed = m_vertices;
			int i = 0;
			for( auto& vertex : m_vertices_transformed ) {
				m_shape.setPoint( i, sf::Vector2f( vertex.x, vertex.y ));
				m_b2_vertices.push_back( b2Vec2( Tool::Bf( vertex.x), Tool::Bf(vertex.y )));
				i++;
			}
		}
		m_bound.Set(m_b2_vertices.data(),m_b2_vertices.size());
	}
}

void Polygon::Reset() {
	m_vertices_transformed.clear();
	m_b2_vertices.clear();
}

Polygon* Polygon::CloneStrict() const {
	return new Polygon(*this);
}

const b2Shape* Polygon::GetUpdatable() const {
	return &m_bound;
}


const sf::Drawable* Polygon::GetDrawable() const {
	return &m_shape;
}

const sf::Transformable* Polygon::GetTransformable() const {
	return &m_shape;
}


Shape* Polygon::Clone() const {
	return new Polygon(*this);
}

void Polygon::AddBodyCoords( float t_x, float t_y, float t_rotation ) {
	m_transform = sf::Transform::Identity;
	m_transform.translate( t_x, t_y );
	m_transform.rotate( t_rotation );
}


void Polygon::FixToBody() {
	m_is_fixed_to_body = true;
	m_shape.setPosition( 0 ,0 );
	m_shape.setRotation( 0 );
}

//
void Polygon::Draw( sf::RenderWindow& t_window ) {
	//t_window.draw( m_shape, m_transform );
	t_window.draw( m_shape );
}

//
void Polygon::Draw( sf::RenderWindow& t_window, sf::Transform& t_transform ) {
	//TODO m_transform + t_transform
	t_window.draw( m_shape, t_transform );
}

//
void Polygon::SetColor( sf::Color& t_color ) {
	m_shape.setFillColor( t_color );
	m_color = glm::vec4( t_color.r, t_color.g, t_color.b, t_color.a );
}

void Polygon::SetColor( int r, int g, int b, int a ) {	
	SetColor( glm::vec4(r,g,b,a ));
}
//
void Polygon::SetColor( glm::vec4 t_color ) {
	m_color = t_color;
	m_shape.setFillColor( sf::Color( t_color.x, t_color.y, t_color.z, t_color.w ) );
}

void Polygon::SetAlpha( int t_alpha) {
	SetColor( m_color.a, m_color.y, m_color.z, t_alpha );
}

int Polygon::GetAlpha() {
	return m_color.w;
}

void Polygon::SetVisible( bool t_visible ) {
	SetAlpha( t_visible ? 256 : 0 );
}

glm::vec4 Polygon::GetColor() {
	return m_color;
}

glm::vec4 Polygon::GetRGBA() {
	return GetColor();
}

glm::vec3 Polygon::GetRGB() {
	return glm::vec3( m_color );
}

//
const sf::Color& Polygon::GetColorsf() {
	return m_shape.getFillColor();
}

void Polygon::SetTexture( const sf::Texture* t_texture ) {
	mp_texture = t_texture;
	m_shape.setTexture( t_texture );
	SetTextureCoords(0,0,0,0);
}

//
void Polygon::SetTextureCoords( glm::vec4 t_coords ) {
	if( t_coords[0]==0 && t_coords[1]==0 && t_coords[2] == 0 && t_coords[3]==0 ) {
		t_coords[2] = mp_texture->getSize().x;
		t_coords[3] = mp_texture->getSize().y;
	}
	m_tex_coords = t_coords;
	m_shape.setTextureRect( sf::IntRect( m_tex_coords[0], m_tex_coords[1], m_tex_coords[2], m_tex_coords[3] ));
}
//
void Polygon::SetTextureCoords( const sf::IntRect& t_rect ) {
	m_shape.setTextureRect( t_rect );
	m_tex_coords.x = t_rect.left;
	m_tex_coords.y = t_rect.top;
	m_tex_coords.z = t_rect.width;
	m_tex_coords.w = t_rect.height;
}

void Polygon::SetTextureCoords( float u0, float v0, float u1, float v1 ) {
	SetTextureCoords( glm::vec4( u0, v0, u1, v1 ));
}
//
const sf::Texture* Polygon::GetTexture() {
	return m_shape.getTexture();
}

glm::vec4 Polygon::GetTextureCoords() {
	return m_tex_coords;
}
//
const sf::IntRect& Polygon::GetTextureCoordssf() {
	return m_shape.getTextureRect();
}
//
void Polygon::SetOrigin( float t_x, float t_y ) {
	m_origin.x = t_x;
	m_origin.y = t_y;
	m_shape.setOrigin( m_origin.x, m_origin.y );
}

void Polygon::SetOrigin( glm::vec2 t_origin ) {
	SetOrigin( t_origin.x, t_origin.y );
}
//
void Polygon::SetPosition( float t_x, float t_y ) {
	m_position.x = t_x;
	m_position.y = t_y;
	m_shape.setPosition( m_position.x, m_position.y );
	if( m_is_fixed_to_body ) {
		TransformVertices();
	}
}

void Polygon::SetPosition( glm::vec2 t_position ) {
	SetPosition( t_position.x, t_position.y );
}
//
void Polygon::SetRotation( float t_rotation ) {
	m_rotation = t_rotation;
	m_shape.setRotation( t_rotation );
	if(m_is_fixed_to_body ) {
		TransformVertices();
	}
}
//
void Polygon::SetScale( float t_x, float t_y ) {
	m_scale.x = t_x;
	m_scale.y = t_y;
	m_shape.setScale( sf::Vector2f( t_x, t_y ));
	//TODO
	//TransformVertices();
}

void Polygon::SetScale( glm::vec2 t_scale ) {
	SetScale( t_scale.x, t_scale.y );	
}

glm::vec2 Polygon::GetOrigin() {
	return m_origin;
}

glm::vec2 Polygon::GetPosition() {
	return m_position;
}

float Polygon::GetRotation() {
	return m_rotation;
}

glm::vec2 Polygon::GetScale() {
	return m_scale;
}
//
void Polygon::FlipHorizontal() {
	m_scale.x = -m_scale.x;
	m_shape.setScale( sf::Vector2f( m_scale.x, m_scale.y ));
}
//
void Polygon::FlipVertical() {
	m_scale.y = -m_scale.y;
	m_shape.setScale( sf::Vector2f( m_scale.x, m_scale.y ));
}
//
void Polygon::FlipDiagonal() {
	m_scale.x = -m_scale.x;
	m_scale.y = -m_scale.y;
	m_shape.setScale( sf::Vector2f( m_scale.x, m_scale.y ));
}

void Polygon::Animate( sf::Time& t_dt ) {
}
