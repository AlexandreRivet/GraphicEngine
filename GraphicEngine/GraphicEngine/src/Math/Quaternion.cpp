#include "Math/Quaternion.h"

#include <cmath>

Quaternion::Quaternion() : w(1), x(0), y(0), z(0){}
Quaternion::Quaternion(float fW, float fX, float fY, float fZ) : w(fW), x(fX), y(fY), z(fZ){}
Quaternion::Quaternion(const Matrix3& rot){ this->FromRotationMatrix(rot); }
Quaternion::Quaternion(const float& rfAngle, const Vector3& rkAxis){ this->FromAngleAxis(rfAngle, rkAxis); }
Quaternion::Quaternion(const Vector3& xaxis, const Vector3& yaxis, const Vector3& zaxis){ this->FromAxes(xaxis, yaxis, zaxis); }
Quaternion::Quaternion(const Vector3* akAxis){ this->FromAxes(akAxis); }

void Quaternion::swap(Quaternion& other){
	std::swap(w, other.w);
	std::swap(x, other.x);
	std::swap(y, other.y);
	std::swap(z, other.z);
}
float Quaternion::operator [] (const size_t i) const{
	assert(i < 4);
	return *(&w + i);
}
float& Quaternion::operator [] (const size_t i){
	assert(i < 4);
	return *(&w + i);
}

void Quaternion::FromRotationMatrix(const Matrix3& kRot){
	float fTrace = kRot[0][0] + kRot[1][1] + kRot[2][2];
	float fRoot;

	if (fTrace > 0.0)
	{
		// |w| > 1/2, may as well choose w > 1/2
		fRoot = sqrt(fTrace + 1.0f);  // 2w
		w = 0.5f*fRoot;
		fRoot = 0.5f / fRoot;  // 1/(4w)
		x = (kRot[2][1] - kRot[1][2])*fRoot;
		y = (kRot[0][2] - kRot[2][0])*fRoot;
		z = (kRot[1][0] - kRot[0][1])*fRoot;
	}
	else
	{
		// |w| <= 1/2
		static size_t s_iNext[3] = { 1, 2, 0 };
		size_t i = 0;
		if (kRot[1][1] > kRot[0][0])
			i = 1;
		if (kRot[2][2] > kRot[i][i])
			i = 2;
		size_t j = s_iNext[i];
		size_t k = s_iNext[j];

		fRoot = sqrt(kRot[i][i] - kRot[j][j] - kRot[k][k] + 1.0f);
		float* apkQuat[3] = { &x, &y, &z };
		*apkQuat[i] = 0.5f*fRoot;
		fRoot = 0.5f / fRoot;
		w = (kRot[k][j] - kRot[j][k])*fRoot;
		*apkQuat[j] = (kRot[j][i] + kRot[i][j])*fRoot;
		*apkQuat[k] = (kRot[k][i] + kRot[i][k])*fRoot;
	}
}
void Quaternion::ToRotationMatrix(Matrix3& kRot) const{
	float fTx = x + x;
	float fTy = y + y;
	float fTz = z + z;
	float fTwx = fTx*w;
	float fTwy = fTy*w;
	float fTwz = fTz*w;
	float fTxx = fTx*x;
	float fTxy = fTy*x;
	float fTxz = fTz*x;
	float fTyy = fTy*y;
	float fTyz = fTz*y;
	float fTzz = fTz*z;

	kRot[0][0] = 1.0f - (fTyy + fTzz);
	kRot[0][1] = fTxy - fTwz;
	kRot[0][2] = fTxz + fTwy;
	kRot[1][0] = fTxy + fTwz;
	kRot[1][1] = 1.0f - (fTxx + fTzz);
	kRot[1][2] = fTyz - fTwx;
	kRot[2][0] = fTxz - fTwy;
	kRot[2][1] = fTyz + fTwx;
	kRot[2][2] = 1.0f - (fTxx + fTyy);
}
void Quaternion::FromAngleAxis(const float& rfAngle, const Vector3& rkAxis){
	float fHalfAngle(0.5*rfAngle);
	float fSin = sin(fHalfAngle);
	w = cos(fHalfAngle);
	x = fSin*rkAxis.x;
	y = fSin*rkAxis.y;
	z = fSin*rkAxis.z;
}
void Quaternion::ToAngleAxis(float& rfAngle, Vector3& rkAxis) const{
	float fSqrLength = x*x + y*y + z*z;
	if (fSqrLength > 0.0)
	{
		rfAngle = 2.0*acos(w);
		float fInvLength = 1/sqrt(fSqrLength);
		rkAxis.x = x*fInvLength;
		rkAxis.y = y*fInvLength;
		rkAxis.z = z*fInvLength;
	}
	else
	{
		// angle is 0 (mod 2*pi), so any axis will do
		rfAngle = 0.0;
		rkAxis.x = 1.0;
		rkAxis.y = 0.0;
		rkAxis.z = 0.0;
	}
}
void Quaternion::ToAngleAxis(float& dAngle, Vector3& rkAxis) const{
	float rAngle;
	ToAngleAxis(rAngle, rkAxis);
	dAngle = rAngle;
}
void Quaternion::FromAxes(const Vector3* akAxis){
	Matrix3 kRot;

	for (size_t iCol = 0; iCol < 3; iCol++)
	{
		kRot[0][iCol] = akAxis[iCol].x;
		kRot[1][iCol] = akAxis[iCol].y;
		kRot[2][iCol] = akAxis[iCol].z;
	}

	FromRotationMatrix(kRot);
}
void Quaternion::FromAxes(const Vector3& xaxis, const Vector3& yaxis, const Vector3& zaxis){
	Matrix3 kRot;

	kRot[0][0] = xaxis.x;
	kRot[1][0] = xaxis.y;
	kRot[2][0] = xaxis.z;

	kRot[0][1] = yaxis.x;
	kRot[1][1] = yaxis.y;
	kRot[2][1] = yaxis.z;

	kRot[0][2] = zaxis.x;
	kRot[1][2] = zaxis.y;
	kRot[2][2] = zaxis.z;

	FromRotationMatrix(kRot);
}
void Quaternion::ToAxes(Vector3* akAxis) const{
	Matrix3 kRot;

	ToRotationMatrix(kRot);

	for (size_t iCol = 0; iCol < 3; iCol++)
	{
		akAxis[iCol].x = kRot[0][iCol];
		akAxis[iCol].y = kRot[1][iCol];
		akAxis[iCol].z = kRot[2][iCol];
	}
}
void Quaternion::ToAxes(Vector3& xaxis, Vector3& yaxis, Vector3& zaxis) const{
	Matrix3 kRot;

	ToRotationMatrix(kRot);

	xaxis.x = kRot[0][0];
	xaxis.y = kRot[1][0];
	xaxis.z = kRot[2][0];

	yaxis.x = kRot[0][1];
	yaxis.y = kRot[1][1];
	yaxis.z = kRot[2][1];

	zaxis.x = kRot[0][2];
	zaxis.y = kRot[1][2];
	zaxis.z = kRot[2][2];
}

