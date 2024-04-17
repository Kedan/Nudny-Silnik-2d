#ifndef NUDNY_SILNIK_RESOURCE_H
#define NUDNY_SILNIK_RESOURCE_H

#include <vector>
#include <map>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Log.h"

namespace n2d {
	template<typename T>
	class Resource {
		protected:
			std::vector<T> 			m_data;
			std::map<std::string,int>	m_map;
		public:

			void ReserveMemory( int t_size ) {
				m_data.reserve( t_size );
			};

			int Load( std::string t_filepath ) {
				LOG.Time() << "Resources Load ( "<< t_filepath <<" ) - begin\n";
				int result = GetId( t_filepath );
				if( result == -1 ) {
					ReserveData();	
					result = m_data.size() - 1;
					if( !LoadData( result, t_filepath )) {
						std::cerr << "Resource Load  - Couldn't load: " << t_filepath << std::endl;
						m_data.pop_back();
						result = -1;
					} else {
						m_map[ t_filepath ] = result;
					}
				}
				LOG.Time() << "Resources Load - end( "<<(result>-1?"ok":"failed")<<" )\n";
				return result;
			}

			bool IsLoaded( std::string t_filepath ) {
				return m_map.find( t_filepath ) != m_map.end();
			}

			int GetId( std::string t_filepath ) {
				return IsLoaded( t_filepath ) ? m_map[ t_filepath ] : -1;
			}
			
			T Get( int t_id ) {
				return m_data[t_id];
			}

			T Get( std::string t_filepath ) {
				int id = GetIdOrLoad( t_filepath );
				return m_data[ id ];
			}

			T* GetPtr( int t_id ) {
				return t_id < m_data.size() ? &m_data[ t_id ] : nullptr;
			}

			T* GetPtr( std::string t_filepath ) {
				int id = GetIdOrLoad( t_filepath );
				return GetPtr( id );
			}

			T& GetRef( int t_id ) {
				return m_data[ t_id ];
			}
			
			T& GetRef( std::string t_filepath ) {
				int id = GetIdOrLoad( t_filepath );
				return m_data[ id ];
			}

			const T& GetCRef( int t_id ) {
				return m_data[ t_id ];
			}
			
			const T& GetCRef( std::string t_filepath ) {
				int id = GetIdOrLoad( t_filepath );
				return m_data[ id ];
			}
			
			void Free() {
				m_data.clear();
				m_map.clear();
			}
		protected:
			int GetIdOrLoad( std::string t_filepath ) {
				return IsLoaded( t_filepath ) ? GetId( t_filepath ) : Load( t_filepath );
			}
			virtual bool LoadData( int t_id,  std::string t_filepath ) = 0;
			virtual void ReserveData() = 0;
	}; // class Resource
	
	template<typename T>
	class ResourceSFML : public Resource<T> { 
		protected:
			void ReserveData() {
				Resource<T>::m_data.push_back( T() );
			}
			bool LoadData( int t_id, std::string t_filepath ) {
				return Resource<T>::m_data[ t_id ].loadFromFile( t_filepath );
			}
	};

	class ResourceSFMLMusic : public Resource<std::shared_ptr<sf::Music>> {
		protected:
			void ReserveData() {
				m_data.push_back(std::shared_ptr<sf::Music>( new sf::Music() ));
			}
			bool LoadData( int t_id, std::string t_filepath ) {
				return m_data[t_id]->openFromFile( t_filepath );
			}
	}; // class ResourceSFMLMusic
	
}; //namespace

#endif
