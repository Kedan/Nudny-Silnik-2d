#ifndef NUDNY_SILNIK_2D_CORE_CONFIG_HPP
#define NUDNY_SILNIK_2D_CORE_CONFIG_HPP

#include "nlohmann/json.hpp"

namespace ns {
	class Config {
		public:
			Config( const Config& ) = delete;
			Config& operator=( const Config& ) = delete;
			static Config& getInstance();
			bool load( const std::string& );
			bool isLoaded();
			bool save( const std::string& );
			nlohmann::json&	json();
		private:
			Config(){};
			static std::unique_ptr<Config> 	m_instance;
			static std::mutex 				m_mutex;
			nlohmann::json					m_json;
			bool 							m_isLoaded{false};
	};
};

#endif
