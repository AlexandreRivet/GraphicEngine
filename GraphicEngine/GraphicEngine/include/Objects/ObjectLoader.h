#ifndef _OBJECTLOADER_H_
#define _OBJECTLOADER_H_

#include <string>
#include <map>

#include "Utils\Utils.h"
#include "Objects\Object3D.h"


class ObjectLoader
{
public:

	static Object3D load(const std::string& filename);

protected:

	static Object3D _loadOBJ(const std::string&);
	static Object3D _loadFBX(const std::string&);


private:

	ObjectLoader();
};

#endif //_OBJECTLOADER_H_