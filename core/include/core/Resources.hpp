#ifndef NUDNY_SILNIK_2D_CORE_RESOURCES_HPP
#define NUDNY_SILNIK_2D_CORE_RESOURCES_HPP

#include <string>
#include <vector>
#include <utility>
#include <memory>
#include <numeric>
#include <algorithm>
#include <iostream>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Audio/Music.hpp>

namespace ns {
	
	template<typename T>
	class Asset {
		public:
			Asset( int t_id, const std::string& t_path ) : m_id(t_id), m_path(t_path) {
				//load();
			}
			
			virtual bool load() = 0;
			
			inline bool operator==(const int& t_i ) const {
				return m_id == t_i;
			}

			inline bool operator==(const std::string& t_str ) const {
				return m_path == t_str;
			}
			
			T get() const {
				return m_data;
			}
		
			T& getr() {
				return m_data;
			}

			const T& getc() {
				return m_data;
			}
			
			inline int getId() const {
				return m_id;
			}
			
			inline std::string getPath() const {
				return m_path;
			}
		protected:
			int			m_id;
			std::string m_path;
			T			m_data;
	};

	template<typename T>
	class sfAsset : public Asset<T> {
		public:
			sfAsset( int t_id, const std::string& t_path ) : Asset<T>(t_id, t_path) {
				load();
			}
			bool load() {
				return this->m_data.loadFromFile( this->m_path );
			}
	};
	
	template<typename T>
	class sfMusicAsset : public Asset<std::shared_ptr<T>> {
		public:
			sfMusicAsset( int t_id, const std::string& t_path ) : Asset<T>(t_id, t_path) {
				load();
			}
			bool load() {
				return this->m_data->openFromFile(this->m_path );
			}
	};
	
	template< template<typename> class TWrapper, typename TClass>
	class Collection {
		public:
			Collection(const int& size){
				m_assets.reserve(size);
			};
			
			// load single asset
			int load(const std::string& t_path) {
				int result = -1;
				auto r = std::find(std::cbegin(m_assets), std::cend(m_assets), t_path);
				if(r==std::cend(m_assets)) {
					m_assets.push_back(TWrapper<TClass>(m_idPool,t_path));
					result = m_idPool;
					++m_idPool;
				} else { 
					std::cout << "\"" << t_path << "\" loaded already!";
					result = r->getId();
				}
				return result;
			}
			
			// load collection of assets 
			std::pair<bool,std::vector<bool>> load(const std::vector<std::string>& t_v) {
				std::vector<bool> load_results;
				for(auto s : t_v){
					load_results.push_back(load(s)<0?false:true);
				}
				return std::pair<bool,std::vector<bool>>{(load_results.size()!=std::accumulate(load_results.begin(),load_results.end(),0)),load_results};
			}
			
			int getId(const std::string& t_path) {
				auto r = std::find(std::cbegin(m_assets), std::cend(m_assets), t_path);
				if( r!=std::cend(m_assets))
					return r->getId();
			}

			TClass get(const int& i) {
				auto r = std::find(std::cbegin(m_assets), std::cend(m_assets), i);
				if( r!=std::cend(m_assets))
					return r->get();
				throw std::runtime_error("Asset not found");
			}
			
			TClass get(const std::string& t_path) {
				auto r = std::find(std::cbegin(m_assets), std::cend(m_assets), t_path);
				if( r!=std::cend(m_assets)) {
					return r->get();
				}
				int i = load(t_path);
				return get(i);
			}

			TClass& getr(const std::string& t_path) {
				auto r = std::find(std::cbegin(m_assets), std::cend(m_assets), t_path);
				if( r!=std::cend(m_assets)) {
					return r->getr();
				}
				int i = load(t_path);
				return getr(i);
			}

			const TClass* getc(const int& i) {
				auto r = std::find(std::cbegin(m_assets), std::cend(m_assets), i);
				if( r!=std::cend(m_assets))
					return *r.getc();
				return nullptr;
			}

			const TClass* cget(const std::string& t_path ) {
				auto r = std::find(std::cbegin(m_assets), std::cend(m_assets), t_path);
				if( r!=std::cend(m_assets))
					return *r.cget();
				int i = load(t_path);
				return cget(i);
			}

			inline int size() {
				return m_assets.size();
			}
		protected:
			int								m_idPool{0};
			std::vector<TWrapper<TClass>>	m_assets;
	};
	
	class Resources {
		public:
			Collection<sfAsset,sf::Font>		fonts{10};
		//	Collection<sfAsset,sf::Texture>		textures{100};
		//	Collection<sfAsset,sf::SoundBuffer>	sounds{100};
		//	Collection<sfMusicAsset,sf::Music>	music{10};
	};
}; // namespace ns

#endif
