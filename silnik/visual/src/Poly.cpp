#include "Poly.h"

using namespace n2d;

Poly::Poly( std::vector<glm::vec2> vertices ) {
	Reset();
	SetDensity();
	SetFriction();
	SetVertices( vertices ); // before position & rotation
	SetPosition();
	SetRotation();
	SetColor();
	fixture.shape 		= &bound;
}

Poly::Poly( const Poly& poly ) {
	Reset();
	SetDensity( poly.fixture.density );
	SetFriction( poly.fixture.friction );
	SetVertices( poly.m_vertices ); // ! before postion & rotation
	SetPosition( poly.position.x, poly.position.y );
	SetRotation( poly.rotation );
	SetColor( poly.color );
	fixture.shape 		= &bound;
}

Shape* Poly::Clone() const {
	return new Poly( *this );
}

b2Shape* Poly::GetUpdatable() {
	return (b2Shape*)&bound;
}

sf::Drawable* Poly::GetDrawable()  {
	return (sf::Drawable*)&shape;
}

sf::Transformable* Poly::GetTransformable() {
	return (sf::Transformable*)&shape;
}

void Poly::Draw( sf::RenderWindow& w ) {
	w.draw( shape, m_transform );
}

void Poly::Draw( sf::RenderWindow& w, sf::Transform& t ) {
	w.draw( shape, t );
}
void Poly::AddBodyCoords( float x, float y, float r ) { 
	m_transform = sf::Transform::Identity;
	m_transform.translate( x, y );
	m_transform.rotate( r );

//	All shape.vertices are transformed every SetPosition/SetRotation
//	You don't have to transform it while drawing	
//	m_transform.translate( position.x, position.y );
//	m_transform.rotate( rotation );
}

void Poly::FixToBody() {
	shape.setPosition( 0 ,0 );
	shape.setRotation( 0 );
}

void Poly::SetRotation( float r ) {
	rotation = r;
	shape.setRotation( rotation );
	TransformVertices();
}

void Poly::SetPosition( float x, float y ) {
	position.x = x;
	position.y = y;
	shape.setPosition( position.x, position.y );
	TransformVertices();
}

void Poly::SetPosition( glm::vec2 pos ) {
	SetPosition( pos.x, pos.y );
}

void Poly::SetOrigin( float x, float y ) {
	origin.x = x;
	origin.y = y;
	shape.setOrigin( origin.x, origin.y );
}

void Poly::SetOrigin( glm::vec2 origin ) {
	if( Shape::origin != origin )
		SetOrigin( origin.x, origin.y );
}

void Poly::SetColor( glm::vec4 color ) {
	Poly::color = color;
	shape.setFillColor( sf::Color( color[0], color[1], color[2], color[3] ));
}

void Poly::SetColor( int r, int g, int b, int a ) {
	SetColor( glm::vec4(r,g,b,a ));
}

void Poly::SetColor( sf::Color color ) {
	Poly::color[0] = color.r;
	Poly::color[1] = color.b;
	Poly::color[2] = color.b;
	Poly::color[3] = color.a;
	shape.setFillColor( color );
}	

void Poly::SetTexture( int id ) {
	texture_id = id;
	shape.setTexture( mp_resources->textures.GetPtr( texture_id ));
}

void Poly::SetTexture( sf::Texture& t_texture ) {
	shape.setTexture( &t_texture );
}

void Poly::SetTexture( std::string texture_path ) {
	if( !mp_resources->textures.IsLoaded( texture_path ) ) {
		texture_id = mp_resources->textures.Load( texture_path );
	}
	if( texture_id >= 0 ) {
		SetTexture( texture_id );
	}
	SetTextureCoords();
}

void Poly::SetTextureCoords( glm::vec4 coords ) {
	if( texture_id > -1 && coords[0]==0 && coords[1]==0 && coords[2] == 0 && coords[3]==0 ) {
		coords[2] = mp_resources->textures.GetRef( texture_id ).getSize().x;
		coords[3] = mp_resources->textures.GetRef( texture_id ).getSize().y;
	}
	tex_coords = coords;
	shape.setTextureRect( sf::IntRect( tex_coords[0], tex_coords[1], tex_coords[2], tex_coords[3] ));
}

void Poly::SetTextureCoords( float u0, float v0, float u1, float v1 ) {
	SetTextureCoords( glm::vec4( u0, v0, u1, v1 ));
}

void Poly::SetVertices( std::vector<glm::vec2> t_vertices ) {
	if( collide && t_vertices.size() > 2 ) {
		m_vertices = t_vertices;
		TransformVertices();
	} 
};

void Poly::TransformVertices() {
	if( m_vertices.size()>2 ) {
		Reset();
		shape.setPointCount(m_vertices.size());
		if( !(position.x==0 && position.y==0 && rotation==0 )) {
			vertices		= Tool::Transform( m_vertices, position, rotation );
			int i=0;
			for( auto& vertex : vertices ) {
				shape.setPoint( i, sf::Vector2f( vertex.x, vertex.y ));
				b2_vertices.push_back( b2Vec2( Tool::Bf( vertex.x), Tool::Bf(vertex.y )));
				i++;
			}
		} else {
			vertices = m_vertices;
			int i = 0;
			for( auto& vertex : vertices ) {
				shape.setPoint( i, sf::Vector2f( vertex.x, vertex.y ));
				b2_vertices.push_back( b2Vec2( Tool::Bf( vertex.x), Tool::Bf(vertex.y )));
				i++;
			}
		}
		bound.Set(b2_vertices.data(),b2_vertices.size());
	} else {
		//std::cout << "Poly::TransformVertices - geometry has "<<m_vertices.size()<<" vertices! Must have minimum 3! Cant create shape!\n";
	}
}

void Poly::Reset() {
	vertices.clear();
	b2_vertices.clear();		
}

void Poly::Animate( float t_dt ) {
}

void Poly::ClearAnimation( ) {
}

void Poly::Play() {
}

void Poly::Pause() {
}

void Poly::Stop() {
}
