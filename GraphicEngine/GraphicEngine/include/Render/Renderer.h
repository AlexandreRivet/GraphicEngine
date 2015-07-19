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

	void setViewport(uint w, uint h);
	uint getWidth() const;
	uint getHeight() const;

	void render(Scene& s, Camera& c);

private:

	Vector3 mClearColor;
	
	uint mViewportWidth;
	uint mViewportHeight;

	bool mAutoClear;
	
};


#endif