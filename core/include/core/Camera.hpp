#ifndef NUDNY_SLINIK_2D_CORE_CAMERA_HPP
#define NUDNY_SLINIK_2D_CORE_CAMERA_HPP

#include <glm/glm.hpp>
#include <SFML/Graphics/View.hpp>
#include <core/Interfaces.hpp>

namespace ns {
	namespace itf {
		class Camera :
		public itf::Drawable,
		public itf::Interactive, 
		public itf::Simulated {
			public:
				virtual void lookAt(const float&, const float&) = 0;
			};
	}; // namespace itf
	class Camera : public itf::Camera {  
			Camera();
			void draw(sf::RenderWindow&); 
			void handleEvents(const sf::Event& );
			void update(const sf::Time& );
			void lookAt(const float&, const float& );
		protected:
			sf::View	m_view;
			glm::vec2 	m_position{400,300};
			glm::vec2	m_size{800,600};
	};
}; // namespace ns

#endif