Vector3 Quaternion::xAxis(void) const{
	float fTy = 2.0f*y;
	float fTz = 2.0f*z;
	float fTwy = fTy*w;
	float fTwz = fTz*w;
	float fTxy = fTy*x;
	float fTxz = fTz*x;
	float fTyy = fTy*y;
	float fTzz = fTz*z;

	return Vector3(1.0f - (fTyy + fTzz), fTxy + fTwz, fTxz - fTwy);
}
Vector3 Quaternion::yAxis(void) const{
	float fTx = 2.0f*x;
	float fTy = 2.0f*y;
	float fTz = 2.0f*z;
	float fTwx = fTx*w;
	float fTwz = fTz*w;
	float fTxx = fTx*x;
	float fTxy = fTy*x;
	float fTyz = fTz*y;
	float fTzz = fTz*z;

	return Vector3(fTxy - fTwz, 1.0f - (fTxx + fTzz), fTyz + fTwx);
}
Vector3 Quaternion::zAxis(void) const{
	float fTx = 2.0f*x;
	float fTy = 2.0f*y;
	float fTz = 2.0f*z;
	float fTwx = fTx*w;
	float fTwy = fTy*w;
	float fTxx = fTx*x;
	float fTxz = fTz*x;
	float fTyy = fTy*y;
	float fTyz = fTz*y;

	return Vector3(fTxz + fTwy, fTyz - fTwx, 1.0f - (fTxx + fTyy));
}

Quaternion& Quaternion::operator= (const Quaternion& rkQ){
	w = rkQ.w;
	x = rkQ.x;
	y = rkQ.y;
	z = rkQ.z;
	return *this;
}
Quaternion Quaternion::operator+ (const Quaternion& rkQ) const{ return Quaternion(w + rkQ.w, x + rkQ.x, y + rkQ.y, z + rkQ.z); }
Quaternion Quaternion::operator- (const Quaternion& rkQ) const{ return Quaternion(w - rkQ.w, x - rkQ.x, y - rkQ.y, z - rkQ.z); }
Quaternion Quaternion::operator* (const Quaternion& rkQ) const{
	return Quaternion
		(
		w * rkQ.w - x * rkQ.x - y * rkQ.y - z * rkQ.z,
		w * rkQ.x + x * rkQ.w + y * rkQ.z - z * rkQ.y,
		w * rkQ.y + y * rkQ.w + z * rkQ.x - x * rkQ.z,
		w * rkQ.z + z * rkQ.w + x * rkQ.y - y * rkQ.x
		);
}
Quaternion Quaternion::operator* (float fScalar) const{ return Quaternion(fScalar*w, fScalar*x, fScalar*y, fScalar*z); }
Quaternion Quaternion:: operator- () const{ return Quaternion(-w, -x, -y, -z); }
bool Quaternion::operator== (const Quaternion& rhs) const{
	return (rhs.x == x) && (rhs.y == y) && (rhs.z == z) && (rhs.w == w);
}
bool Quaternion::operator!= (const Quaternion& rhs) const{ return !operator==(rhs); }

