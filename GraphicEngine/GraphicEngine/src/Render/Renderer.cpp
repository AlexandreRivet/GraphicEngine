#include "Render/Renderer.h"

#include "GL/glew.h"

Renderer::Renderer()
	: mClearColor(Vector3::ZERO),
	mAutoClear(true)
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

void Renderer::setViewport(uint w, uint h)
{
	mViewportWidth = w;
	mViewportHeight = h;
}

uint Renderer::getWidth() const
{
	return mViewportWidth;
}

uint Renderer::getHeight() const
{
	return mViewportHeight;
}

void Renderer::render(Scene& s, Camera& c)
{
	// On met � jour la position de la cam dans le monde
	c.updateWorldMatrix();

	// Mise � jour des objets � traiter
	s.updateObjectsList();

	// Trier les objets du plus loin au plus pr�s
	std::vector<Object3D*>& objects = s.getObjects();

	std::sort(objects.begin(), objects.end(), [&c](Object3D* a, Object3D* b) ->bool
	{
		float distA = a->getWorldPosition().distance(c.getWorldPosition());
		float distB = b->getWorldPosition().distance(c.getWorldPosition());

		return distA < distB;
	});

	glViewport(0, 0, mViewportWidth, mViewportHeight);

	if (mAutoClear)
	{
		glClearColor(mClearColor.x, mClearColor.y, mClearColor.z, 1.0f);
		glClearDepth(1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	// Parcourir les objets et faire les draw
	/*for (uint i = 0; i < objects.size(); ++i)
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

		// Proj matrix
		mat->getShader()->setUniform("u_proj", c.getProjectionMatrix());

		// View matriw
		mat->getShader()->setUniform("u_view", c.getWorldMatrix());

		// World matrix
		mat->getShader()->setUniform("u_world", obj->getWorldMatrix());


		// On dessine
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->mIndicesBuffer);
		glDrawElements(GL_TRIANGLES, geo.getNbIndices(), GL_UNSIGNED_SHORT, 0);

		// On unbind le material
		mat->unbind();

	}*/

}