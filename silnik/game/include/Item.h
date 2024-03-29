#ifndef NUDNY_ITEM_H
#define NUDNY_ITEM_H

namespace n2d {
	class Item : public Entity {
		protected:
			int	m_value;
			float 	m_volume;
			float	m_weight;
			bool	m_usable;
		public:
			Item();
			int 	GetCapacity();
			bool 	IsUsable();
	}; // class Item
}; // namespace n2d

#endif
