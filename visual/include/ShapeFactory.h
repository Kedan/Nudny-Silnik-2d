#ifndef NUDNY_SILNIK_2D_VISUAL_SHAPE_FACTORY_H
#define NUDNY_SILNIK_2D_VISUAL_SHAPE_FACTORY_H

#include <memory>
#include <Shape.h">
#include <Circle.h">
#include <Rectangle.h>
#include <Polygon.h>

namespace nudny {
	class ShapeFactory() {
		public:
			static std::shared_ptr<Shape> Create( int t_type ) {
				switch( t_type ) {
					case 1:
						break;
					case 2:
						return std::make_shared<Shape>( new Circle() );
					case 3:
						return std::make_shared<Shape>( new Rectangle() );
					case 4:
						break;
					case 5:
						return std::make_shared<Shape>( new Polygon() );
					default:
						return nullptr;
				};
				return nullptr;
			};	
	}; // class ShapeFactory
}; // namespace nudny;

#endif
