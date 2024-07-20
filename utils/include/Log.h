#ifndef NUDNY_SILNIK_2D_UTILS_LOG_H
#define NUDNY_SILNIK_2D_UTILS_LOG_H

#include <chrono>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <mutex>
#include <glm/glm.hpp>
#include <Tool.h>

namespace nudny {
	class Logger {
		protected:
			bool m_opened = false;
			std::ostringstream m_buffer;
			std::string m_filename = "./log";
		public:
			std::ostringstream out;
			Logger();
			void SetFile( std::string );
			Logger& Log( const std::string& t_s );
			Logger& Time();
			void Open();
			void Close();
			void Flush();
			void Clear();
			template<class T>
			Logger&  operator<<( T t_msg  ) {
				out << t_msg;
				Flush();
				return *this;
			}
	}; // class Logger
	
	static Logger LOG;
}; // namespace 

#endif
