#define CATCH_CONFIG_MAIN

#include<catch2/catch_test_macros.hpp>
#include<iostream>
#include<Tool.h>

TEST_CASE("Converting vectors","[classic]") {

	SECTION( "Conversion multiplayers values" ) {
		REQUIRE( 0.01f == n2d::PIXEL_TO_BOX2D );
		REQUIRE( 100.0f == n2d::BOX2D_TO_PIXEL );
	};

	SECTION(" glm -> box2d") {	
		glm::vec2 tmp;
		b2Vec2 res;
		float i1,j1;
		for( float i=511.53f,j=-345.34f;i>-100.f,j<100.0f;i-=23.11f,j+=17.51f ) {
			i1 = i * 0.01f;
			j1 = j * 0.01f;
			tmp.x = i;
			tmp.y = j;
			
			// conversion here
			res = n2d::Tool::g2b( tmp );
			
			REQUIRE( res.x == i1 );
			REQUIRE( res.y == j1 );
		}
	}

	SECTION(" sfml -> box2d") {	
		sf::Vector2f tmp;
		b2Vec2 res;
		float i1,j1;
		for( float i=511.53f,j=-345.34f;i>-100.f,j<100.0f;i-=23.11f,j+=17.51f ) {
			i1 = i * 0.01f;
			j1 = j * 0.01f;
			tmp.x = i;
			tmp.y = j;
			
			// conversion here
			res = n2d::Tool::s2b( tmp );
			
			REQUIRE( res.x == i1 );
			REQUIRE( res.y == j1 );
		}
	}

	SECTION(" box2d -> glm") {	
		glm::vec2 res;
		b2Vec2 tmp;
		float i1,j1;
		for( float i=511.53f,j=-345.34f;i>-100.f,j<100.0f;i-=23.11f,j+=17.51f ) {
			i1 = i * 100.0f;
			j1 = j * 100.0f;
			tmp.x = i;
			tmp.y = j;
			
			// conversion here
			res = n2d::Tool::b2g( tmp );
			
			REQUIRE( res.x == i1 );
			REQUIRE( res.y == j1 );
		}
	}
}


