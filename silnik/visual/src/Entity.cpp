#include "Entity.h"

using namespace n2d;

Entity::Entity() {}

int Entity::Add( Body* body ) {
	bodies.push_back( body );
	return bodies.size() - 1;
}

void Entity::Draw( sf::RenderWindow& w ) {
	for( auto b : bodies ) {
		b->Draw( w );
	}
	if( show_text ) {
		text.Draw( w );
	}
}

void Entity::Draw( sf::RenderWindow& w, sf::Transform& t ) {
	for( auto b : bodies ) {
		b->Draw( w, t );
	}
	if( show_text ) {
		text.Draw( w, t );
	}
}

void Entity::Update( float dt ) {
	for( auto b : bodies ) {	
		b->Update( dt );
	}
	if( show_text ) {
		text.Update( dt );
	}
}

void Entity::Events( sf::Event& t_event ) {
}

void Entity::Create( b2World& world ) {
	for( auto b : bodies ) {
		//b->SetPosition( position + b->position );
		//b->SetRotation( rotation + b->rotation );
		b->Create( world );
	}
}

void Entity::LoadText( tson::Object& t_object ) {
	text.Load( t_object.getText() );
}

void Entity::LoadTemplate( tson::Object& t_object ) {
}

//void Entity::FlipVertically() {
//}
//
//void Entity::FlipHorizontally() {
//}
//
//void Entity::SetPosition( float t_x, float t_y ) {
//}
//
//void Entity::SetPosition( glm::vec2 t_position ) {
//}
//
//void Entity::SetRotation( float angle ) {
//}
//
void Entity::SetVelocity( float t_x, float t_y ) {
	for( auto body : bodies ) {
		body->GetBodyPtr()->SetLinearVelocity( b2Vec2( t_x, t_y ) );	
	}	
}

void Entity::SetRotation( float t_angle ) {
}

void Entity::SetType( b2BodyType t_type ) {
	for( auto body : bodies ) {
		body->GetBodyPtr()->SetType( t_type );
	}
}
