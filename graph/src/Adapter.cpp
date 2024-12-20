#include <graph/Adapter.hpp>

namespace ns {

	sf::CircleShape sfCircle(const b2BodyId& t_body, const b2Circle& t_shape) {
		sf::CircleShape c;
		float r = sf(t_shape.radius );
		c.setRadius(r);
		c.setOrigin(r,r);
		sync(c,t_body);
		return c;
	}
	
	sf::CircleShape	sfCircle(tson::Object& t_c) 	{
		if( t_c.getObjectType() != tson::ObjectType::Ellipse ) {
			throw std::invalid_argument("sf::CircleShape require tson::ObjectType::Ellipse.");
		}
		sf::CircleShape c;
		c.setPosition(sf(t_c.getPosition()) );
		c.setRadius(t_c.getSize().x );
		c.setRotation(t_c.getRotation());
		c.setFillColor(sf(t_c.get<tson::Colori>("color")));
		// set texture
		return c;
	}

	sf::RectangleShape sfRectangle(const b2BodyId& t_body, const b2Polygon& t_shape ) {
		sf::RectangleShape r;
		if( t_shape.count == 4 ) {
		}
		sf::Vector2f s = sfBoxSize(t_shape); 
		r.setOrigin(s.x/2,s.y/2);
		r.setSize(s);
		sync( r, t_body );
		return r;
	}

	sf::RectangleShape sfRectangle(tson::Object& t_r) {
		if( t_r.getObjectType() != tson::ObjectType::Rectangle ) {
			throw std::invalid_argument("sf::RectangleShape require tson::ObjectType::Rectangle.");
		}
		sf::RectangleShape r;
		r.setSize(sf(t_r.getSize()));
		r.setOrigin(r.getSize()/2.0f);
		r.setPosition(sf(t_r.getPosition()));
		r.setRotation(t_r.getRotation());
		r.setFillColor(sf(t_r.get<tson::Colori>("color")));
		// set texture
		return r;
	}
	
	sf::ConvexShape sfConvex(tson::Object& t) {
		if( t.getObjectType() != tson::ObjectType::Rectangle ) {
			throw std::invalid_argument("sf::ConvexShape require tson::ObjectType::Polygon.");
		}
		sf::ConvexShape c;
		c.setPosition(sf(t.getPosition()));
		c.setRotation(t.getRotation());
		c.setFillColor(sf(t.get<tson::Colori>("color")));
		c.setPointCount(static_cast<std::size_t>(t.getPolygons().size()));
		for(std::size_t i=0;i<t.getPolygons().size();++i) {
			c.setPoint(i,sf(t.getPolygons()[i]));
		}
		return c;
		// set texture
	}
	
	sf::Sprite sf(const tson::Tile& t) {
		sf::Sprite s;
		return s;
	}
	
	sf::Vector2f sfBoxSize( const b2Polygon& t_box ) {
		if( t_box.count != 4 ) {
			throw std::invalid_argument("Provided polygon is not a box!");			
		}
		const b2Vec2& v0 = t_box.vertices[0];
		const b2Vec2& v1 = t_box.vertices[1];
		const b2Vec2& v2 = t_box.vertices[2];

		float width = b2Distance(v0, v1);
		float height = b2Distance(v1,v2);

		return sf(b2Vec2(width,height));
	}

//	b2Vec2 getBoxSize(const b2Polygon& t_box ) {
//		if( t_box.count != 4 ) {
//			throw std::invalid_argument("Provided polygon is not a box!");			
//		}
//		const b2Vec2& v0 = t_box.vertices[0];
//		const b2Vec2& v1 = t_box.vertices[1];
//		const b2Vec2& v2 = t_box.vertices[2];
//

//		float width = b2Distance(v0, v1);
//		float height = b2Distance(v1,v2);
//
//		return b2Vec2(width,height);
//	}

	b2Circle b2(const sf::CircleShape& t_c)	{ 
		b2Circle c;
		c.center = b2( t_c.getOrigin().x-t_c.getRadius(), t_c.getOrigin().y-t_c.getRadius() );
		c.radius = b2( t_c.getRadius() );
		return c;
	}
	
	b2Polygon b2(const sf::RectangleShape& t_r) {
		return  b2MakeOffsetBox( b2(t_r.getSize().x/2), b2(t_r.getSize().y/2), b2(t_r.getOrigin()), glm::radians(t_r.getRotation()));
	}

	b2Polygon b2(const sf::ConvexShape& t_c) {
		if(t_c.getPointCount()>b2_maxPolygonVertices || t_c.getPointCount()<3 ) {
			throw std::out_of_range("b2Polygon must have minumum 2 and maximum "+std::to_string(b2_maxPolygonVertices)+" vertices. "+std::to_string(t_c.getPointCount())+" given.");
		}
		b2Vec2*	v 	= new b2Vec2[t_c.getPointCount()];
		for(std::size_t i=0;i<t_c.getPointCount();++i) {
			v[i] = b2(t_c.getPoint(i));
		}
		b2Hull	h	= b2ComputeHull(v,t_c.getPointCount());
		b2Transform t;
		t.p = b2(t_c.getPosition());
		t.q = b2MakeRot(t_c.getRotation());
		b2Polygon p = b2MakeOffsetPolygon(&h,1.0f,t);
		return p;
	}

	void sync(sf::CircleShape& t_target,		tson::Object& t_src ) 	{ t_target = sfCircle(t_src);	}
	void sync(sf::RectangleShape& t_target, 	tson::Object& t_src ) 	{ t_target = sfRectangle(t_src); }
	void sync(sf::ConvexShape& t_target, 		tson::Object& t_src )	{ t_target = sfConvex(t_src); }
	
	std::unique_ptr<sf::Shape> createSfmlShape(tson::Object& t_src) {
		switch( t_src.getObjectType() ) {
			case tson::ObjectType::Ellipse:
				return std::make_unique<sf::CircleShape>(sfCircle(t_src));
			case tson::ObjectType::Rectangle:
				return std::make_unique<sf::RectangleShape>(sfRectangle(t_src));
			case tson::ObjectType::Polygon:
				return std::make_unique<sf::ConvexShape>(sfConvex(t_src));
		}
		return nullptr;
	}
};

