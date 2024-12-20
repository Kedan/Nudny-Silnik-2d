#ifndef NUDNY_SILNIK_2D_GRAPH_SHAPE_STATE_HPP
#define NUDNY_SILNIK_2D_GRAPH_SHAPE_STATE_HPP

#include <bitset>
#include <glm/glm.hpp>

namespace ns {
	enum SHAPE_STATE {
		constexpr DRAWABLE 		= 0b00000001,
		constexpr UPDATABLE		= 0b00000010,
		constexpr SIMULATED		= 0b00000100,
		constexpr INTERACTIVE	= 0b00001000,
	};

	class ShapeState {
		public:
			glm::vec2		position;
			float			rotation;
			glm::vec2		size;
			float			radius;
			glm::vec4		color;
			std::bitset<4>	state;
	};

	class BodyState : public ShapeState {
		public:
			glm::vec2	v;
			float		w;
			float 		mass;
			float 		density;
			float 		friction;
			float 		restitution;
	}
};

#endif
