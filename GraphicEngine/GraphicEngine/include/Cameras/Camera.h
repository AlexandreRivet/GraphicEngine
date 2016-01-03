#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "Objects/Object3D.h"

class Camera : public Object3D
{
public:

	Camera();

    const Matrix4& getProjectionMatrix() const;
	Vector3 getWorldDirection() const;

	void lookAt(const Vector3& target, bool yawFixed = true);
	void setDirection(const Vector3& direction, bool yawFixed = true);

	virtual void updateProjectionMatrix();

protected:

	Matrix4 mProjectionMatrix;

};

#endif