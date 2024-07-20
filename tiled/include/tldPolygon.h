#ifndef NUDNY_SILNIK_2D_TILED_POLYGON_H
#define NUDNY_SILNIK_2D_TILED_POLYGON_H

#include <tileson/tileson.h>
#include <Polygon.h>

namespace nudny {
	class tldPolygon : public Polygon {
		public:
			tldPolygon( tson::Object& );
			bool Load( tson::Object& );
			std::vector<glm::vec2>	LoadGeometry( tson::Object&, glm::vec2, glm::vec2 );	
		protected:
			tson::Object m_tiled_obj;
	}; //class 
}; // namespace

#endif
