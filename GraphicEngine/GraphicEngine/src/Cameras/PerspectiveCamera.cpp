#include "Cameras/PerspectiveCamera.h"

PerspectiveCamera::PerspectiveCamera(float fov, float aspect, float near, float far)
	: mFov(fov),
	mAspect(aspect),
	mNear(near),
	mFar(far)
{
	updateProjectionMatrix();
}

void PerspectiveCamera::setFov(float fov)
{
	mFov = fov;

	updateProjectionMatrix();
}

float PerspectiveCamera::getFov() const
{
	return mFov;
}

void PerspectiveCamera::setAspect(float aspect)
{
	mAspect = aspect;

	updateProjectionMatrix();
}

float PerspectiveCamera::getAspect() const
{
	return mAspect;	
}

void PerspectiveCamera::setNear(float near)
{
	mNear = near;

	updateProjectionMatrix();
}

float PerspectiveCamera::getNear() const
{
	return mNear;
}

void PerspectiveCamera::setFar(float far)
{
	mFar = far;

	updateProjectionMatrix();
}

float PerspectiveCamera::getFar() const
{
	return mFar;
}

void PerspectiveCamera::updateProjectionMatrix()
{
	float top = mNear * std::tan(Math::degToRad(mFov * 0.5f));
	float bottom = -top;
	float left = bottom * mAspect;
	float right = top * mAspect;
	
	float x = 2 * mNear / (right - left);
	float y = 2 * mNear / (top - bottom);

	float a = (right + left) / (right - left);
	float b = (top + bottom) / (top - bottom);
	float c = -(mFar + mNear) / (mFar - mNear);
	float d = -2.0f * mFar * mNear / (mFar - mNear);

	mProjectionMatrix = Matrix4(

		x,	0,	a,	0,
		0,	y,	b,	0,
		0,	0,	c,	d,
		0,	0, -1,	0

	);

}