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

namespace tools
{
    template <typename T>
    void unusedArg(T& value)
    {
        (void)value;
    }

    /**
    * Variadic template uses for remove the warnings, unused parameter function
    */
    template < typename T, typename... TArgs >
    void unusedArg(T& value, TArgs... args)
    {
        (void)value;

        unusedArg(args...);
    }
}

#endif