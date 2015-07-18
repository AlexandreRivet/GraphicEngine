#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "prerequisites.h"
#include "Math/Vector3.h"

#include "Objects/Scene.h"
#include "Cameras/Camera.h"

class Renderer
{
public:

	Renderer();

	void setClearColor(const Vector3& color);
	Vector3& getClearColor();

	void render(Scene& s, Camera& c);

	void projectObjects(std::vector<Object3DSPtr>& objects, std::vector<Object3DSPtr>* out);
	void Renderer::sortObjectByDistance(std::vector<Object3DSPtr>& objects, Camera& c);

private:

	Vector3 mClearColor;

	bool mAutoClear;
	
};


#endif