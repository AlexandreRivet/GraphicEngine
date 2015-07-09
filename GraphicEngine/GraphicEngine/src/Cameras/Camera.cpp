#include "Cameras/Camera.h"

Camera::Camera()
	: mProjectionMatrix(Matrix4())
{

}

Matrix4& Camera::getProjectionMatrix()
{
	return mProjectionMatrix;
}

Vector3 Camera::getWorldDirection()
{




	return Vector3();
}