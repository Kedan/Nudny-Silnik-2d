#include "Log.h"
#include "Tool.h"
#include "Model.h"

usingn namespace n2d;

Model::Model() {
}

Model::~Model() {
}

void Model::Register( App& t_app ) {
	for( auto b : m_bodies ) {
		t_app.AddUpdatable( &b );
		t_app.AddDrawable( &b );
	}
}

// Drawable 

void Model::Draw( sf::RenderWindow& t_window ) {
	for( auto b : m_bodies ) {
		b.Draw( t_window );
	}
}

void Model::Draw( sf::RenderWindow& t_window, sf::Transform& t_transform ) {
	for( auto b : m_bodies ) {
		b.Draw( t_window, t_transform );
	}
}

// Updatable

void Model::Update( float t_dt ) {
	for( auto b : m_bodies ) {
		b.Update( t_dt );
	}
}

// Creatable
void Model::Create( b2World& t_world ) {
	for( auto b : m_bodies ) {
		b.Create( t_world );
	}
}
  
