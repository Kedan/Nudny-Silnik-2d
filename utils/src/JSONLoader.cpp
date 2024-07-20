#include <fstream>
#include "JSONLoader.h"

using namespace nudny;

JSONLoader::JSONLoader() {}

JSONLoader::JSONLoader( std::string t_file ) {
	Load( t_file );
}

bool JSONLoader::Load( std::string t_filename ) {
	bool result = false;
	std::string contents;
	std::ifstream file( t_filename, std::ios::binary );
	if( file ) {
		file >> m_JSON;
		file.close();
		result = true;
	} else {
		std::cout << "JSONLoader::Load() -> Nie znaleziono pliku "<< t_filename <<"!\n";
	}
	return result;
}

json JSONLoader::GetData() {
	return m_JSON;
}
