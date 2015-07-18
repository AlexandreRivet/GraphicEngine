#ifndef _SCENE_H_
#define _SCENE_H_

#include "Objects/Object3D.h"

class Scene
{
public:
	
	Scene();

	void add(Object3DUPtr& obj, Object3D* parent = nullptr);
	void remove(Object3DUPtr& obj);

	Object3DUPtr& getRoot();
	std::vector<Object3D*>& getObjects();

	void autoUpdate(bool update);
	bool autoUpdate() const;

	void needUpdate();				// callback à appeler
	void updateObjectsList();
	void addObjectInList(Object3DUPtr& obj);

private:
	
	Object3DUPtr mRoot;								// Root de la scène 
	std::vector<Object3D*> mObjects;				// Liste des objets à rendre pendant la frame

	bool mAutoUpdate;
	bool mObjectsListNeedsUpdate;
};

#endif