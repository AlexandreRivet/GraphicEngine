#ifndef _SCENE_H_
#define _SCENE_H_

#include "Objects/Object3D.h"

class Scene : public Object3D
{
public:
	
	Scene();

	void autoUpdate(bool update);
	bool autoUpdate() const;

private:
	
	bool mAutoUpdate;

};

#endif