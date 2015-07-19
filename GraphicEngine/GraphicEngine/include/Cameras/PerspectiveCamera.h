#ifndef _PERSPECTIVECAMERA_H_
#define _PERSPECTIVECAMERA_H_

#include "Cameras/Camera.h"

class PerspectiveCamera : public Camera
{
public:

	PerspectiveCamera::PerspectiveCamera(float fov = 50.0f, float w = 800.0f, float h = 600.0f, float near = 0.1f, float far = 2000.0f);

	void setFov(float fov);
	float getFov() const;

	void setWidth(float w);
	void setHeight(float h);
	float getAspect() const;

	void setNear(float near);
	float getNear() const;

	void setFar(float far);
	float getFar() const;

	void updateProjectionMatrix();

private:

	float mFov;
	float mWidth;
	float mHeight;
	float mNear;
	float mFar;

};

#endif