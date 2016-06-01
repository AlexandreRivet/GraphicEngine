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

void Camera::setDirection(const Vector3& direction, bool yawFixed)
{
	Vector3 mYawFixedAxis = Vector3::UNIT_Z;
	Vector3 zAdjustVec = -direction;
	zAdjustVec.normalise();

	Quaternion targetWorldRotation;

	if (yawFixed)
	{
		Vector3 xVec = mYawFixedAxis.crossProduct(zAdjustVec);
		xVec.normalise();

		Vector3 yVec = zAdjustVec.crossProduct(xVec);
		yVec.normalise();

		targetWorldRotation.FromAxes(xVec, yVec, zAdjustVec);
	}
	else
	{
		Vector3 axes[3];
		mRotation.ToAxes(axes);
		Quaternion rotQuat;

		if ((axes[2] + zAdjustVec).squaredLength() < 0.00005f)
		{
			rotQuat.FromAngleAxis((float)M_PI, axes[1]);
		}
		else
		{
			rotQuat = axes[2].getRotationTo(zAdjustVec);
		}
		targetWorldRotation = rotQuat * mRotation;
	}

	mRotation = targetWorldRotation;

	updateMatrix();
}