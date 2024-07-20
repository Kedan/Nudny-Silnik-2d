#ifndef NUDNY_SILNIK_2D_UTILS_JSON_CLASS_H
#define NUDNY_SILNIK_2D_UTILS_JSON_CLASS_H

#include <iostream>
#include "json.hpp"

using json = nlohmann::json;

namespace nudny {
	class JSONLoader {
		protected:
			json m_JSON;
			std::vector<unsigned char> m_data; 
		public:
			JSONLoader();
			JSONLoader( std::string t_file );
			bool Load( std::string t_file );
			static bool Find( std::string t_value, json t_accessor ) {
				return t_accessor.find( t_value ) != t_accessor.end();
			}
			json GetData();
	};
};

#endif
