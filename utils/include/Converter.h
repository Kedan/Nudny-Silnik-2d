#ifndef NUNDY_SILNIK_2D_UTILS_CONVERTER_H
#define NUNDY_SILNIK_2D_UTILS_CONVERTER_H

#include <glm/glm.hpp>
#include <tileson/tileson.h>

namespace nudny {
	class ConverterTsonToGlm {
		public:
			static glm::vec4 Rect( const tson::Rect& t_rect ) {
				return glm::vec4( t_rect.x, t_rect.y, t_rect.width, t_rect.height );
			}
			static glm::vec2 Vec2( const tson::Vector2i& t_v ) {
				return glm::vec2( t_v.x, t_v.y );
			}
	}; // class ConverterTsonToGlm
	class Converter {
		protected:
			static ConverterTsonToGlm	m_tson_to_glm;
		public:
			static ConverterTsonToGlm& Huj() {
				return m_tson_to_glm;
			}
			static ConverterTsonToGlm& TSON_TO_GLM() {
				return m_tson_to_glm;
			};
	}; // class Converter
}; // namespace nudny

#endif
