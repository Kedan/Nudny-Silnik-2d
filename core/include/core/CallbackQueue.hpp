#ifndef NUDNY_SILNIK_2D_GAME_QUEUE_HPP
#define NUDNY_SILNIK_2D_GAME_QUEUE_HPP

#include <functional>
#include <memory>
#include <mutex>
#include <queue>
#include <vector>
#include <algorithm>

namespace ns {
	template<typename TClass, typename... TCallbackParams> 
	class CallbackQueue {
		public:
			CallbackQueue( void(TClass::*t_callback)(TCallbackParams...)) : m_callback(t_callback) {}
			
			void push( const std::shared_ptr<TClass>& t_object ) {
				std::lock_guard<std::mutex> lock( m_mutex );
				m_queue.push( std::weak_ptr<TClass>( t_object ));
			}

			void execute(TCallbackParams... t_params ){
				std::lock_guard<std::mutex> lock( m_mutex );
				while( !m_queue.empty() ) {
					if( auto ptr = m_queue.front().lock() ) {
						(ptr.get()->*m_callback)(t_params...);
					}
					m_queue.pop();
				}
			};
		protected:
			void (TClass::*m_callback)(TCallbackParams...){nullptr};
			std::queue<std::weak_ptr<TClass>>	m_queue;
			std::mutex m_mutex;
	};
};

#endif
