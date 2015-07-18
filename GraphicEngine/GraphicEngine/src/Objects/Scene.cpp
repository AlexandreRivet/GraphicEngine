#include "Objects/Scene.h"

Scene::Scene()
	: mAutoUpdate(true),
	mRoot()
{

}

void Scene::add(Object3DUPtr& obj, Object3D* parent)
{
	if (parent == nullptr)
		mRoot->addChild(obj);
	else
		parent->addChild(obj);

	needUpdate();
}

void Scene::remove(Object3DUPtr& obj)
{
	if (obj->getParent() == nullptr)		// ça veut dire qu'on est au root faut pas déconner on y touche pas à lui
		return;

	obj->getParent()->removeChild(obj);

}

Object3DUPtr& Scene::getRoot()
{
	return mRoot;
}

std::vector<Object3D*>& Scene::getObjects()
{
	return mObjects;
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

void Scene::addObjectInList(Object3DUPtr& obj)
{
	if (!obj->isActive())
		return;

	if (obj->isVisble() && obj->hasMesh())
		mObjects.push_back(obj.get());

	std::vector<Object3DUPtr>& children = obj->getChildren();

	for (uint i = 0; i < children.size(); ++i)
	{
		addObjectInList(children[i]);
	}
}