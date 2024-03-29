#define NUDNY_LOG_ON

#include "Log.h"

using namespace n2d;

Logger::Logger(){}

void Logger::SetFile( std::string t_filepath ) {
	m_filename = t_filepath;
}

Logger& Logger::Log( const std::string& t_s ) {
#ifdef NUDNY_LOG_ON
	out << t_s;
#endif
	return *this;
}

void Logger::Time() {
#ifdef NUDNY_LOG_ON
	out << n2d::Tool::GetCurrentDatetime() << " - ";
#endif
}

void Logger::Open() {
#ifdef NUDNY_LOG_ON
	if( !m_opened ) {
		Clear();
		out << "- - - - - - - - - - - - - - - - - - - - - - - -\n" << "Log begin\nat " << n2d::Tool::GetCurrentDatetime() << "\n-\n\n";
		Flush();
		m_opened = true;
	}
#endif
}

void Logger::Close() {
#ifdef NUDNY_LOG_ON
	out << "\n-\nlog end\nat " << n2d::Tool::GetCurrentDatetime() << "\n\n";
	Flush();
	m_opened = false;
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
