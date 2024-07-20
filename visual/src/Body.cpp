#include "Body.h"

using namespace nudny;

Body::Body( float t_x, float t_y, float t_rotation ) {
	is_ground 	= false;
	position.x	= t_x;
	position.y	= t_y;
	rotation	= t_rotation;
	def.type 	= b2_dynamicBody;
	def.position.Set( Tool::Bf(t_x), Tool::Bf(t_y) );
	def.angle 	= Tool::rad( t_rotation );
}
Body::Body( glm::vec2 t_position, float t_rotation ) {
	is_ground 	= false;
	position 	= t_position;
	rotation 	= t_rotation;
	def.type 	= b2_dynamicBody;
	def.position.Set( Tool::Bf(position.x), Tool::Bf(position.y) );
	def.angle 	= Tool::rad( rotation );
}

int Body::Add( Shape* t_shape, std::string t_alias ) {
	std::cout << "Add raw pointer\n";
	m_shapes.push_back( std::shared_ptr<Shape>( t_shape ));
	m_shapes.back()->FixToBody();
	int id = m_shapes.size() - 1;
	if( !t_alias.empty() ) {
		m_shape_sets.insert({t_alias,id});
	}
	return id;
}

int Body::Add( std::shared_ptr<Shape> t_shape, std::string t_alias ) {
	std::cout << "Add smart pointer\n";
	m_shapes.push_back( t_shape );
	m_shapes.back()->FixToBody();
	int id = m_shapes.size() - 1;
	if( !t_alias.empty() ) {
		m_shape_sets.insert({t_alias,id});
	}
	return id;
}

//bool Body::Remove( std::unique_ptr<Shape> t_shape ) {
//	bool result = false;
//	int i = 0;
//	for( auto shape : m_shapes ) {
//		if( shape == t_shape ) {
//			m_body->DestroyFixture( m_fixtures[i]);
//			m_shapes.erase( m_shapes.begin() + i );
//			for( auto [alias,id] : m_shape_sets ) {
//				if( id == i ) {
//					m_shape_sets.erase( alias );
//				}
//			}
//		}
//		i++;
//	}
//	for
//	return false;
//}

bool Body::Remove( int t_shape_idx ) {
	if( m_shapes.size() < t_shape_idx ) {
		m_body->DestroyFixture( m_fixtures[ t_shape_idx ]);
		m_shapes.erase( m_shapes.begin() + t_shape_idx );
		for( auto [alias,id] : m_shape_sets ) {
			if( id == t_shape_idx ) {
				m_shape_sets.erase( alias );
			}
		}
		return true;
	}
	return false;
}

bool Body::Remove( std::string t_alias ) {
	for( auto [alias,id] : m_shape_sets ) {
		if( alias == t_alias ) {
			return Remove( id );
		}	
	}
	return false;
}

void Body::Fixture() {
	try{
		int i = 0;
		if( is_ground ) {
			for( const auto& s : m_shapes ) {
				if( s->collide ) {
					m_fixtures[ i ] = m_body->CreateFixture( s->fixture.shape, 0.0f );
					i++;
				}
			}
		} else {
			for( const auto& s : m_shapes ) {
				if( s->collide ) {
					m_fixtures[ i ] = m_body->CreateFixture( &s->fixture );
					i++;
				}
			}
		}
	} catch( std::exception e ) {
		LOG.Time() << "ERROR: Body Fixrure() " << e.what() << "\n";
	}
}

void Body::Enable( bool enable) {
	m_body->SetEnabled( enable );
}

void Body::Disable() {
	Enable(false);
}

bool Body::IsEnable() {
	return m_body->IsEnabled();
}

b2Body* const Body::GetPtr() const {
	return m_body;
}

void Body::Draw( sf::RenderWindow& window ) {
	for( const auto& s : m_shapes ) {
		s->Draw( window );
	}
}

void Body::Draw( sf::RenderWindow& window, sf::Transform& t ) {
	for( const auto& s : m_shapes ) {
		s->Draw( window, t );
	}
}

void Body::Update( sf::Time& t_dt ) {
	rotation 	= Tool::ang( m_body->GetAngle() );
	position 	= Tool::b2g( m_body->GetPosition() );
	for( const auto& s : m_shapes ) {
		s->AddBodyCoords( position.x, position.y, rotation );
	}
	std::cout << "Body::Update = " << position.x << ", " << position.y << "\n";
}

void Body::Create( b2World& t_world ) {
	if( m_shapes.size() > 0 ) {
		m_body = t_world.CreateBody( &def );
		Fixture();	
	} else {
		LOG.Time() << "Body Create() - Could not create body! m_shapes.size: " << m_shapes.size() <<"\n";
	}
}

void Body::Animate( sf::Time& t_dt ) {
	for( const auto& shape : m_shapes ) {
		shape->Animate( t_dt );
	}
}

void Body::SetOrigin( float t_x, float t_y ) {
	// TODO
}

