#ifndef _VECTOR3_H_
#define _VECTOR3_H_

#include "../prerequisites.h"

class Vector3
{
	public:

		Real x, y, z;

	public:

		inline Vector3()
		{
		}

		inline Vector3(const Real fX, const Real fY, const Real fZ)
			: x(fX), y(fY), z(fZ)
		{
		}

		inline explicit Vector3(const Real afCoordinate[3])
			: x(afCoordinate[0]),
			y(afCoordinate[1]),
			z(afCoordinate[2])
		{
		}

		inline explicit Vector3(const int afCoordinate[3])
		{
			x = (Real)afCoordinate[0];
			y = (Real)afCoordinate[1];
			z = (Real)afCoordinate[2];
		}

		inline explicit Vector3(Real* const r)
			: x(r[0]), y(r[1]), z(r[2])
		{
		}

		inline explicit Vector3(const Real scaler)
			: x(scaler)
			, y(scaler)
			, z(scaler)
		{
		}

		inline void swap(Vector3& other)
		{
			std::swap(x, other.x);
			std::swap(y, other.y);
			std::swap(z, other.z);
		}

		inline Real operator [] (const size_t i) const
		{
			assert(i < 3);

			return *(&x + i);
		}

		inline Real& operator [] (const size_t i)
		{
			assert(i < 3);

			return *(&x + i);
		}
		
		inline Real* ptr()
		{
			return &x;
		}
		
		inline const Real* ptr() const
		{
			return &x;
		}

		inline Vector3& operator = (const Vector3& rkVector)
		{
			x = rkVector.x;
			y = rkVector.y;
			z = rkVector.z;

			return *this;
		}

		inline Vector3& operator = (const Real fScaler)
		{
			x = fScaler;
			y = fScaler;
			z = fScaler;

			return *this;
		}

		inline bool operator == (const Vector3& rkVector) const
		{
			return (x == rkVector.x && y == rkVector.y && z == rkVector.z);
		}

		inline bool operator != (const Vector3& rkVector) const
		{
			return (x != rkVector.x || y != rkVector.y || z != rkVector.z);
		}

		inline Vector3 operator + (const Vector3& rkVector) const
		{
			return Vector3(
				x + rkVector.x,
				y + rkVector.y,
				z + rkVector.z);
		}

		inline Vector3 operator - (const Vector3& rkVector) const
		{
			return Vector3(
				x - rkVector.x,
				y - rkVector.y,
				z - rkVector.z);
		}

		inline Vector3 operator * (const Real fScalar) const
		{
			return Vector3(
				x * fScalar,
				y * fScalar,
				z * fScalar);
		}

		inline Vector3 operator * (const Vector3& rhs) const
		{
			return Vector3(
				x * rhs.x,
				y * rhs.y,
				z * rhs.z);
		}

		inline Vector3 operator / (const Real fScalar) const
		{
			assert(fScalar != 0.0);

			Real fInv = 1.0f / fScalar;

			return Vector3(
				x * fInv,
				y * fInv,
				z * fInv);
		}

		inline Vector3 operator / (const Vector3& rhs) const
		{
			return Vector3(
				x / rhs.x,
				y / rhs.y,
				z / rhs.z);
		}

		inline const Vector3& operator + () const
		{
			return *this;
		}

		inline Vector3 operator - () const
		{
			return Vector3(-x, -y, -z);
		}

		inline friend Vector3 operator * (const Real fScalar, const Vector3& rkVector)
		{
			return Vector3(
				fScalar * rkVector.x,
				fScalar * rkVector.y,
				fScalar * rkVector.z);
		}

		inline friend Vector3 operator / (const Real fScalar, const Vector3& rkVector)
		{
			return Vector3(
				fScalar / rkVector.x,
				fScalar / rkVector.y,
				fScalar / rkVector.z);
		}

