#ifndef NUDNY_SILNIK_2D_MODEL_H
#define NUDNY_SILNIK_2D_MODEL_H

#include "Interfaces.h"
#include "Body.h"

namespace n2d {
	class Model :
	public Drawable,
	public Updatable,
	public Creatable,
       	public Animated,
	public Physical,
	public Colored,
	public Textured	{
		protected:
			int 			m_id;
			std::string 		m_name;

			glm::vec2		m_position;
			float			m_rotation;
			glm::vec2		m_velocity;
			glm::vec2		m_angular_velocity;

			std::vector<Body> 	m_bodies;
			//std::vector<Joint>	m_joints;
		public:
			Model();
			~Model();

			void Register( App& t_app );
	}; // class Model
}; // namespace n2d

#endif
