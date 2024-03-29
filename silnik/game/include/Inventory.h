#ifndef NUDNY_INVENTORY_H
#define NUDNY_INVENTORY_H

namespace n2d {
	class Inventory : public Entity {
		protected:
			float			max_volume;
			float			max_weight;
			float			current_volume;
			float			current_weight;
			std::vector<Item> 	items;
		public:
			Inventory( int );
			void AddItem( Item& );
			void SelectItem( int );
			void UseItem( int );
			void RemoveItem( int );
			void GrabAll( Inventory& );
			void DropAll();

			void Draw( sf::RenderWindow& );
			void Draw( sf::RenderWindow&, sf::Transform& );
			void Update( float );
			void Events( sf::Event& );
	}; // class Inventory
}; // namespace n2d

#endif
