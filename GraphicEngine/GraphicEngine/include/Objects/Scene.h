#ifndef _SCENE_H_
#define _SCENE_H_

#include "Objects/Object3D.h"

class Scene
{
public:
	
	Scene();

	void add(Object3D obj, Object3D parent);

	void autoUpdate(bool update);
	bool autoUpdate() const;

private:
	
	Object3DUPtr mRoot;
	std::vector<Object3D> mObjects;

	bool mAutoUpdate;

};

#endif