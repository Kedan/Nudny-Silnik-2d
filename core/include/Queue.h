#ifndef NUDNY_SILNIK_2D_CORE_QUEUE_H
#define NUDNY_SILNIK_2D_CORE_QUEUE_H

#include <Interfaces.h>

namespace nudny {
	
	class Queue;

	template<typename T>
	class TQueue {
		public:
			TQueue(){};
			bool Exists( T& t_T) {
				for( auto t : m_queue ) {
					if( t.get() == &t_T )
						return true;
				}
				return false;
			}

			bool Exists( std::shared_ptr<T> t_T ) {
				for( auto t : m_queue ) {
					if( t == t_T)
						return true;
				}
				return false;
			}

			bool Add( T& t_T ) {
				if( !Exists( t_T ) ) {
					m_queue.push_back( std::shared_ptr<T>(&t_T) );
					return true;
				}
				return false;
			}

			bool Add( std::shared_ptr<T> t_T ) {
				if( !Exists( t_T )) {
					m_queue.push_back( t_T );
					return true;
				}
				return false;
			}

			bool Remove( T& t_T ) {
				int i = 0;
				for( auto t : m_queue ) {
					if( t.get() == &t_T ) {
						m_queue.erase( m_queue.begin() + i );
						return true;
					}
					i++;
				}
				return false;
			}
			bool Remove( std::shared_ptr<T> t_T ) {
				int i = 0;
				for( auto t : m_queue ) {
					if( t == &t_T ) {
						m_queue.erase( m_queue.begin() + i );
						return true;
					}
					i++;
				}
				return false;
			}

			friend class Queue;
		protected:
			std::vector<std::shared_ptr<T>>		m_queue;
	}; // class Queue 

	class Queue {
		public:
			TQueue<Drawable>	drawable;
			TQueue<Updatable>	updatable;
			TQueue<Creatable>	creatable;
			TQueue<Interactive>	interactive;
			TQueue<Animated>	animated;
			
			Queue();

			void Draw( sf::RenderWindow& );
			void Draw( sf::RenderWindow&, sf::Transform& );
			void Update( sf::Time& );
			void Events( sf::Event& );
			void Create( b2World& );
			void Animate( sf::Time& );

			void Run( sf::Event&, sf::Time&, sf::RenderWindow& );
			void Run( sf::Event&, sf::Time&, sf::RenderWindow&, sf::Transform& );
			
			void Clear();
	}; // class GameQueue
}; // namespace nudny

#endif
