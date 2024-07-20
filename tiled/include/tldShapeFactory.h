#ifndef NUDNY_SILNIK_2D_TILED_SHAPE_FACTORY_H
#define NUDNY_SILNIK_2D_TILED_SHAPE_FACTORY_H

#include <tileson/tileson.h>
#include <Shape.h>
#include <tldCircle.h>
#include <tldRectangle.h>
#include <tldPolygon.h>

namespace nudny {
	class tldShapeFactory {
		public:
			static std::unique_ptr<Shape> Create( tson::Object t_object ) {
				int type = (int)t_object.getObjectType();
				std::unique_ptr<Shape> result;
				switch( type ) {
					case 1: //Object
						break;
					case 2: // Elipse/Circle
						result.reset( new tldCircle( t_object ));
						break;
					case 3:
						result.reset( new tldRectangle( t_object ));
						break;
					case 4: //Point
						break;
					case 5:
						result.reset( new tldPolygon( t_object ));
						break;
					case 6: //Polyline
						break;
					case 7: // Text
						break;
					case 8: // Template
						break;
				};
				return std::move( result );
			}
	};
}; // namespace 

#endif
