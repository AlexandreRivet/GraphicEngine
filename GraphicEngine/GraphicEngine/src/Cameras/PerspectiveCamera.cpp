#include "Cameras/PerspectiveCamera.h"

PerspectiveCamera::PerspectiveCamera(float fov, float w, float h, float near, float far)
    : Camera(),
    mFov(fov),
    mWidth(w),
	mHeight(h),
    mNear(near),
    mFar(far)
{
    updateProjectionMatrix();
}

void PerspectiveCamera::set(float fov, float w, float h, float near, float far)
{
	mFov = fov;
	mWidth = w;
	mHeight = h;
	mNear = near;
	mFar = far;

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

void PerspectiveCamera::setWidth(float w)
{
	mWidth = w;

	updateProjectionMatrix();
}

void PerspectiveCamera::setHeight(float h)
{
	mHeight = h;

	updateProjectionMatrix();
}

float PerspectiveCamera::getAspect() const
{
    return mWidth / mHeight;
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
	float aspect = mWidth / mHeight;

	float xymax = mNear * std::tan(Math::degToRad(mFov * 0.5f));
	float ymin = -xymax;
	float xmin = -xymax;
	float width = xymax - xmin;
	float height = xymax - ymin;
	float depth = mFar - mNear;
	float q = -(mFar + mNear) / depth;
	float qn = -2.0f * mFar * mNear / depth;

    float w = 2 * mNear / width;
	w = w / aspect;
    float h = 2 * mNear / height;

    mProjectionMatrix = Matrix4(
		w,    0.0f, 0.0f,  0.0f,
        0.0f, h,    0.0f,  0.0f,
        0.0f, 0.0f, q,  -1.0f,
        0.0f, 0.0f, qn, 0.0f
    );

}