		inline friend Vector3 operator + (const Vector3& lhs, const Real rhs)
		{
			return Vector3(
				lhs.x + rhs,
				lhs.y + rhs,
				lhs.z + rhs);
		}

		inline friend Vector3 operator + (const Real lhs, const Vector3& rhs)
		{
			return Vector3(
				lhs + rhs.x,
				lhs + rhs.y,
				lhs + rhs.z);
		}

		inline friend Vector3 operator - (const Vector3& lhs, const Real rhs)
		{
			return Vector3(
				lhs.x - rhs,
				lhs.y - rhs,
				lhs.z - rhs);
		}

		inline friend Vector3 operator - (const Real lhs, const Vector3& rhs)
		{
			return Vector3(
				lhs - rhs.x,
				lhs - rhs.y,
				lhs - rhs.z);
		}

		inline Vector3& operator += (const Vector3& rkVector)
		{
			x += rkVector.x;
			y += rkVector.y;
			z += rkVector.z;

			return *this;
		}

		inline Vector3& operator += (const Real fScalar)
		{
			x += fScalar;
			y += fScalar;
			z += fScalar;
			return *this;
		}

		inline Vector3& operator -= (const Vector3& rkVector)
		{
			x -= rkVector.x;
			y -= rkVector.y;
			z -= rkVector.z;

			return *this;
		}

		inline Vector3& operator -= (const Real fScalar)
		{
			x -= fScalar;
			y -= fScalar;
			z -= fScalar;
			return *this;
		}

		inline Vector3& operator *= (const Real fScalar)
		{
			x *= fScalar;
			y *= fScalar;
			z *= fScalar;
			return *this;
		}

		inline Vector3& operator *= (const Vector3& rkVector)
		{
			x *= rkVector.x;
			y *= rkVector.y;
			z *= rkVector.z;

			return *this;
		}

		inline Vector3& operator /= (const Real fScalar)
		{
			assert(fScalar != 0.0);

			Real fInv = 1.0f / fScalar;

			x *= fInv;
			y *= fInv;
			z *= fInv;

			return *this;
		}

		inline Vector3& operator /= (const Vector3& rkVector)
		{
			x /= rkVector.x;
			y /= rkVector.y;
			z /= rkVector.z;

			return *this;
		}

		inline Real length() const
		{
			return sqrt(x * x + y * y + z * z);
		}


		inline Real squaredLength() const
		{
			return x * x + y * y + z * z;
		}

		inline Real distance(const Vector3& rhs) const
		{
			return (*this - rhs).length();
		}

		inline Real squaredDistance(const Vector3& rhs) const
		{
			return (*this - rhs).squaredLength();
		}

		inline Real dotProduct(const Vector3& vec) const
		{
			return x * vec.x + y * vec.y + z * vec.z;
		}

		inline Real absDotProduct(const Vector3& vec) const
		{
			return abs(x * vec.x) + abs(y * vec.y) + abs(z * vec.z);
		}

		inline Real normalise()
		{
			Real fLength = sqrt(x * x + y * y + z * z);

			if (fLength > Real(0.0f))
			{
				Real fInvLength = 1.0f / fLength;
				x *= fInvLength;
				y *= fInvLength;
				z *= fInvLength;
			}

			return fLength;
		}

		inline Vector3 crossProduct(const Vector3& rkVector) const
		{
			return Vector3(
				y * rkVector.z - z * rkVector.y,
				z * rkVector.x - x * rkVector.z,
				x * rkVector.y - y * rkVector.x);
		}

		inline Vector3 midPoint(const Vector3& vec) const
		{
			return Vector3(
				(x + vec.x) * 0.5f,
				(y + vec.y) * 0.5f,
				(z + vec.z) * 0.5f);
		}

		inline bool operator < (const Vector3& rhs) const
		{
			if (x < rhs.x && y < rhs.y && z < rhs.z)
				return true;
			return false;
		}

