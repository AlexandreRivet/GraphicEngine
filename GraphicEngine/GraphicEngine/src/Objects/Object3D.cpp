#include "Objects/Object3D.h"

Object3D::Object3D()
	: mName("Unknown"),
	mMesh(nullptr),
	mPosition(Vector3::ZERO),
	mRotation(Quaternion::IDENTITY),
	mScale(Vector3::UNIT_SCALE),
	mMatrixNeedsUpdate(true),
	mWorldMatrixNeedsUpdate(true),
	mRenderGroupIndex(50),
	mVisible(true),
	mAbsoluteVisible(true),
	mCastShadow(true),
	mReceiveShadow(true)
{

}

Object3D::Object3D(const std::string& name)
	: mName(name),
	mMesh(nullptr),
	mPosition(Vector3::ZERO),
	mRotation(Quaternion::IDENTITY),
	mScale(Vector3::UNIT_SCALE),
	mMatrixNeedsUpdate(true),
	mWorldMatrixNeedsUpdate(true),
	mRenderGroupIndex(50),
	mVisible(true),
	mAbsoluteVisible(true),
	mCastShadow(true),
	mReceiveShadow(true)
{
	updateMatrix();
}

Object3D::Object3D(const std::string& name, MeshSPtr m)
	: mName(name),
	mMesh(m),
	mPosition(Vector3::ZERO),
	mRotation(Quaternion::IDENTITY),
	mScale(Vector3::UNIT_SCALE),
	mMatrixNeedsUpdate(true),
	mWorldMatrixNeedsUpdate(true),
	mRenderGroupIndex(50),
	mVisible(true),
	mAbsoluteVisible(true),
	mCastShadow(true),
	mReceiveShadow(true)
{
	updateMatrix();
}

const std::string& Object3D::getName() const
{
	return mName;
}

void Object3D::setPosition(const Vector3& v)
{
	mPosition = v;
	notifyUpdate(true);
}

void Object3D::setRotation(const Quaternion& q)
{
	mRotation = q;
	notifyUpdate(true);
}

void Object3D::setScale(const Vector3& v)
{
	mScale = v;
	notifyUpdate(true);
}

void Object3D::translateOnAxis(float distance, const Vector3& axis)
{
	Vector3 v1;
	v1 = mRotation * axis;
	mPosition += v1 * distance;
	notifyUpdate(true);
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
	notifyUpdate(true);
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
	notifyUpdate(true);
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

void Object3D::lookAt(const Vector3& target, bool yawFixed)
{
	Matrix4 m1 = mMatrix.lookAt(mPosition, target, Vector3::UNIT_Y);
	Matrix3 m2;
	m1.extract3x3Matrix(m2);
	mRotation.FromRotationMatrix(m2);

	notifyUpdate(true);
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

void Object3D::addChild(Object3D* child)
{
	child->setParent(this);
	mChildren.push_back(child);

	child->refreshAbsoluteVisible();
}

void Object3D::removeChild(Object3D* child)
{
	mChildren.erase(std::find(mChildren.begin(), mChildren.end(), child));
}

void Object3D::setParent(Object3D* object)
{
	mParent = object;

	notifyUpdate();
	refreshAbsoluteVisible();
}

Object3D* Object3D::getParent()
{
	return mParent;
}

std::vector<Object3D*>& Object3D::getChildren()
{
	return mChildren;
}

Vector3& Object3D::getPosition()
{
	return mPosition;
}

Vector3 Object3D::getWorldPosition()
{
	if (mMatrixNeedsUpdate)
		updateMatrix();

	if (mMatrixNeedsUpdate || mWorldMatrixNeedsUpdate)
		updateWorldMatrix();

	return mDerivedPosition;
}

Quaternion& Object3D::getRotation()
{
	return mRotation;
}

Quaternion Object3D::getWorldRotation()
{
	if (mMatrixNeedsUpdate)
		updateMatrix();

	if (mMatrixNeedsUpdate || mWorldMatrixNeedsUpdate)
		updateWorldMatrix();

	return mDerivedOrientation;
}

Vector3& Object3D::getScale()
{
	return mScale;
}

Vector3 Object3D::getWorldScale()
{
	if (mMatrixNeedsUpdate)
		updateMatrix();

	if (mMatrixNeedsUpdate || mWorldMatrixNeedsUpdate)
		updateWorldMatrix();

	return mDerivedScale;
}

void Object3D::setVisible(bool visible, bool cascade)
{
	mVisible = visible;
	mAbsoluteVisible = ((mParent != nullptr) ? mParent->isAbsoluteVisible() : true) && mVisible;

	std::vector<Object3D*>::iterator iter = mChildren.begin();
	std::vector<Object3D*>::iterator end = mChildren.end();

	if (cascade)
	{
		for (; iter != end; ++iter)
			(*iter)->setVisible(visible, cascade);
	}
	else
	{
		for (; iter != end; ++iter)
			(*iter)->refreshAbsoluteVisible();
	}
}

bool Object3D::isVisble() const
{
	return mVisible;
}

void Object3D::refreshAbsoluteVisible()
{
	mAbsoluteVisible = ((mParent != nullptr) ? mParent->isAbsoluteVisible() : true) && mVisible;
}

bool Object3D::isAbsoluteVisible() const
{
	return mAbsoluteVisible;
}

void Object3D::flipVisibility(bool cascade)
{
	mVisible = !mVisible;
	mAbsoluteVisible = ((mParent != nullptr) ? mParent->isAbsoluteVisible() : true) && mVisible;

	std::vector<Object3D*>::iterator iter = mChildren.begin();
	std::vector<Object3D*>::iterator end = mChildren.end();

	if (cascade)
	{
		for (; iter != end; ++iter)
			(*iter)->flipVisibility(cascade);
	}
	else
	{
		for (; iter != end; ++iter)
			(*iter)->refreshAbsoluteVisible();
	}
}


Matrix4& Object3D::getMatrix()
{
	return mMatrix;
}

void Object3D::updateMatrix()
{
	mMatrixNeedsUpdate = false;
	mMatrix.makeTransform(mPosition, mScale, mRotation);
}

Matrix4& Object3D::getWorldMatrix()
{
	if (mMatrixNeedsUpdate)
		updateMatrix();

	if (mMatrixNeedsUpdate || mWorldMatrixNeedsUpdate)
		updateWorldMatrix();

	return mWorldMatrix;
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
			mWorldMatrix = mMatrix * mParent->getWorldMatrix();
		}

		Matrix4 m = mWorldMatrix;
		mDerivedPosition = mWorldMatrix.getTrans();
		mDerivedOrientation = mWorldMatrix.extractQuaternion();
		mDerivedScale = mWorldMatrix.getScaleV3();

		mWorldMatrixNeedsUpdate = false;
	}
}


void Object3D::notifyUpdate(bool mustUpdateLocalMatrix)
{
	mMatrixNeedsUpdate = mMatrixNeedsUpdate || mustUpdateLocalMatrix;
	mWorldMatrixNeedsUpdate = true;

	for (uint i = 0; i < mChildren.size(); ++i)
		mChildren.at(i)->notifyUpdate();
}

int Object3D::getRenderGroupIndex() const
{
	return mRenderGroupIndex;
}

void Object3D::setRenderGroupIndex(int index)
{
	mRenderGroupIndex = index;
}

void Object3D::castShadow(bool cast)
{
	mCastShadow = cast;
}

bool Object3D::canCastShadow() const
{
	return mCastShadow;
}

void Object3D::receiveShadow(bool receive)
{
	mReceiveShadow = receive;
}

bool Object3D::canReceiveShadow() const
{
	return mReceiveShadow;
}