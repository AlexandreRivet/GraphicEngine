#include "Objects/Scene.h"

Scene::Scene()
	: mAutoUpdate(true)
{

}

void Scene::autoUpdate(bool update)
{
	mAutoUpdate = update;
}

bool Scene::autoUpdate() const
{
	return mAutoUpdate;
}