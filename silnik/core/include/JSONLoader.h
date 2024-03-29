#ifndef NUDNY_JSON_LOADER_CLASS_H
#define NUDNY_JSON_LOADER_CLASS_H

#include <iostream>
#include "json.hpp"

using json = nlohmann::json;

namespace n2d {
	/**
	 * Class used for loading and easy hangling json files
	 */
	class JSONLoader {
		protected:
			/**
			 * json parser
			 */
			json JSON;
			/**
			 * Some stuff, Don't remember what for. Propablly raw data from json file.
			 */ 
			std::vector<unsigned char> data; 
		public:
			/**
			 * Default construcor
			 */
			JSONLoader();

			/**
			 * Construcor
			 * @param	t_file	- path to .json file
			 */ 
			JSONLoader( std::string t_file );

			/**
			 * Load method.
			 * @param	t_file	- path to .json file
			 * @return	true if file is loaded and parsed correctly. Else returns false.
			 */
			bool Load( std::string t_file );

			/**
			 * Searching values in json data
			 * @param	t_value		- Value you search
			 * @param	t_accessor	- json data you want to search in
			 * @return	true if finds value, false if don't	
			 */
			static bool Find( std::string t_value, json t_accessor ) {
				return t_accessor.find( t_value ) != t_accessor.end();
			}

			/**
			 * Returns parsed json data. Call this method ONLY if Load() returns true.
			 * @return	json data;
			 */ 
			json GetData();
	};
};

#endif
