#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "Objects/Object3D.h"

class Camera : public Object3D
{
public:

	Camera();

	virtual Matrix4& getProjectionMatrix();

	Vector3& getWorldDirection() const;

protected:

	Matrix4 mProjectionMatrix;

};

#endif