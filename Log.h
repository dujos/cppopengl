#ifndef LOG_H
#define LOG_H

#include <sstream>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

class Log {

protected:
	static std::string file_name;
	static int level;

public:
	static void create_log(std::ostringstream& txt, int lvl);
	static bool log(const std::ostringstream& oss);
	static int get_level() {return level;}

};

#endif