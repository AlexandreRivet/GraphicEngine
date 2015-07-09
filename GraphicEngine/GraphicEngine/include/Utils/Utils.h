#ifndef _UTILS_H_
#define _UTILS_H_

#include <fstream>
#include <streambuf>
#include <cstdlib>

class Utils
{
public:
	static bool fileToString(const std::string& fileName, std::string& content);

};

#endif