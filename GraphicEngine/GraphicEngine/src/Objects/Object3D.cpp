#include "Objects/Object3D.h"

Object3D::Object3D()
	: mMesh(nullptr),
	mPosition(Vector3::ZERO),
	mRotation(Quaternion::IDENTITY),
	mScale(Vector3::UNIT_SCALE),
	mHasMesh(false),
	mVisible(true),
	mActive(true)
{
	updateMatrix();
}

Object3D::Object3D(MeshSPtr m)
	: mMesh(m),
	mPosition(Vector3::ZERO),
	mRotation(Quaternion::IDENTITY),
	mScale(Vector3::UNIT_SCALE),
	mHasMesh(true),
	mVisible(true),
	mActive(true)
{
	updateMatrix();
}

void Object3D::setPosition(const Vector3& v)
{
	mPosition = v;
	updateMatrix();
}

void Object3D::setRotation(const Quaternion& q)
{
	mRotation = q;
	updateMatrix();
}

void Object3D::setScale(const Vector3& v)
{
	mScale = v;
	updateMatrix();
}

void Object3D::translateOnAxis(float distance, const Vector3& axis)
{
	Vector3 v1;
	v1 = mRotation * axis;
	mPosition += v1 * distance;
	updateMatrix();
}

void Object3D::translateX(float distance)
{
	translateOnAxis(distance, Vector3::UNIT_X);
}

void Object3D::translateY(float distance)
{
	translateOnAxis(distance, Vector3::UNIT_Y);
}

void Object3D::translateZ(float distance)
{
	translateOnAxis(distance, Vector3::UNIT_Z);
}

void Object3D::rotateOnAxis(float angle, const Vector3& axis)
{
	Quaternion q;
	q.FromAngleAxis(angle, axis);
	mRotation = mRotation * q;
	updateMatrix();
}

void Object3D::rotateX(float angle)
{
	rotateOnAxis(angle, Vector3::UNIT_X);
}

void Object3D::rotateY(float angle)
{
	rotateOnAxis(angle, Vector3::UNIT_Y);
}

void Object3D::rotateZ(float angle)
{
	rotateOnAxis(angle, Vector3::UNIT_Z);
}

void Object3D::scaleOnAxis(float scale, const Vector3& axis)
{
	Vector3 v;
	v = axis * scale;

	if (axis.x == 0.0f)
		v.x = 1.0f;
	if (axis.y == 0.0f)
		v.y = 1.0f;
	if (axis.z == 0.0f)
		v.z = 1.0f;

	mScale *= v;
	updateMatrix();
}

void Object3D::scaleX(float scale)
{
	scaleOnAxis(scale, Vector3::UNIT_X);
}

void Object3D::scaleY(float scale)
{
	scaleOnAxis(scale, Vector3::UNIT_Y);
}

void Object3D::scaleZ(float scale)
{
	scaleOnAxis(scale, Vector3::UNIT_Z);
}

void Object3D::setMesh(MeshSPtr m)
{
	mMesh = m;
}

MeshSPtr& Object3D::getMesh()
{
	return mMesh;
}

bool Object3D::hasMesh() const
{
	return mMesh != nullptr;
}

void Object3D::addChild(Object3DUPtr& child)
{
	child->setParent(this);
	mChildren.push_back(std::move(child));
}

void Object3D::removeChild(Object3DUPtr& child)
{
	mChildren.erase(std::find(mChildren.begin(), mChildren.end(), child));
}

void Object3D::setParent(Object3D* object)
{
	mParent = object;
}

Object3D* Object3D::getParent()
{
	return mParent;
}

std::vector<Object3DUPtr>& Object3D::getChildren()
{
	return mChildren;
}

Vector3& Object3D::getPosition()
{
	return mPosition;
}

Vector3 Object3D::getWorldPosition()
{
	updateWorldMatrix(true);

	Vector3 pos;
	mWorldMatrix.getTrans(pos);
	return pos;
}

Quaternion& Object3D::getRotation()
{
	return mRotation;
}

Quaternion Object3D::getWorldRotation()
{
	updateWorldMatrix(true);

	return mWorldMatrix.extractQuaternion();
}

Vector3& Object3D::getScale()
{
	return mScale;
}

Vector3 Object3D::getWorldScale()
{
	updateWorldMatrix(true);

	Vector3 scale;
	mWorldMatrix.getScale(scale);
	return scale;
}

Matrix4& Object3D::getMatrix()
{
	return mMatrix;
}

Matrix4& Object3D::getWorldMatrix()
{
	if (mWorldMatrixNeedsUpdate)
		updateWorldMatrix();

	return mWorldMatrix;
}

void Object3D::updateMatrix()
{
	mMatrix.makeTransform(mPosition, mScale, mRotation);

	mWorldMatrixNeedsUpdate = true;
}

void Object3D::updateWorldMatrix(bool force)
{
	if (mWorldMatrixNeedsUpdate || force)
	{
		if (mParent == nullptr)
		{
			mWorldMatrix = mMatrix;
		}
		else
		{
			mWorldMatrix = mParent->getWorldMatrix() * mMatrix;
		}

		mWorldMatrixNeedsUpdate = false;

	}
}

void Object3D::setVisible(bool visible, bool cascade)
{
	mVisible = false;

	if (cascade)
	{
		std::vector<Object3DUPtr>::iterator iter = mChildren.begin();
		std::vector<Object3DUPtr>::iterator end = mChildren.end();

		for (; iter != end; ++iter)
		{
			(*iter)->setVisible(visible, cascade);
		}
	}
}

bool Object3D::isVisble() const
{
	return mVisible;
}

void Object3D::setActive(bool active)
{
	mActive = active;
}

bool Object3D::isActive() const
{
	return mActive;
}
