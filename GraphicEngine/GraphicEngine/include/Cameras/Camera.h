#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "Objects/Object3D.h"

class Camera : public Object3D
{
public:

	Camera();

    const Matrix4& getProjectionMatrix() const;
	Vector3 getWorldDirection() const;

protected:

	Matrix4 mProjectionMatrix;

};

#endif