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

	// Première chose à faire, c'est de mettre à jour les shadow map
	if(!_renderShadowMap(&s, &c))
		return;

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
		_renderPassListFromType(rg.passList.opaques, &s, &c, false);
		_renderPassListFromType(rg.passList.transparents, &s, &c, true);
	}	

	// Dernier reset
	glBlendFunc(GL_ONE, GL_ZERO);
	glBlendFuncSeparate(GL_ONE, GL_ZERO, GL_ONE, GL_ZERO);
	glDisable(GL_BLEND);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glDepthMask(GL_TRUE);
	glDepthRange(0.f, 1.f);
	glCullFace(GL_FRONT);
	glFrontFace(GL_CCW);

}

void Renderer::_renderPassListFromType(std::vector<TypeRender>& p, Scene* s, Camera* c, bool reverse)
{
	if (reverse)
		_renderPassList(p.rbegin(), p.rend(), s, c);
	else
		_renderPassList(p.begin(), p.end(), s, c);
}

template <typename T> void Renderer::_renderPassList(T start, T end,Scene* s, Camera* c)
{
	for (auto it = start; it != end; ++it)
	{
		TypeRender tr = *it;
		Pass* p = tr.pass;
		Object3D* obj = tr.obj;

		if (!p->checkLinked())
			continue;

		// Reset des valeurs GL
		glBlendFunc(GL_ONE, GL_ZERO);
		glBlendFuncSeparate(GL_ONE, GL_ZERO, GL_ONE, GL_ZERO);
		glDisable(GL_BLEND);
		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);
		glDepthMask(GL_TRUE);
		glDepthRange(0.f, 1.f);
		glCullFace(GL_BACK);
		glFrontFace(GL_CCW);

		MeshSPtr mesh = obj->getMesh();
		OpenGLBuffer buffers = mesh->getBuffers();

		glUseProgram(p->m_OpenGLProgram);

		_renderShaderProgram(p->m_vertexProgram, p, s, obj, c);
		_renderShaderProgram(p->m_fragmentProgram, p, s, obj, c);
		_renderShaderProgram(p->m_geometryProgram, p, s, obj, c);

		// Ici on lit la pass

		for (auto jt = p->m_parameters.begin(); jt != p->m_parameters.end(); ++jt)
		{
			std::pair<std::string, std::string> params_pass = *jt;
			PassParamDef ppd = MaterialManager::m_passParamDef.at(params_pass.first);
			std::vector<std::string> values = Utils::split(params_pass.second, ' ');
			ppd.render(values);
		}

		if (buffers.mIndexBuffer != nullptr && buffers.mIndexBuffer->numItems > 0)
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers.mIndexBuffer->id); 
			glDrawElements(p->getRenderMethod(), mesh->getGeometry().getNbIndices(), GL_UNSIGNED_INT, 0);			
		}
		else
		{
			glDrawArrays(p->getRenderMethod(), 0, mesh->getGeometry().getNbVertices());
		}		

		glUseProgram(0);
	}
}

void Renderer::_renderShaderProgram(ShaderProgram* sp, Pass* p, Scene* s, Object3D* obj, Camera* c)
{
	if (sp == nullptr)
		return;

	MeshSPtr mesh = obj->getMesh();
	OpenGLBuffer buffers = mesh->getBuffers();

	// On envoie les attributes à la CG
	for (auto jt = sp->m_attributes_auto.begin(); jt != sp->m_attributes_auto.end(); ++jt)
	{
		ShaderParameter* shaderParam = &(*jt).second;
		AttributeAuto aa = MaterialManager::m_attributesAuto.at(shaderParam->key);
		if (!shaderParam->isInit)
		{
			shaderParam->location = aa.init(p->m_OpenGLProgram, (*jt).first);
			shaderParam->isInit = true;
		}
		aa.render(p->m_OpenGLProgram, shaderParam->location, buffers);
	}

	// On envoie les sampler
	int numSampler = 0;
	for (auto jt = sp->m_samplers.begin(); jt != sp->m_samplers.end(); ++jt)
	{
		StringParameter* shaderParam = &(*jt).second;
		Sampler s = MaterialManager::m_samplers.at(shaderParam->key);
		if (!shaderParam->isInit)
		{
			shaderParam->location = s.init(p->m_OpenGLProgram, (*jt).first);
			shaderParam->isInit = true;
		}
		s.render(p->m_OpenGLProgram, shaderParam->location, p, shaderParam->value, numSampler);
		numSampler++;
	}

	// On envoie les uniform à la CG
	for (auto jt = sp->m_uniforms_auto.begin(); jt != sp->m_uniforms_auto.end(); ++jt)
	{
		ShaderParameter* shaderParam = &(*jt).second;
		UniformAuto ua = MaterialManager::m_uniformsAuto.at(shaderParam->key);
		if (!shaderParam->isInit)
		{
			shaderParam->location = ua.init(p->m_OpenGLProgram, (*jt).first);
			shaderParam->isInit = true;
		}
		ua.render(p->m_OpenGLProgram, shaderParam->location, (*jt).first, s, obj, c, numSampler);
	}

	// On envoie les uniform non auto
	for (auto jt = sp->m_uniforms_noauto.begin(); jt != sp->m_uniforms_noauto.end(); ++jt)
	{
		FloatParameter* floatParam = &(*jt).second;
		if (!floatParam->isInit)
		{
			floatParam->location = MaterialManager::_initShaderProgramUniformAuto(p->m_OpenGLProgram, (*jt).first);			// Pour acquérir la location on peut considérer que c'est comme un uniform auto
			floatParam->isInit = true;
		}
		MaterialManager::_renderShaderProgramUniformNoAuto(p->m_OpenGLProgram, floatParam->location, floatParam->values);
	}
}

