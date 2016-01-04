#include "Render/Renderer.h"

#include "Utils/freeglut_include.h"

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
	glViewport(0, 0, mViewportWidth, mViewportHeight);
}

uint Renderer::getWidth() const
{
	return mViewportWidth;
}

uint Renderer::getHeight() const
{
	return mViewportHeight;
}

void Renderer::render(const std::function<void()>& renderFunction, UI::UIManager& uiManager)
{
	glDepthMask(GL_TRUE);

	if (mAutoClear)
	{
		glClearColor(mClearColor.x, mClearColor.y, mClearColor.z, 1.0f);
		glClearDepth(1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	// rend la scène 3D
	renderFunction();

	// rend l'UI par dessus
	render(uiManager);

	// Inversion des buffers
	glutSwapBuffers();

	// Trick chelou
	Sleep(1);
}

void Renderer::render(Scene& s, Camera& c, UI::UIManager& uiManager)
{
	glDepthMask(GL_TRUE);
	
	if (mAutoClear)
	{
		glClearColor(mClearColor.x, mClearColor.y, mClearColor.z, 1.0f);
		glClearDepth(1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	// rend la scène 3D
	render(s, c);

	// rend l'UI par dessus
	render(uiManager);

	// Inversion des buffers
	glutSwapBuffers();

	// Trick chelou
	Sleep(1);
}

void Renderer::render(UI::UIManager& uiManager)
{
	glDepthMask(GL_FALSE);

	// On calcule les positions finales
	uiManager.computePosition(mViewportWidth, mViewportHeight);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, mViewportWidth, mViewportHeight, 0, 0, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Dessin
    uiManager.render();
}

void Renderer::render(Scene& s, Camera& c)
{
	// On met à jour la position de la cam dans le monde
	c.updateWorldMatrix();

	// Mise à jour des objets à traiter
	s.updateObjectsList();

	// Trier les objets du plus loin au plus près
	std::vector<Object3D*> objects = s.getObjects();

	std::sort(objects.begin(), objects.end(), [&c](Object3D* a, Object3D* b) ->bool
	{
		float distA = a->getWorldPosition().distance(c.getWorldPosition());
		float distB = b->getWorldPosition().distance(c.getWorldPosition());

		return distA < distB;
	});
	
	// Parcourir les objets et faire les draw
	for (uint i = 0; i < objects.size(); ++i)
	{
		Object3D* obj = objects[i];
		obj->updateWorldMatrix();

		if (obj->getRenderMode() == GL_POINTS)
		{
			glEnable(GL_POINT_SPRITE);
			glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
		}
			
		MeshSPtr mesh = obj->getMesh();
		Geometry& geo = mesh->getGeometry();
		MaterialSPtr& mat = mesh->getMaterial();

		// On bind le VAO
		glBindVertexArray(mesh->mVAO);

		// On bind le material
		mat->bind();

		// On envoie le reste des uniformes

		// Viewport
		mat->getShader()->setUniform("u_viewport", mViewportWidth, mViewportHeight);

		// Proj matrix
		mat->getShader()->setUniform("u_proj", c.getProjectionMatrix());

		// View matriw
		mat->getShader()->setUniform("u_view", c.getWorldMatrix().inverse());

		// World matrix
		mat->getShader()->setUniform("u_world", obj->getWorldMatrix());

		// On dessine
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->mIBO);
		glDrawElements(obj->getRenderMode(), geo.getNbIndices(), GL_UNSIGNED_INT, 0);

		// On unbind le material
		mat->unbind();
	}
	
}

void Renderer::setAutoUpdate(bool update)
{
	mAutoUpdate = update;
}

bool Renderer::autoUpdate() const
{
	return mAutoUpdate;
}

void Renderer::setAutoClear(bool clear)
{
	mAutoClear = clear;
}

bool Renderer::autoClear() const
{
	return mAutoClear;
}