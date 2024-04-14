#define NUDNY_LOG_ON
#define NUDNY_LOG_SAME_FILE

#include "Log.h"

using namespace n2d;

Logger::Logger(){}

void Logger::SetFile( std::string t_filepath ) {
#ifndef NUDNY_LOG_SAME_FILE
	m_filename = t_filepath;
#endif
}

Logger& Logger::Log( const std::string& t_s ) {
#ifdef NUDNY_LOG_ON
	out << t_s;
#endif
	return *this;
}

Logger& Logger::Time() {
#ifdef NUDNY_LOG_ON
	out << n2d::Tool::GetCurrentDatetime() << " - ";
	return *this;
#endif
}

void Logger::Open() {
#ifdef NUDNY_LOG_ON
#ifndef NUDNY_LOG_SAME_FILE
	if( !m_opened ) {
		Clear();
		out << "- - - - - - - - - - - - - - - - - - - - - - - -\n" << "Log begin\nat " << n2d::Tool::GetCurrentDatetime() << "\n-\n\n";
		Flush();
		m_opened = true;
	}
#endif
#endif
}

void Logger::Close() {
#ifdef NUDNY_LOG_ON
#ifndef NUDNY_LOG_SAME_FILE
	out << "\n-\nlog end\nat " << n2d::Tool::GetCurrentDatetime() << "\n\n";
	Flush();
	m_opened = false;
#endif
#endif
}	

void Logger::Flush() {
#ifdef NUDNY_LOG_ON
	std::ofstream file( m_filename, std::ios::out | std::ios::app );
	if( file.is_open() ) {
		file << out.str();
		file.close();
		Clear();
	} else {
		std::cerr << "n2d::log::write - could not open "<< m_filename <<" log file \n";
	}
#endif
};

void Logger::Clear() {
#ifdef NUDNY_LOG_ON
	out.str("");
	out.clear();
#endif
}
