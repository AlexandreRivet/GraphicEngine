#include "Render/Renderer.h"

#include "Utils/freeglut_include.h"
#include <list>
#include "Materials/MaterialManager.h"

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
	// Mise à jour des objets à traiter
	s.updateObjectsList();
	std::vector<Object3D*> objects = s.getObjects();

	// On va trier par renderGroup
	std::list<RenderGroup> renderGroups;

	// Ici on trie par render group
	for (uint i = 0; i < objects.size(); ++i)
	{
		Object3D* obj = objects[i];

		if (!obj->isAbsoluteVisible() || !obj->hasMesh())
			continue;

		int renderGroupIndex = obj->getRenderGroupIndex();

		std::list<RenderGroup>::iterator found = std::find_if(renderGroups.begin(), renderGroups.end(), [renderGroupIndex](RenderGroup rg) -> bool
		{
			return rg.index == renderGroupIndex;
		});

		// On n'a pas trouvé ce render group
		if (found == renderGroups.end())
			renderGroups.push_back(RenderGroup(renderGroupIndex, obj));
		else
			found->objects.push_back(obj);
	}

	renderGroups.sort([](RenderGroup a, RenderGroup b) {
		return a.index < b.index;
	});

	// On parcours chaque rendergroup
	for (auto it = renderGroups.begin(); it != renderGroups.end(); ++it)
	{
		RenderGroup rg = *it;

		// On trie d'abord par rapport à la caméra
		std::sort(rg.objects.begin(), rg.objects.end(), [&c](Object3D* a, Object3D* b) -> bool
		{
			float distA = a->getWorldPosition().distance(c.getWorldPosition());
			float distB = b->getWorldPosition().distance(c.getWorldPosition());

			return distA < distB;
		});

		// On va filtrer maintenant les opaques et les transparents
		for (auto objIt = rg.objects.begin(); objIt != rg.objects.end(); ++objIt)
		{
			Object3D* obj = *objIt;
			Material* mat = obj->getMesh()->getMaterial();

			if (mat == nullptr)
				continue;

			std::map<std::string, Pass*> passList = mat->getPassList();

			for (auto passIt = passList.begin(); passIt != passList.end(); ++passIt)
			{
				Pass* p = passIt->second;

				if (p->isTransparent())
					rg.passList.transparents.push_back(Transparent(p, obj));
				else
					rg.passList.opaques.push_back(Opaque(p, obj));
			}
		}

		// On va faire le rendu => opaques puis transparents
		_renderPassListFromType(rg.passList.opaques, &c, false);
		_renderPassListFromType(rg.passList.transparents, &c, true);
	}	
}

void Renderer::_renderPassListFromType(std::vector<TypeRender>& p, Camera* c, bool reverse)
{
	if (reverse)
		_renderPassList(p.rbegin(), p.rend(), c);
	else
		_renderPassList(p.begin(), p.end(), c);
}

template <typename T> void Renderer::_renderPassList(T start, T end, Camera* c)
{
	for (auto it = start; it != end; ++it)
	{
		TypeRender tr = *it;
		Pass* p = tr.pass;
		Object3D* obj = tr.obj;

		if (!p->checkLinked())
			continue;

		MeshSPtr mesh = obj->getMesh();
		OpenGLBuffer buffers = mesh->getBuffers();

		glUseProgram(p->m_OpenGLProgram);

		_renderShaderProgram(p->m_vertexProgram, p, obj, c);
		_renderShaderProgram(p->m_fragmentProgram, p, obj, c);
		_renderShaderProgram(p->m_geometryProgram, p, obj, c);

		// glBlendFunc(GL_ONE, GL_ZERO);
		// glBlendFuncSeparate(GL_ONE, GL_ZERO, GL_ONE, GL_ZERO);
		// glDisable(GL_BLEND);
		glDisable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);
		// glDepthFunc(GL_LEQUAL);
		// glDepthMask(GL_TRUE);
		// glDepthRange(0.f, 1.f);
		// glCullFace(GL_BACK);
		// glFrontFace(GL_CCW);

		if (buffers.mIndexBuffer != nullptr && buffers.mIndexBuffer->numItems > 0)
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers.mIndexBuffer->id);
			glDrawElements(GL_TRIANGLES, mesh->getGeometry().getNbIndices(), GL_UNSIGNED_INT, 0);
		}

		// glDrawArrays(GL_TRIANGLES, 0, mesh->getGeometry().getNbVertices());

		glUseProgram(0);
	}
}

void Renderer::_renderShaderProgram(ShaderProgram* sp, Pass* p, Object3D* obj, Camera* c)
{
	if (sp == nullptr)
		return;

	MeshSPtr mesh = obj->getMesh();
	OpenGLBuffer buffers = mesh->getBuffers();

	// On envoie les attributes à la CG
	for (auto jt = sp->m_attributes_auto.begin(); jt != sp->m_attributes_auto.end(); ++jt)
	{
		ShaderParameter sp = (*jt).second;
		AttributeAuto aa = MaterialManager::m_attributesAuto.at(sp.key);
		if (!sp.isInit)
		{
			sp.location = aa.init(p->m_OpenGLProgram, (*jt).first);
			sp.isInit = true;
		}
		aa.render(p->m_OpenGLProgram, sp.location, buffers);
	}

	// On envoie les uniform à la CG
	for (auto jt = sp->m_uniforms_auto.begin(); jt != sp->m_uniforms_auto.end(); ++jt)
	{
		ShaderParameter sp = (*jt).second;
		UniformAuto ua = MaterialManager::m_uniformsAuto.at(sp.key);
		if (!sp.isInit)
		{
			sp.location = ua.init(p->m_OpenGLProgram, (*jt).first);
			sp.isInit = true;
		}
		ua.render(p->m_OpenGLProgram, sp.location, obj, c);
	}

	// On envoie les sampler
	int numSampler = 0;
	for (auto jt = sp->m_samplers.begin(); jt != sp->m_samplers.end(); ++jt)
	{
		StringParameter sp = (*jt).second;
		Sampler s = MaterialManager::m_samplers.at(sp.key);
		if (!sp.isInit)
		{
			sp.location = s.init(p->m_OpenGLProgram, (*jt).first);
			sp.isInit = true;
		}
		s.render(p->m_OpenGLProgram, sp.location, p, sp.value, numSampler);
		numSampler++;
	}

	// On envoie les uniform non auto
	for (auto jt = sp->m_uniforms_noauto.begin(); jt != sp->m_uniforms_noauto.end(); ++jt)
	{
		FloatParameter fp = (*jt).second;
		if (!fp.isInit)
		{
			fp.location = MaterialManager::_initShaderProgramUniformAuto(p->m_OpenGLProgram, (*jt).first);			// Pour acquérir la location on peut considérer que c'est comme un uniform auto
			fp.isInit = true;
		}
		MaterialManager::_renderShaderProgramUniformNoAuto(p->m_OpenGLProgram, fp.location, fp.values);

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