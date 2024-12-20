#ifndef NUDNY_SILNIK_GRAPH_ADAPTER_HPP
#define NUDNY_SILNIK_GRAPH_ADAPTER_HPP

#include <memory>
#include <glm/glm.hpp>
#include <SFML/Graphics.hpp>
#include <tileson/tileson.hpp>
#include <box2d/box2d.h>
#include <nlohmann/json.hpp>
//#include <graph/Vec2.hpp>

namespace ns {
	namespace constans {
		constexpr float BOX2D_SCALE 	= 0.01f;
		constexpr float BOX2D_SCALE_INV = 100.0f;
	}
	inline float		glm(float f)					{ return constans::BOX2D_SCALE_INV*f; }
	inline glm::vec2 	glm(const sf::Vector2f v) 		{ return glm::vec2(v.x, v.y); }
	inline glm::vec2	glm(const tson::Vector2i& v )	{ return glm::vec2( static_cast<float>(v.x), static_cast<float>(v.y)); }
	inline glm::vec2 	glm(const b2Vec2& v)			{ return glm::vec2( glm(v.x), glm(v.y)); }
	inline glm::vec4	glm(const sf::Color& c)			{ return glm::vec4( c.r/255, c.g/255, c.b/255, c.a/255); }
	inline glm::vec4	glm(const tson::Colori& c )		{ return glm::vec4( c.r/255, c.g/255, c.b/255, c.a/255); }
	inline glm::vec4	glm(const tson::Colorf& c )		{ return glm::vec4( c.r, c.g, c.b, c.a ); }	

	inline float		sf(float f)						{ return glm(f); }
	inline sf::Vector2f	sf(const glm::vec2& v)			{ return sf::Vector2f(v.x, v.y); }
	inline sf::Vector2f	sf(const tson::Vector2i& v)		{ return sf::Vector2f( static_cast<float>(v.x), static_cast<float>(v.y)); }
	inline sf::Vector2f	sf(const b2Vec2& v)				{ return sf::Vector2f( sf(v.x), sf(v.y)); }
	inline sf::Color	sf(const glm::vec4& c)			{ return sf::Color( static_cast<sf::Uint8>(255*c.x), static_cast<sf::Uint8>(255*c.y), static_cast<sf::Uint8>(255*c.z), static_cast<sf::Uint8>(255*c.a)); }
	inline sf::Color	sf(const tson::Colori& c)		{ return sf::Color( static_cast<sf::Uint8>(c.r),static_cast<sf::Uint8>(c.g),static_cast<sf::Uint8>(c.b),static_cast<sf::Uint8>(c.a)); }
	inline sf::Color	sf(tson::Colorf& c)				{ return sf( c.asInt()); }

	inline void sync(sf::CircleShape& t_target, const b2BodyId& t_body ) {
		t_target.setPosition(sf( b2Body_GetPosition(t_body)));
		t_target.setRotation(glm::degrees(b2Body_GetRotation(t_body).s));
	}
	inline void sync(sf::RectangleShape& t_target, const b2BodyId& t_body) {
		t_target.setPosition(sf(b2Body_GetPosition(t_body)));
		t_target.setRotation(glm::degrees(b2Body_GetRotation(t_body).s));
	}
	inline void sync(sf::ConvexShape& t_target, const b2BodyId& t_body) {
		t_target.setPosition(sf(b2Body_GetPosition(t_body)));
		t_target.setRotation(glm::degrees(b2Body_GetRotation(t_body).s));
	}
	
	sf::CircleShape		sfCircle(tson::Object& t_c);
	sf::CircleShape 	sfCircle(const b2BodyId&, const b2Circle&);	
	sf::RectangleShape 	sfRectangle(tson::Object& t_r);
	sf::RectangleShape	sfRectangle( const b2BodyId&, const b2Polygon& );
	sf::ConvexShape 	sfConvex(tson::Object& t);
	sf::Sprite 			sf(const tson::Tile& t);

	inline float	b2(float f)						{ return constans::BOX2D_SCALE*f; }
	inline b2Vec2	b2v(float x, float y)			{ return b2Vec2( b2(x), b2(y) ); }
	inline b2Vec2	b2( float x, float y)			{ return b2Vec2( b2(x), b2(y) ); }
	inline b2Vec2	b2(const glm::vec2& v)			{ return b2v( v.x, v.y ); }
	inline b2Vec2	b2(const sf::Vector2f& v)		{ return b2v( v.x, v.y ); }
	inline b2Vec2	b2(const tson::Vector2i& v)		{ return b2v( static_cast<float>(v.x), static_cast<float>(v.y) ); }
	inline b2Vec2	b2(const tson::Vector2f& v)		{ return b2v( v.x, v.y ); }

	sf::Vector2f	sfBoxSize(const b2Polygon& t_box );
	b2Circle b2(const sf::CircleShape& t_c); 
	b2Polygon b2(const sf::RectangleShape& t_r);
	b2Polygon b2(const sf::ConvexShape& t_c);

	void sync(sf::CircleShape& t_target,		tson::Object& t_src );
	void sync(sf::RectangleShape& t_target, 	tson::Object& t_src );
	void sync(sf::ConvexShape& t_target, 		tson::Object& t_src );
	
	inline void sync(b2Circle& t_target, const sf::CircleShape& t_src ) {
		t_target.center = b2(t_src.getPosition());
		t_target.radius = b2(t_src.getRadius());
	}

	inline void sync(b2Polygon& t_target, const sf::RectangleShape& t_src) {
		t_target = t_src.getOrigin()!=t_src.getSize()/2.0f ? b2MakeOffsetBox( b2(t_src.getSize().x/2.0f), b2(t_src.getSize().y/2.0f), b2(t_src.getPosition()),t_src.getRotation()) : b2MakeBox(b2(t_src.getSize().x)/2.0f,b2(t_src.getSize().y)/2.0f);
	}

	std::unique_ptr<sf::Shape> createSfmlShape(tson::Object& t_src);
};
#endif
