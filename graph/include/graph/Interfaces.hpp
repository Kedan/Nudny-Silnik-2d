#ifndef NUDNY_SILNIK_2D_GRAPH_INTERFACES_HPP
#define NUDNY_SILNIK_2D_GRAPH_INTERFACES_HPP

#include <core/Interfaces.hpp>

namespace ns::itf {
	class Colored {
		public:
			virtual void setColor(const sf::Color&)=0;
			virtual void setColor(const glm::vec4&)=0;
			virtual void setColor(const tson::Color&)=0;
			virtual void setColor(const float&, const float&, const float&, const float&)=0;

			virtual const sf::Color&	getColor()=0;
			virtual const glm::vec4&	getColorg()=0;
	};
	class Textures {
		public:
			virtual void setTexture(const sf::Texture*, bool)=0;
			virtual void setTextureRect(const sf::IntRect&)=0;
			virtual void setTextureRect(const glm::vec4&)=0;
			virtual const sf::Texture*	getTexture()=0;
			virtual const sf::IntRect&	getTextureRect()=0;
	};
	class Animated {
		public:
			virtual void animate(const sf::Time&) = 0;
	};
};

#endif