float Quaternion::Dot(const Quaternion& rkQ) const{ return w*rkQ.w + x*rkQ.x + y*rkQ.y + z*rkQ.z; }
float Quaternion::Norm() const{ return w*w + x*x + y*y + z*z; }
float Quaternion::normalise(void){
	float len = Norm();
	float factor = 1.0f / sqrt(len);
	*this = *this * factor;
	return len;
}
Quaternion Quaternion::Inverse() const{
	float fNorm = w*w + x*x + y*y + z*z;
	if (fNorm > 0.0)
	{
		float fInvNorm = 1.0f / fNorm;
		return Quaternion(w*fInvNorm, -x*fInvNorm, -y*fInvNorm, -z*fInvNorm);
	}
	else
	{
		// return an invalid result to flag the error
		return ZERO;
	}
}
Quaternion Quaternion::UnitInverse() const{ return Quaternion(w, -x, -y, -z); }
Quaternion Quaternion::Exp() const{
	float fAngle = sqrt(x*x + y*y + z*z);
	float fSin = sin(fAngle);

	Quaternion kResult;
	kResult.w = cos(fAngle);

	if (abs(fSin) >= msEpsilon)
	{
		float fCoeff = fSin / (fAngle);
		kResult.x = fCoeff*x;
		kResult.y = fCoeff*y;
		kResult.z = fCoeff*z;
	}
	else
	{
		kResult.x = x;
		kResult.y = y;
		kResult.z = z;
	}

	return kResult;
}
Quaternion Quaternion::Log() const{
	Quaternion kResult;
	kResult.w = 0.0;

	if (abs(w) < 1.0)
	{
		float fAngle = acos(w);
		float fSin = sin(fAngle);
		if (abs(fSin) >= msEpsilon)
		{
			float fCoeff = fAngle / fSin;
			kResult.x = fCoeff*x;
			kResult.y = fCoeff*y;
			kResult.z = fCoeff*z;
			return kResult;
		}
	}

	kResult.x = x;
	kResult.y = y;
	kResult.z = z;

	return kResult;
}

