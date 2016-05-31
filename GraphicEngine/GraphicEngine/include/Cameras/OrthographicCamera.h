#ifndef _ORTHOGRAPHICCAMERA_H_
#define _ORTHOGRAPHICCAMERA_H_

#include "Cameras/Camera.h"

class OrthographicCamera : public Camera
{
public:

	OrthographicCamera(float left, float right, float bottom, float top, float near = 0.1f, float far = 30000.0f);

	void setSize(float s);
	float getSize() const;
	void updateProjectionMatrix();

private:

	float mLeft;
	float mRight;
	float mBottom;
	float mTop;
	float mNear;
	float mFar;

	float mSize;
};

#endif