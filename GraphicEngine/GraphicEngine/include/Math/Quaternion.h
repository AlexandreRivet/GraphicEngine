#ifndef _QUATERNION_H_
#define _QUATERNION_H_

#include "prerequisites.h"

#include "Matrix3.h"
#include "Vector3.h"

class Quaternion
{
	public:
		float w;
		float x;
		float y;
		float z;

	public:
		Quaternion();
		Quaternion(float fW, float fX, float fY, float fZ);
		Quaternion(const Matrix3& rot);
		Quaternion(const float& rfAngle, const Vector3& rkAxis);
		Quaternion(const Vector3& xaxis, const Vector3& yaxis, const Vector3& zaxis);
		Quaternion(const Vector3* akAxis);
		
		void swap(Quaternion& other);
		float operator [] (const size_t i) const;
		float& operator [] (const size_t i);
		
		void FromRotationMatrix(const Matrix3& kRot);
		void ToRotationMatrix(Matrix3& kRot) const;
		void FromAngleAxis(const float& rfAngle, const Vector3& rkAxis);
		void ToAngleAxis(float& dAngle, Vector3& rkAxis) const;
		void FromAxes(const Vector3* akAxis);
		void FromAxes(const Vector3& xAxis, const Vector3& yAxis, const Vector3& zAxis);
		void ToAxes(Vector3* akAxis) const;
		void ToAxes(Vector3& xAxis, Vector3& yAxis, Vector3& zAxis) const;

		Vector3 xAxis(void) const;
		Vector3 yAxis(void) const;
		Vector3 zAxis(void) const;

		Quaternion& operator= (const Quaternion& rkQ);
		Quaternion operator+ (const Quaternion& rkQ) const;
		Quaternion operator- (const Quaternion& rkQ) const;
		Quaternion operator* (const Quaternion& rkQ) const;
		Quaternion operator* (float fScalar) const;
		Quaternion operator- () const;
		bool operator== (const Quaternion& rhs) const;
		bool operator!= (const Quaternion& rhs) const;

		float Dot(const Quaternion& rkQ) const;
		float Norm() const;
		float normalise(void);
		Quaternion Inverse() const;
		Quaternion UnitInverse() const;
		Quaternion Exp() const;
		Quaternion Log() const;

		Vector3 operator* (const Vector3& rkVector) const;
		float getRoll(bool reprojectAxis = true) const;
		float getPitch(bool reprojectAxis = true) const;
		float getYaw(bool reprojectAxis = true) const;
		bool equals(const Quaternion& rhs, const float& tolerance) const;
		static Quaternion Slerp(float fT, const Quaternion& rkP, const Quaternion& rkQ, bool shortestPath = false);
		static Quaternion SlerpExtraSpins(float fT, const Quaternion& rkP, const Quaternion& rkQ, int iExtraSpins);
		static void Intermediate(const Quaternion& rkQ0, const Quaternion& rkQ1, const Quaternion& rkQ2, Quaternion& rka, Quaternion& rkB);
		static Quaternion Squad(float fT, const Quaternion& rkP, const Quaternion& rkA, const Quaternion& rkB, const Quaternion& rkQ, bool shortestPath = false);
		static Quaternion nlerp(float fT, const Quaternion& rkP, const Quaternion& rkQ, bool shortestPath = false);
		static const float msEpsilon;
		static const Quaternion ZERO;
		static const Quaternion IDENTITY;
		bool isNaN() const;

		friend std::ostream& operator << (std::ostream& o, const Quaternion& q);
};


#endif