void Body::SetOrigin( glm::vec2 t_origin ) {
	SetOrigin( t_origin.x, t_origin.y );
}

void Body::SetPosition( float x, float y ) {
	position.x = x;
	position.y = y;
	if( !m_body ) {
		def.position.Set( Tool::Bf(position.x), Tool::Bf(position.y));
	} else {
		m_body->SetTransform( Tool::g2b(position), Tool::rad(rotation));
	}
}

void Body::SetPosition( glm::vec2 t_position ) {
	position = t_position;
	SetPosition( position.x, position.y );
}

void Body::SetRotation( float r ) {
	rotation = r;
	if( !m_body ) {
		def.angle = Tool::rad( rotation );
	} else {
		m_body->SetTransform( Tool::g2b(position), Tool::rad(rotation));
	}
}

void Body::SetScale( float t_x, float t_y ) {
	// TODO
}

void Body::SetScale( glm::vec2 t_scale ) {
	SetScale( t_scale.x, t_scale.y );
}

glm::vec2 Body::GetOrigin() {
	return glm::vec2(0,0);
}

glm::vec2 Body::GetPosition() {
	position = Tool::b2g( m_body->GetPosition() );
	return position;
}

float Body::GetRotation() {
	rotation = Tool::ang( m_body->GetAngle() );
	return rotation;
}

glm::vec2 Body::GetScale() {
	return glm::vec2(1,1);
}

void Body::SetDirection( glm::vec2 t_direction ) {
	b2Vec2 d = Tool::g2b( t_direction );
	d.Normalize();
	d*=m_body->GetLinearVelocity().Length();
	m_body->SetLinearVelocity( d );
}

void Body::SetSpeed( float t_speed ) {
	b2Vec2 v = m_body->GetLinearVelocity();
	v.Normalize();
	v *= Tool::Bf( t_speed );
	m_body->SetLinearVelocity( v );
}

void Body::SetVelocity( glm::vec2 t_v ) {
	m_body->SetLinearVelocity( Tool::g2b( t_v ));
}

void Body::SetAngularVelocity( float t_omega ) {
	m_body->SetAngularVelocity( Tool::rad( t_omega ));
}

void Body::SetImpulse( glm::vec2 t_i ) {
	m_body->ApplyLinearImpulseToCenter( Tool::g2b( t_i ), true );
}

void Body::SetMass( float t_m ) {
	m_body->GetMassData( &m_mass_data );
	m_mass_data.mass = t_m;
	m_body->SetMassData( &m_mass_data );
}

void Body::Awake( bool t_awake ) {
	m_body->SetAwake( t_awake );
}

glm::vec2 Body::GetDirection() {
	return glm::normalize( Tool::b2g( m_body->GetLinearVelocity() ));
}

float Body::GetSpeed() {
	return Tool::b2g( m_body->GetLinearVelocity()).length();
}

glm::vec2 Body::GetVelocity() {
	return Tool::b2g( m_body->GetLinearVelocity() );
}

float Body::GetAngularVelocity() {
	return Tool::ang( m_body->GetAngularVelocity() );
}

float Body::GetMass() {
	return m_body->GetMass();
}

void Body::FlipHorizontal() {
	int i = 0;
	for( const auto& shape : m_shapes ) {
		m_body->DestroyFixture( m_fixtures[i] );
		shape->FlipHorizontal();
		++i;
	}
	Fixture();
}

void Body::FlipVertical() {
	int i = 0;
	for( const auto& shape : m_shapes ) {
		m_body->DestroyFixture( m_fixtures[i] );
		shape->FlipVertical();
		++i;
	}
	Fixture();
}

void Body::FlipDiagonal() {
	int i = 0;
	for( const auto& shape : m_shapes ) {
		m_body->DestroyFixture( m_fixtures[ i ] );
		shape->FlipDiagonal();
		++i;
	}
	Fixture();
}

void Body::SetColor( sf::Color& t_color ) {
	for( const auto& s : m_shapes ) {
		s->SetColor( t_color );
	}	
}

void Body::SetColor( int r, int g, int b, int a ) {
	for( const auto& s : m_shapes ) {
		s->SetColor( r, g, b, a );
	}
}

void Body::SetColor( glm::vec4 t_color ) {
	for( const auto& s : m_shapes ) {
		s->SetColor( t_color );
	}
}

void Body::SetAlpha(int t_alpha ) {
	for( const auto& s : m_shapes ) {
		s->SetAlpha( t_alpha );
	}
}

void Body::SetVisible( bool t_visible ) {
	SetAlpha( t_visible ? 255 : 0 );
}

int Body::GetAlpha() {
	return m_shapes.front()->GetAlpha();
}

glm::vec4 Body::GetColor() {
	return m_shapes.front()->GetColor();
}

glm::vec4 Body::GetRGBA() {
	return GetColor();
}

glm::vec3 Body::GetRGB() {
	return m_shapes.front()->GetRGB();
}

const sf::Color& Body::GetColorsf() {
	return m_shapes.front()->GetColorsf();
}
