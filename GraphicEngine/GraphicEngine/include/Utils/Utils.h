#ifndef _UTILS_H_
#define _UTILS_H_

#include <fstream>
#include <streambuf>
#include <cstdlib>
#include <vector>
#include <string>
#include <iomanip>
#include <iostream>
#include <sstream>

class Utils
{
public:
	static bool fileToString(const std::string& fileName, std::string& content);
	static std::vector<std::string> Utils::split(const std::string &s, char delim);
};

namespace tools
{
    template <typename T>
    void unusedArg(const T& value)
    {
        (void)value;
    }

    /**
    * Variadic template uses for remove the warnings, unused parameter function
    */
    template < typename T, typename... TArgs >
    void unusedArg(const T& value, TArgs... args)
    {
        (void)value;

        unusedArg(args...);
    }

	const std::string& to_string_presision(float f, int precision);
}

#endif