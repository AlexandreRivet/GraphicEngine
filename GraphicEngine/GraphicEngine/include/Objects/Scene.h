#ifndef _SCENE_H_
#define _SCENE_H_

#include "Objects/Object3D.h"

class Scene
{
public:
	
	Scene();

	void add(Object3D obj, Object3D parent);
	void remove();

	void autoUpdate(bool update);
	bool autoUpdate() const;

	void needUpdate();				// callback à appeler
	void updateObjectsList();
	void addObjectInList(Object3DSPtr obj);

private:
	
	Object3DUPtr mRoot;
	std::vector<Object3D> mObjects;

	bool mAutoUpdate;
	bool mObjectsListNeedsUpdate;
};

#endif