#include <fstream>
#include "JSONLoader.h"

using namespace n2d;

JSONLoader::JSONLoader() {}

JSONLoader::JSONLoader( std::string file ) {
	Load( file );
}

bool JSONLoader::Load( std::string filename ) {
	bool result = false;
	std::string contents;
	std::ifstream file( filename, std::ios::binary );
	if( file ) {
		file >> JSON;
		file.close();
		result = true;
	} else {
		std::cout << "JSONLoader::Load() -> Nie znaleziono pliku "<< filename <<"!\n";
	}
	return result;
}

json JSONLoader::GetData() {
	return JSON;
}
