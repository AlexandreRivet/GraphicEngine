#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "prerequisites.h"
#include "Math/Vector3.h"

#include "Objects/Scene.h"
#include "Cameras/Camera.h"
#include "UI/UIManager.h"

struct TypeRender
{
	Pass* pass;
	Object3D* obj;

	TypeRender(Pass* p, Object3D* o)
		: pass(p),
		obj(o)
	{

	}
};

struct Transparent : public TypeRender
{
	Transparent(Pass* p, Object3D* o) : TypeRender(p, o) {}
};

struct Opaque : public TypeRender
{
	Opaque(Pass* p, Object3D* o) : TypeRender(p, o) {}
};

struct ListPass
{
	std::vector<TypeRender> opaques;
	std::vector<TypeRender> transparents;
};

struct RenderGroup
{
	int index;
	std::vector<Object3D*> objects;
	ListPass passList;

	RenderGroup(int _index, Object3D* _obj)
		: index(_index)
	{
		objects.push_back(_obj);
	}
};


class Renderer
{
public:

	Renderer();

	void setClearColor(const Vector3& color);
	Vector3& getClearColor();

	void setViewport(uint w, uint h);
	uint getWidth() const;
	uint getHeight() const;

	void render(const std::function<void()>& renderFunction, UI::UIManager& uiManager);
	void render(Scene& s, Camera& c, UI::UIManager& uiManager);
	void render(Scene& s, Camera& c);
	void render(UI::UIManager& uiManager);
	

	void _renderShaderProgram(ShaderProgram* sp, Pass* p, Scene* s, Object3D* obj, Camera* c);

	void setAutoClear(bool clear);
	bool autoClear() const;

	void setAutoUpdate(bool update);
	bool autoUpdate() const;

	void _renderPassListFromType(std::vector<TypeRender>& p, Scene* s, Camera* c, bool reverse);
	template <typename T> void _renderPassList(T start, T end, Scene* s, Camera* c);
	bool _renderShadowMap(Scene* s, Camera* c);

private:

	Vector3 mClearColor;
	
	uint mViewportWidth;
	uint mViewportHeight;

	bool mAutoClear;
	bool mAutoUpdate;
	
};


#endif