		inline bool operator >(const Vector3& rhs) const
		{
			if (x > rhs.x && y > rhs.y && z > rhs.z)
				return true;
			return false;
		}

		inline void makeFloor(const Vector3& cmp)
		{
			if (cmp.x < x) x = cmp.x;
			if (cmp.y < y) y = cmp.y;
			if (cmp.z < z) z = cmp.z;
		}

			inline void makeCeil(const Vector3& cmp)
		{
			if (cmp.x > x) x = cmp.x;
			if (cmp.y > y) y = cmp.y;
			if (cmp.z > z) z = cmp.z;
		}

		inline Vector3 perpendicular(void) const
		{
			static const Real fSquareZero = (Real)(1e-06 * 1e-06);

			Vector3 perp = this->crossProduct(Vector3::UNIT_X);

			// Check length
			if (perp.squaredLength() < fSquareZero)
			{
				/* This vector is the Y axis multiplied by a scalar, so we have
				to use another axis.
				*/
				perp = this->crossProduct(Vector3::UNIT_Y);
			}
			perp.normalise();

			return perp;
		}
		

		/** Returns true if this vector is zero length. */
		inline bool isZeroLength(void) const
		{
			Real sqlen = (x * x) + (y * y) + (z * z);
			return (sqlen < (1e-06 * 1e-06));

		}

		/** As normalise, except that this vector is unaffected and the
		normalised vector is returned as a copy. */
		inline Vector3 normalisedCopy(void) const
		{
			Vector3 ret = *this;
			ret.normalise();
			return ret;
		}

		/** Calculates a reflection vector to the plane with the given normal .
		@remarks NB assumes 'this' is pointing AWAY FROM the plane, invert if it is not.
		*/
		inline Vector3 reflect(const Vector3& normal) const
		{
			return Vector3(*this - (2 * this->dotProduct(normal) * normal));
		}

		/** Returns whether this vector is within a positional tolerance
		of another vector.
		@param rhs The vector to compare with
		@param tolerance The amount that each element of the vector may vary by
		and still be considered equal
		*/
		inline bool positionEquals(const Vector3& rhs, Real tolerance = 1e-03) const
		{
			return
				(rhs.x - x) <= tolerance &&
				(rhs.y - y) <= tolerance &&
				(rhs.z - z) <= tolerance;
		}

		/** Returns whether this vector is within a positional tolerance
		of another vector, also take scale of the vectors into account.
		@param rhs The vector to compare with
		@param tolerance The amount (related to the scale of vectors) that distance
		of the vector may vary by and still be considered close
		*/
		inline bool positionCloses(const Vector3& rhs, Real tolerance = 1e-03f) const
		{
			return squaredDistance(rhs) <=
				(squaredLength() + rhs.squaredLength()) * tolerance;
		}

		/// Extract the primary (dominant) axis from this direction vector
		inline Vector3 primaryAxis() const
		{
			Real absx = abs(x);
			Real absy = abs(y);
			Real absz = abs(z);
			if (absx > absy)
			if (absx > absz)
				return x > 0 ? Vector3::UNIT_X : Vector3::NEGATIVE_UNIT_X;
			else
				return z > 0 ? Vector3::UNIT_Z : Vector3::NEGATIVE_UNIT_Z;
			else // absx <= absy
			if (absy > absz)
				return y > 0 ? Vector3::UNIT_Y : Vector3::NEGATIVE_UNIT_Y;
			else
				return z > 0 ? Vector3::UNIT_Z : Vector3::NEGATIVE_UNIT_Z;


		}

		// special points
		static const Vector3 ZERO;
		static const Vector3 UNIT_X;
		static const Vector3 UNIT_Y;
		static const Vector3 UNIT_Z;
		static const Vector3 NEGATIVE_UNIT_X;
		static const Vector3 NEGATIVE_UNIT_Y;
		static const Vector3 NEGATIVE_UNIT_Z;
		static const Vector3 UNIT_SCALE;


};


#endif