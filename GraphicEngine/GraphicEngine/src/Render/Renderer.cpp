#include "Render/Renderer.h"

#include "GL/glew.h"

Renderer::Renderer()
{

}

void Renderer::setClearColor(const Vector3& color)
{
	mClearColor = color;
}

Vector3& Renderer::getClearColor()
{
	return mClearColor;
}

void Renderer::render(Scene& s, Camera& c)
{
	if (s.autoUpdate() == true)
		s.updateWorldMatrix();

	if (c.getParent() == nullptr)
		c.updateWorldMatrix();

	// Trier les objets
	std::vector<Object3DSPtr> objects;
	projectObjects(s.getChildren(), &objects);			// On fait juste une liste continue de tous les objets de la liste

	std::vector<Object3DSPtr> objectsSorted;




	if (mAutoClear)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(mClearColor.x, mClearColor.y, mClearColor.z, 1.0f);
	}

	// Parcourir les objets


}

void Renderer::projectObjects(std::vector<Object3DSPtr>& objects, std::vector<Object3DSPtr>* out)
{
	if (objects.size() == 0)
		return;

	for (uint i = 0; i < objects.size(); ++i)
	{
		out->push_back(objects[i]);
		projectObjects(objects[i]->getChildren(), out);
	}
}

void Renderer::sortObjectByDistance(std::vector<Object3DSPtr>& objects, Camera& c)
{

}