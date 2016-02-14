#include "Utils/Utils.h"

#include "prerequisites.h"

#include <sstream>

bool Utils::fileToString(const std::string& fileName, std::string& content)
{
	std::ifstream file(fileName);

	if (file.is_open())
	{
		file.seekg(0, std::ios::end);
		content.reserve(static_cast<unsigned int>(file.tellg()));
		file.seekg(0, std::ios::beg);

		content.assign((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	}
	else
	{
		std::cout << "Can't open file : " << fileName << std::endl;
		return false;
	}

	return true;

}

std::vector<std::string> Utils::split(const std::string &s, char delim) 
{
	std::vector<std::string> elems;
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim)) 
	{
		elems.push_back(item);
	}
	return elems;
}

std::string Utils::trim(const std::string& s)
{
	if (s.empty())
		return s;

	std::size_t firstScan = s.find_first_not_of(' ');
	std::size_t first = firstScan == std::string::npos ? s.length() : firstScan;
	std::size_t last = s.find_last_not_of(' ');

	return s.substr(first, last - first + 1);
}

std::string tools::to_string_presision(float f, int precision)
{
	std::stringstream ss;
	ss << std::fixed << std::setprecision(precision) << f;
	return ss.str();
}

