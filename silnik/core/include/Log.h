#ifndef NUDNY_LOG_H
#define NUDNY_LOG_H

#include <chrono>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <mutex>
#include <glm/glm.hpp>
#include <Tool.h>

namespace n2d {
	/**
	 * Makeing logs. As simple, as handy and useful.
	 */
	class Logger {
		protected:
			bool m_opened = false;
			std::ostringstream m_buffer;
			std::string m_filename = "./log";
		public:
			/** Steam where all comments are hold. Use like std::cout. */
			std::ostringstream out;
			Logger();

			/** 
			 * Set log file path.
			 * @param	- file path
			 */
			void SetFile( std::string );

			/**
			 * To delete. Use n2d::Logger::out stream.
			 */
			Logger& Log( const std::string& t_s );

			/**
			 * Put human-readanle datetime stamp into n2d::Logger::out.
			 */
			Logger& Time();

			/**
			 * Opens log, put some header into n2d::Logger::out stream.
			 * If you use logger in your own class, call this method once in constructor.
			 */
			void Open();

			/**
			 * Close log, put some footer into n2d::Logger::out steam.
			 * If you use logger in yout own class, call this method once - in destructor
			 */
			void Close();

			/**
			 * Save and clear the log.
			 * Write n2d::Logger::out stream into file, than clear it.
			 * When I use n2d::Logger, I call this method at the end of method.
			 */
			void Flush();

			/**
			 * Clear log buffers
			 */
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
