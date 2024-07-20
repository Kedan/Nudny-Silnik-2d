#ifndef NUDNY_SILNIK_2D_TILED_TLCIRCLE_H
#define NUDNY_SILNIK_2D_TILED_TLCIRCLE_H

#include <tileson/tileson.h>

namespace nudny {
	class tldObject {
		public:
			virtual bool Load( tson::Object& ) = 0;
		protected:
			inline void SetObj( tson::Object& t_obj ) : m_tiled_obj( t_obj ) {}
			tson::Object	m_tiled_obj;
	}; // class
}; // namespace

#endif
