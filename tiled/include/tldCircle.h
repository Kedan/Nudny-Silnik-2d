#ifndef NUNDY_SILNIK_2D_TILED_CIRCLE_H
#define NUNDY_SILNIK_2D_TILED_CIRCLE_H

#include <tileson/tileson.h>
#include <Circle.h>

namespace nudny {
	class tldCircle : public Circle {
		public:
			tldCircle( tson::Object& );
			bool Load( tson::Object& );
		protected:
			tson::Object m_tiled_obj;
	}; // class
}; // namespace

#endif
