#include <fstream>
#include "core/Config.hpp"

namespace ns {

std::unique_ptr<Config> Config::m_instance;
std::mutex Config::m_mutex;

Config& Config::getInstance() {
	std::lock_guard<std::mutex> lock(m_mutex);
	if(!m_instance)
		m_instance.reset(new Config());
	return *m_instance;
}

bool Config::load( const std::string& t_file ) {
	std::ifstream file( t_file, std::ios::binary );
	if( file ) {
		file >> m_json;
		file.close();
		return m_isLoaded=true;
	}
	return false;
}

bool Config::isLoaded() {
	return m_isLoaded;
}

bool Config::save( const std::string& t_file ) {
	return false;
}

nlohmann::json& Config::json() {
	return m_json;
}

} // namespace ns
