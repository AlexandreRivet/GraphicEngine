#ifndef _SCENE_H_
#define _SCENE_H_

#include "Lights/Light.h"
#include "Lights/PointLight.h"

class Scene
{
public:
	
	Scene();

	void loadFromFile(const std::string& filename);
	void _parseOBJ();
	void add(Object3D* obj, Object3D* parent = nullptr);
	void addLight(Light* l, Object3D* parent = nullptr);
	void addLight(PointLight* l, Object3D* parent = nullptr);
	void remove(Object3D* obj);

	Object3D* getRoot();
	std::vector<Object3D*>& getObjects();
	std::vector<Object3D*>& getObjectsWithoutMesh();
	Object3D* getObject(uint index);

	std::vector<PointLight*> getPointLights() const;
	Light* getDirectionalLight() const;

	void autoUpdate(bool update);
	bool autoUpdate() const;

	void needUpdate();								// callback à appeler
	void updateObjectsList();
	void addObjectInList(Object3D* obj);

private:
	
	Object3D* mRoot;								// Root de la scène 
	std::vector<Object3D*> mObjects;				// Liste des objets à rendre pendant la frame
	std::vector<Object3D*> mObjectsWithoutMesh;		// Liste des objets sans mesh
	
	Light* mDirectionalLight;
	std::vector<PointLight*> mPointLights;

	bool mAutoUpdate;
	bool mObjectsListNeedsUpdate;
};

#endif