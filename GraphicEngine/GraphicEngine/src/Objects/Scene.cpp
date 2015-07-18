#include "Objects/Scene.h"

Scene::Scene()
	: mAutoUpdate(true)
{

}

void Scene::add(Object3D obj, Object3D parent)
{
	// TODO
}

void Scene::remove()
{
	// TODO
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

	// Faut envoyer le root mais c'est unique_ptr
	// addObjectInList(mRoot);

	mObjectsListNeedsUpdate = false;
}

void Scene::addObjectInList(Object3DSPtr obj)
{
	if (!obj->isActive())
		return;


	// faut push les objets mais que faire si on reçoit le root c'est un unique_ptr
	// sinon ça peut être object3d simple ou un shared_ptr
	// mObjects.push_back(obj);

	std::vector<Object3DSPtr> children = obj->getChildren();

	for (uint i = 0; i < children.size(); ++i)
	{
		addObjectInList(children[i]);
	}
}