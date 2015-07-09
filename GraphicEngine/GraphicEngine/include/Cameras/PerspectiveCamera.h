#ifndef _PERSPECTIVECAMERA_H_
#define _PERSPECTIVECAMERA_H_

#include "Cameras/Camera.h"

class PerspectiveCamera : public Camera
{
public:

	PerspectiveCamera(float fov = 50.0f, float aspect = 1.0f, float near = 0.1f, float far = 2000.0f);

	void setFov(float fov);
	float getFov() const;

	void setAspect(float aspect);
	float getAspect() const;

	void setNear(float near);
	float getNear() const;

	void setFar(float far);
	float getFar() const;

	void updateProjectionMatrix();

private:

	float mFov;
	float mAspect;
	float mNear;
	float mFar;

};

#endif