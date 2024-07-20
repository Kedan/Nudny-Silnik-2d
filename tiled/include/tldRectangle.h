#ifndef NUDNY_SILNIK_2D_TILED_RECTANGLE_H
#define NUDNY_SILNIK_2D_TILED_RECTANGLE_H

#include <tileson/tileson.h>
#include <Rectangle.h>

namespace nudny {
	class tldRectangle : public Rectangle {
		public:
			tldRectangle( tson::Object& );
			bool Load( tson::Object& );
		protected:
			tson::Object m_tiled_obj;
	}; // class
}; // namespace

#endif
