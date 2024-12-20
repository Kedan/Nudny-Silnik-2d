#ifndef NUNDY_SILNIK_GRAPH_SHAPE_HPP
#define NUNDY_SILNIK_GRAPH_SHAPE_HPP

#include <SFML/Graphics.hpp>
#include <core/Interfaces.hpp>
#include <box2d/box2d.h>

namespace ns {
	class Shape : 
		public itf::Drawable, 
		public itf::Updatable,
   		public itf::Simulated	{
		public:
			Shape() { def = b2DefaultShapeDef(); }
			virtual void reset() = 0;
			virtual void create(b2BodyId&) = 0;
			virtual void center() = 0;
		public:
			b2ShapeId		id;
			float			rotation	{0.f};
			sf::Vector2f	origin		{ 0.f, 0.f };
			sf::Vector2f 	position	{0.f, 0.f};
			sf::Color		color		{255,255,255,255};
			b2ShapeDef		def;
			sf::Vector2f	size		{0.0f, 0.0f};
			float			radius		{0.0f};
	};
};

#endif
