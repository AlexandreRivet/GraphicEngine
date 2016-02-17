#include "Objects/Scene.h"

Scene::Scene()
	: mAutoUpdate(true)
{
	mRoot = new Object3D();
}

void Scene::add(Object3D* obj, Object3D* parent)
{
	if (parent == nullptr)
		mRoot->addChild(obj);
	else
		parent->addChild(obj);

	needUpdate();
}

void Scene::addLight(Light* obj, Object3D* parent)
{
	if (parent == nullptr)
		mRoot->addChild(obj);
	else
		parent->addChild(obj);

	mDirectionalLight = obj;
}

void Scene::addLight(PointLight* obj, Object3D* parent)
{
	if (parent == nullptr)
		mRoot->addChild(obj);
	else
		parent->addChild(obj);

	mPointLights.push_back(obj);
}

void Scene::remove(Object3D* obj)
{
	if (obj->getParent() == nullptr)		// ça veut dire qu'on est au root faut pas déconner on y touche pas à lui
		return;

	obj->getParent()->removeChild(obj);

}

Object3D* Scene::getRoot()
{
	return mRoot;
}

std::vector<Object3D*>& Scene::getObjectsWithoutMesh()
{
	return mObjectsWithoutMesh;
}

std::vector<Object3D*>& Scene::getObjects()
{
	return mObjects;
}

Light* Scene::getDirectionalLight() const
{
	return mDirectionalLight;
}

std::vector<PointLight*> Scene::getPointLights() const
{
	return mPointLights;
}

void Scene::autoUpdate(bool update)
{
	mAutoUpdate = update;
}

bool Scene::autoUpdate() const
{
	return mAutoUpdate;
}

void Scene::needUpdate()
{
	mObjectsListNeedsUpdate = true;
}

void Scene::updateObjectsList()
{
	if (!mObjectsListNeedsUpdate)
		return;

	mObjects.clear();

	addObjectInList(mRoot);

	mObjectsListNeedsUpdate = false;
}

void Scene::addObjectInList(Object3D* obj)
{
	if (!obj->hasMesh())
		mObjectsWithoutMesh.push_back(obj);
	else
		mObjects.push_back(obj);

	std::vector<Object3D*>& children = obj->getChildren();

	for (uint i = 0; i < children.size(); ++i)
	{
		addObjectInList(children[i]);
	}
}