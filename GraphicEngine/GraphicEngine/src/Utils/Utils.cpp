#include "Utils/Utils.h"

#include "prerequisites.h"

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