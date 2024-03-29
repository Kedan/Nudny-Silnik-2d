#include "Body.h"

using namespace n2d;

Body::Body( float x, float y, float rotation ) {
	is_ground = false;
	def.type = b2_dynamicBody;
	def.position.Set( Tool::Bf(x), Tool::Bf(y) );
	def.angle = Tool::rad( rotation );
}
Body::Body( glm::vec2 position, float rotation ) {
	is_ground = false;
	def.type = b2_dynamicBody;
	def.position.Set( Tool::Bf(position.x), Tool::Bf(position.y) );
	def.angle = Tool::rad( rotation );
}

void Body::Add( Shape* shape ) {
	m_shapes.push_back( shape );
	m_shapes.back()->FixToBody();
}

void Body::Create( b2World& world ) {
	if( m_shapes.size() > 0 ) {
		m_body = world.CreateBody( &def );
		if( m_body != nullptr ) {
			if( is_ground ) {
				for( auto s : m_shapes ) {
					if( s->collide ) {
						m_body->CreateFixture( s->fixture.shape, 0.0f );
					}
				}
			} else {
				for( auto s : m_shapes ) {
					if( s->collide ) {
						m_body->CreateFixture( &s->fixture );
					}
				}
			}
		} else {
			std::cerr << "n2d::Body::Create() - Could not create body! b2Body ptr: "<< m_body <<"\n";
		}
	} else {
		std::cerr << "n2d::Body::Create() - Could not create body! m_shapes.size: " << m_shapes.size() <<"\n";
	}
};

void Body::Draw( sf::RenderWindow& window ) {
	for( auto s : m_shapes ) {
		s->Draw( window );
	}
}

void Body::Draw( sf::RenderWindow& window, sf::Transform& t ) {
	for( auto s : m_shapes ) {
		s->Draw( window, t );
	}
}

void Body::Update( float dt ) {
	float rotation 		= Tool::ang( m_body->GetAngle() );
	glm::vec2 position 	= Tool::b2g( m_body->GetPosition() );
	for( auto s : m_shapes ) {
		s->AddBodyCoords( position.x, position.y, rotation );
		s->Animate( dt );
	}
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

void Body::SetPosition( glm::vec2 position ) {
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

void Body::Enable( bool enable) {
	m_body->SetEnabled( enable );
}

void Body::Disable() {
	Enable(false);
}

bool Body::IsEnable() {
	return m_body->IsEnabled();
}