Vector3 Quaternion::operator* (const Vector3& rkVector) const{
	Vector3 uv, uuv;
	Vector3 qvec(x, y, z);
	uv = qvec.crossProduct(v);
	uuv = qvec.crossProduct(uv);
	uv *= (2.0f * w);
	uuv *= 2.0f;

	return v + uv + uuv;
}
float Quaternion::getRoll(bool reprojectAxis = true) const{
	if (reprojectAxis)
	{
		// roll = atan2(localx.y, localx.x)
		// pick parts of xAxis() implementation that we need
		//			float fTx  = 2.0*x;
		float fTy = 2.0f*y;
		float fTz = 2.0f*z;
		float fTwz = fTz*w;
		float fTxy = fTy*x;
		float fTyy = fTy*y;
		float fTzz = fTz*z;

		// Vector3(1.0-(fTyy+fTzz), fTxy+fTwz, fTxz-fTwy);

		return atan2(fTxy + fTwz, 1.0f - (fTyy + fTzz));

	}
	else
	{
		return atan2(2 * (x*y + w*z), w*w + x*x - y*y - z*z);
	}
}
float Quaternion::getPitch(bool reprojectAxis = true) const{
	if (reprojectAxis)
	{
		// pitch = atan2(localy.z, localy.y)
		// pick parts of yAxis() implementation that we need
		float fTx = 2.0f*x;
		//			float fTy  = 2.0f*y;
		float fTz = 2.0f*z;
		float fTwx = fTx*w;
		float fTxx = fTx*x;
		float fTyz = fTz*y;
		float fTzz = fTz*z;

		// Vector3(fTxy-fTwz, 1.0-(fTxx+fTzz), fTyz+fTwx);
		return atan2(fTyz + fTwx, 1.0f - (fTxx + fTzz));
	}
	else
	{
		// internal version
		return atan2(2 * (y*z + w*x), w*w - x*x - y*y + z*z);
	}
}
float Quaternion::getYaw(bool reprojectAxis = true) const{
	if (reprojectAxis)
	{
		// yaw = atan2(localz.x, localz.z)
		// pick parts of zAxis() implementation that we need
		float fTx = 2.0f*x;
		float fTy = 2.0f*y;
		float fTz = 2.0f*z;
		float fTwy = fTy*w;
		float fTxx = fTx*x;
		float fTxz = fTz*x;
		float fTyy = fTy*y;

		// Vector3(fTxz+fTwy, fTyz-fTwx, 1.0-(fTxx+fTyy));

		return atan2(fTxz + fTwy, 1.0f - (fTxx + fTyy));

	}
	else
	{
		// internal version
		return asin(-2 * (x*z - w*y));
	}
}
bool Quaternion::equals(const Quaternion& rhs, const float& tolerance) const{
	float fCos = Dot(rhs);
	float angle = acos(fCos);

	return (abs(angle) <= tolerance)
		|| ((angle - M_PI) < tolerance);
}
static Quaternion Slerp(float fT, const Quaternion& rkP, const Quaternion& rkQ, bool shortestPath = false){
	float fCos = rkP.Dot(rkQ);
	Quaternion rkT;

	// Do we need to invert rotation?
	if (fCos < 0.0f && shortestPath)
	{
		fCos = -fCos;
		rkT = -rkQ;
	}
	else
	{
		rkT = rkQ;
	}

	if (abs(fCos) < 1 - msEpsilon)
	{
		// Standard case (slerp)
		float fSin = sqrt(1 - pow(fCos, 2));
		float fAngle = atan2(fSin, fCos);
		float fInvSin = 1.0f / fSin;
		float fCoeff0 = sin((1.0f - fT) * fAngle) * fInvSin;
		float fCoeff1 = sin(fT * fAngle) * fInvSin;
		return fCoeff0 * rkP + fCoeff1 * rkT;
	}
	else
	{
		// There are two situations:
		// 1. "rkP" and "rkQ" are very close (fCos ~= +1), so we can do a linear
		//    interpolation safely.
		// 2. "rkP" and "rkQ" are almost inverse of each other (fCos ~= -1), there
		//    are an infinite number of possibilities interpolation. but we haven't
		//    have method to fix this case, so just use linear interpolation here.
		Quaternion t = (1.0f - fT) * rkP + fT * rkT;
		// taking the complement requires renormalisation
		t.normalise();
		return t;
	}
}
static Quaternion SlerpExtraSpins(float fT, const Quaternion& rkP, const Quaternion& rkQ, int iExtraSpins){
	float fCos = rkP.Dot(rkQ);
	float fAngle = acos(fCos);

	if (abs(fAngle) < msEpsilon)
		return rkP;

	float fSin = sin(fAngle);
	float fPhase = M_PI*iExtraSpins*fT;
	float fInvSin = 1.0f / fSin;
	float fCoeff0 = sin((1.0f - fT)*fAngle - fPhase)*fInvSin;
	float fCoeff1 = sin(fT*fAngle + fPhase)*fInvSin;
	return fCoeff0*rkP + fCoeff1*rkQ;
}
static void Intermediate(const Quaternion& rkQ0, const Quaternion& rkQ1, const Quaternion& rkQ2, Quaternion& rka, Quaternion& rkB){
	Quaternion kQ0inv = rkQ0.UnitInverse();
	Quaternion kQ1inv = rkQ1.UnitInverse();
	Quaternion rkP0 = kQ0inv*rkQ1;
	Quaternion rkP1 = kQ1inv*rkQ2;
	Quaternion kArg = 0.25*(rkP0.Log() - rkP1.Log());
	Quaternion kMinusArg = -kArg;

	rka = rkQ1*kArg.Exp();
	rkB = rkQ1*kMinusArg.Exp();
}
static Quaternion Squad(float fT, const Quaternion& rkP, const Quaternion& rkA, const Quaternion& rkB, const Quaternion& rkQ, bool shortestPath = false){
	float fSlerpT = 2.0f*fT*(1.0f - fT);
	Quaternion kSlerpP = Slerp(fT, rkP, rkQ, shortestPath);
	Quaternion kSlerpQ = Slerp(fT, rkA, rkB);
	return Slerp(fSlerpT, kSlerpP, kSlerpQ);
}
static Quaternion nlerp(float fT, const Quaternion& rkP, const Quaternion& rkQ, bool shortestPath = false){
	Quaternion result;
	float fCos = rkP.Dot(rkQ);
	if (fCos < 0.0f && shortestPath)
	{
		result = rkP + fT * ((-rkQ) - rkP);
	}
	else
	{
		result = rkP + fT * (rkQ - rkP);
	}
	result.normalise();
	return result;
}
static const float msEpsilon;
static const Quaternion ZERO;
static const Quaternion IDENTITY;

std::ostream& operator << (std::ostream& o, const Quaternion& q){
	o << "Quaternion(" << q.w << ", " << q.x << ", " << q.y << ", " << q.z << ")";
	return o;
}