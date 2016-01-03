#include "Cameras/OrthographicCamera.h"

OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top, float near, float far)
	: Camera(),
	mLeft(left),
	mRight(right),
	mBottom(bottom),
	mTop(top),
	mNear(near),
	mFar(far)
{
	updateProjectionMatrix();
}

void OrthographicCamera::updateProjectionMatrix()
{
	float w = mRight - mLeft;
	float h = mTop - mBottom;
	float d = mFar - mNear;

	mProjectionMatrix = Matrix4(
		2.0f / w,	0.0f,		0.0f,		-(mRight + mLeft) / w,
		0.0f,		2.0f / h,	0.0f,		-(mTop + mBottom) / h,
		0.0f,		0.0f,		-2.0f / d,  -(mFar + mNear) / d,
		0.0f,		0.0f,		0.0f,		1.0f
	);
	mProjectionMatrix = mProjectionMatrix.transpose();
}