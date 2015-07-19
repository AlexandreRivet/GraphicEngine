#include "Cameras/Camera.h"

Camera::Camera()
{

}

const Matrix4& Camera::getProjectionMatrix() const
{
	return mProjectionMatrix;
}

Vector3 Camera::getWorldDirection() const
{
	return Vector3();
}

void Camera::updateProjectionMatrix()
{
}