#include "Log.h"

std::string Log::file_name = "log.txt";
int Log::level = 1;

void Log::create_log(std::ostringstream& txt, int lvl) {
	std::ostringstream oss; 
	if(lvl == Log::get_level())
		Log::log((std::ostringstream&) (oss << txt.str()));
}

bool Log::log(const std::ostringstream& oss) {
	std::ofstream ofs(Log::file_name.c_str(), std::ios::out | std::ios::app);
    if (ofs.fail())
		return false;
    if (!(ofs << oss.str() << std::endl)) {
        ofs.close();
        return false;
	}
    ofs.close();
	return true;
}