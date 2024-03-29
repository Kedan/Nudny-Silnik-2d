#define NUDNY_LOG_ON

#include "Log.h"

using namespace n2d;

Logger::Logger(){}

void Logger::setFile( std::string t_filepath ) {
	m_filename = t_filepath;
}

void Logger::log( const std::string& t_s ) {
#ifdef NUDNY_LOG_ON
	m_buffer << t_s;
#endif
}

void Logger::time() {
#ifdef NUDNY_LOG_ON
	m_buffer << n2d::Tool::GetCurrentDatetime() << " - ";
#endif
}

void Logger::open() {
#ifdef NUDNY_LOG_ON
	if( !m_opened ) {
		clear();
		m_buffer << "- - - - - - - - - - - - - - - - - - - - - - - -\n" << "Log begin\nat " << n2d::Tool::GetCurrentDatetime() << "\n-\n\n";
		flush();
		m_opened = true;
	}
#endif
}

void Logger::close() {
#ifdef NUDNY_LOG_ON
	m_buffer << "\n-\nlog end\nat " << n2d::Tool::GetCurrentDatetime() << "\n\n";
	flush();
	m_opened = false;
#endif
}	

void Logger::flush() {
#ifdef NUDNY_LOG_ON
	std::ofstream file( m_filename, std::ios::out | std::ios::app );
	if( file.is_open() ) {
		file << m_buffer.str();
		file.close();
		clear();
	} else {
		std::cerr << "n2d::log::write - could not open "<< m_filename <<" log file \n";
	}
#endif
};

void Logger::clear() {
#ifdef NUDNY_LOG_ON
	m_buffer.str("");
	m_buffer.clear();
#endif
}
