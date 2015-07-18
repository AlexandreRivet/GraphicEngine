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
	// On met à jour la position de la cam dans le monde
	c.updateWorldMatrix();

	// Mise à jour des objets à traiter
	s.updateObjectsList();

	// Trier les objets du plus loin au plus près
	std::vector<Object3D*>& objects = s.getObjects();

	std::sort(objects.begin(), objects.end(), [&c](Object3D* a, Object3D* b) ->bool
	{
		float distA = a->getWorldPosition().distance(c.getWorldPosition());
		float distB = b->getWorldPosition().distance(c.getWorldPosition());

		return distA < distB;
	});

	// glViewport(0, 0, mViewportWidth, mViewportHeight);

	if (mAutoClear)
	{
		glClearColor(mClearColor.x, mClearColor.y, mClearColor.z, 1.0f);
		glClearDepth(1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	// Parcourir les objets et faire les draw
	for (uint i = 0; i < objects.size(); ++i)
	{
		Object3D* obj = objects[i];
		MeshSPtr mesh = obj->getMesh();
		Geometry& geo = mesh->getGeometry();
		MaterialSPtr& mat = mesh->getMaterial();

		// On bind le material
		mat->bind();

		// On configure le reste des attributes
		// Sommets
		glBindBuffer(GL_ARRAY_BUFFER, mesh->mVerticesBuffer);
		GLuint positionLocation = mat->getShader()->attribute("a_position");
		glEnableVertexAttribArray(positionLocation);
		glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, sizeof(float)* 3, 0);

		// On envoie le reste des uniformes

		// On dessine
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->mIndicesBuffer);
		glDrawElements(GL_TRIANGLES, geo.getNbIndices(), GL_UNSIGNED_SHORT, 0);

		// On unbind le material
		mat->unbind();

	}

}