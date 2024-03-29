#ifndef NUDNY_LOG_H
#define NUDNY_LOG_H

#include <chrono>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <mutex>
#include <glm/glm.hpp>
#include <Interfaces.h>

namespace n2d {
	class Logger {
		protected:
			bool m_opened = false;
			std::ostringstream m_buffer;
			std::string m_filename = "./logs/log";
		public:
			Logger();
			void setFile( std::string );
			void log( const std::string& t_s );
			void time();
			void open();
			void close();
			void flush();
			void clear();
	}; // class Logger
}; // namespace 

#endif
