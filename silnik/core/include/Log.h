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
			std::ostringstream out;
			Logger();
			void SetFile( std::string );
			Logger& Log( const std::string& t_s );
			void Time();
			void Open();
			void Close();
			void Flush();
			void Clear();
	}; // class Logger
}; // namespace 

#endif
