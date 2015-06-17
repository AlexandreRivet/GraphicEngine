#ifndef _MATRIX3_H_
#define _MATRIX3_H_

#include "prerequisites.h"
#include "Vector3.h"

class Matrix3
{
	Matrix3(const float* data = nullptr);
	Matrix3(const Matrix3&);
	~Matrix3();

	Matrix3& operator = (const Matrix3&);




	static Matrix3 getIdentity();
	static Matrix3 getZero();
	void identity();
	void zero();
	float* getData();
	const float* getData() const;

	void setData(unsigned int index, float val);
	void setData(unsigned int row, unsigned int column, float val);

	Vector3 operator*(const Vector3&) const;
	Matrix3 operator*(const Matrix3&) const;

	void rotate(float);
	void translate(float x, float y);
	void scale(float x, float y);

private:
	float m_data[9];
};

#endif
