#ifndef _SCENE_H_
#define _SCENE_H_

#include "Lights/Light.h"

class Scene
{
public:
	
	Scene();

	void loadFromFile(const std::string& filename);
	void _parseOBJ();
	void add(Object3D* obj, Object3D* parent = nullptr);
	void add(Light* obj, Object3D* parent = nullptr);
	void remove(Object3D* obj);

	Object3D* getRoot();
	std::vector<Object3D*>& getObjects();
	std::vector<Object3D*>& getObjectsWithoutMesh();
	Object3D* getObject(uint index);

	std::vector<Light*> getLights();

	void autoUpdate(bool update);
	bool autoUpdate() const;

	void needUpdate();				// callback à appeler
	void updateObjectsList();
	void addObjectInList(Object3D* obj);

private:
	
	Object3D* mRoot;								// Root de la scène 
	std::vector<Object3D*> mObjects;				// Liste des objets à rendre pendant la frame
	std::vector<Object3D*> mObjectsWithoutMesh;		// Liste des objets sans mesh
	std::vector<Light*> mLights;

	bool mAutoUpdate;
	bool mObjectsListNeedsUpdate;
};

#endif