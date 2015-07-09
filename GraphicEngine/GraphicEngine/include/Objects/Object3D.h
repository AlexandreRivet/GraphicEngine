#ifndef _OBJECT3D_H_
#define _OBJECT3D_H_

#include <memory>

#include "prerequisites.h"
#include "Math/Vector3.h"
#include "Math/Quaternion.h"
#include "Math/Matrix4.h"

class Object3D
{
public:
	
	Object3D();

	void setPosition(const Vector3& v);
	void setRotation(const Quaternion& q);
	void setScale(const Vector3& v);

	void translateOnAxis(float distance, const Vector3& axis);
	void translateX(float distance);
	void translateY(float distance);
	void translateZ(float distance);
	
	void rotateOnAxis(float angle, const Vector3& axis);
	void rotateX(float angle);
	void rotateY(float angle);
	void rotateZ(float angle);

	void scaleOnAxis(float scale, const Vector3& axis);
	void scaleX(float scale);
	void scaleY(float scale);
	void scaleZ(float scale);

	void setParent(Object3D* object);
	void add(const Object3DSPtr& object);
	void remove(const Object3DSPtr& object);

	Vector3& getPosition();
	Vector3& getWorldPosition();
	Quaternion& getRotation();
	Quaternion& getWorldRotation();
	Vector3& getScale();
	Vector3& getWorldScale();

	Matrix4& getMatrix();
	Matrix4& getWorldMatrix();

	void updateMatrix();
	void updateWorldMatrix(bool force = false);

	void setVisible(bool visible, bool cascade = true);
	bool isVisble() const;


protected:

	Object3D* mParent;
	std::vector<Object3DSPtr> mChildren;

	Vector3 mPosition;
	Quaternion mRotation;
	Vector3 mScale;

	Matrix4 mMatrix;
	Matrix4 mWorldMatrix;
	bool mWorldMatrixNeedsUpdate;

	bool mVisible;

};

typedef std::shared_ptr<Object3D> Object3DSPtr;

#endif