bool Renderer::_renderShadowMap(Scene* s, Camera* c)
{
	Light* light = s->getDirectionalLight();

	if (light == nullptr || ((light != nullptr) && !light->canCastShadow()))
		return true;

	std::vector<Object3D*> objects = s->getObjects();

	Material* mat = MaterialManager::getMaterial("ShadowMapMaterial");
	Pass* pass = mat->getPass("FirstPass");

	if (!pass->checkLinked())
		return false;

	// On utilise toujours le même programme
	glUseProgram(pass->m_OpenGLProgram);
	
	// On crée une caméra ortho qui sera toujours la même
	OrthographicCamera* ortho = new OrthographicCamera(-(mViewportWidth / 2.f), (mViewportWidth / 2.f), (mViewportHeight / 2.f), -(mViewportHeight / 2.f), 0.1f, 500.f);

	// On acquiert les différentes location
	GLint worldLocation = glGetUniformLocation(pass->m_OpenGLProgram, "uWorldMatrix");
	GLint spaceLocation = glGetUniformLocation(pass->m_OpenGLProgram, "uLightSpaceMatrix");
	GLint positionLocation = glGetAttribLocation(pass->m_OpenGLProgram, "aPosition");

	float arr[16];

	light->setShadowCamera(ortho);

	glViewport(0, 0, light->getShadowMapWidth(), light->getShadowMapHeight());
		
	glBindFramebuffer(GL_FRAMEBUFFER, light->getDepthMapFBO());
		
	glClear(GL_DEPTH_BUFFER_BIT);

	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);

	// On bind les matrices pour la light
	Matrix4 lightProjMat = light->getProjectionLight();
	Matrix4 spaceMatrix = lightProjMat * Matrix4().lookAt(light->getWorldPosition(), Vector3(0.0, 0.0, 0.0), Vector3(0.0, 1.0, 0.0));
	spaceMatrix.toArray(arr);
	glUniformMatrix4fv(spaceLocation, 1, GL_FALSE, arr);

	// On parcourt chaque objets dans la scène
	for (auto jt = objects.begin(); jt != objects.end(); ++jt)
	{
		Object3D* obj = *jt;

		if (!obj->isAbsoluteVisible() || !obj->hasMesh() || !obj->canCastShadow())
			continue;

		MeshSPtr mesh = obj->getMesh();
		OpenGLBuffer buffers = mesh->getBuffers();

		// World
		obj->getWorldMatrix().toArray(arr);
		glUniformMatrix4fv(worldLocation, 1, GL_FALSE, arr);
			
		// Vertex buffer
		glBindBuffer(GL_ARRAY_BUFFER, buffers.mVertexBuffer->id);
		glVertexAttribPointer(positionLocation, buffers.mVertexBuffer->itemSize, GL_FLOAT, false, 0, 0);
		glEnableVertexAttribArray(positionLocation);

		if (buffers.mIndexBuffer != nullptr && buffers.mIndexBuffer->numItems > 0)
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers.mIndexBuffer->id);
			glDrawElements(GL_TRIANGLES, mesh->getGeometry().getNbIndices(), GL_UNSIGNED_INT, 0);
		}
		else
		{
			glDrawArrays(GL_TRIANGLES, 0, mesh->getGeometry().getNbVertices());
		}

	}

	light->setShadowCamera(nullptr);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glUseProgram(0);

	// On remet le viewport correctement
	glViewport(0, 0, mViewportWidth, mViewportHeight);
	if (mAutoClear)
	{
		glClearColor(mClearColor.x, mClearColor.y, mClearColor.z, 1.0f);
		glClearDepth(1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	return true;

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