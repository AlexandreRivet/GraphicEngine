#ifndef _MATRIX3_H_
#define _MATRIX3_H_

#include "prerequisites.h"
#include "Math/Math.h"

#include "Math/Vector3.h"

class Matrix3
{
	public:
		inline Matrix3() {}
		inline explicit Matrix3(const float arr[3][3])
		{
			memcpy(m, arr, 9 * sizeof(float));
		}
		inline Matrix3(const Matrix3& rkMatrix)
		{
			memcpy(m, rkMatrix.m, 9 * sizeof(float));
		}
		Matrix3(float fEntry00, float fEntry01, float fEntry02,
			float fEntry10, float fEntry11, float fEntry12,
			float fEntry20, float fEntry21, float fEntry22)
		{
			m[0][0] = fEntry00;
			m[0][1] = fEntry01;
			m[0][2] = fEntry02;
			m[1][0] = fEntry10;
			m[1][1] = fEntry11;
			m[1][2] = fEntry12;
			m[2][0] = fEntry20;
			m[2][1] = fEntry21;
			m[2][2] = fEntry22;
		}

		inline void swap(Matrix3& other)
		{
			std::swap(m[0][0], other.m[0][0]);
			std::swap(m[0][1], other.m[0][1]);
			std::swap(m[0][2], other.m[0][2]);
			std::swap(m[1][0], other.m[1][0]);
			std::swap(m[1][1], other.m[1][1]);
			std::swap(m[1][2], other.m[1][2]);
			std::swap(m[2][0], other.m[2][0]);
			std::swap(m[2][1], other.m[2][1]);
			std::swap(m[2][2], other.m[2][2]);
		}

		inline float* operator[] (size_t iRow) const
		{
			return (float*)m[iRow];
		}

		Vector3 GetColumn(size_t iCol) const;
		void SetColumn(size_t iCol, const Vector3& vec);
		void FromAxes(const Vector3& xAxis, const Vector3& yAxis, const Vector3& zAxis);

		inline Matrix3& operator= (const Matrix3& rkMatrix)
		{
			memcpy(m, rkMatrix.m, 9 * sizeof(float));
			return *this;
		}

		bool operator== (const Matrix3& rkMatrix) const;

		inline bool operator!= (const Matrix3& rkMatrix) const
		{
			return !operator==(rkMatrix);
		}

		Matrix3 operator+ (const Matrix3& rkMatrix) const;

		Matrix3 operator- (const Matrix3& rkMatrix) const;

		Matrix3 operator* (const Matrix3& rkMatrix) const;
		Matrix3 operator- () const;

		Vector3 operator* (const Vector3& rkVector) const;

		friend Vector3 operator* (const Vector3& rkVector,
			const Matrix3& rkMatrix);

		Matrix3 operator* (float fScalar) const;

		friend Matrix3 operator* (float fScalar, const Matrix3& rkMatrix);

		Matrix3 Transpose() const;
		bool Inverse(Matrix3& rkInverse, float fTolerance = 1e-06) const;
		Matrix3 Inverse(float fTolerance = 1e-06) const;
		float Determinant() const;

		void SingularValueDecomposition(Matrix3& rkL, Vector3& rkS,
			Matrix3& rkR) const;
		void SingularValueComposition(const Matrix3& rkL,
			const Vector3& rkS, const Matrix3& rkR);

		void Orthonormalize();

		void QDUDecomposition(Matrix3& rkQ, Vector3& rkD,
			Vector3& rkU) const;

		float SpectralNorm() const;

		void ToAngleAxis(Vector3& rkAxis, float& rfAngle) const;

		void FromAngleAxis(const Vector3& rkAxis, const float& fRadians);

		// The matrix must be orthonormal.  The decomposition is yaw*pitch*roll
		// where yaw is rotation about the Up vector, pitch is rotation about the
		// Right axis, and roll is rotation about the Direction axis.
		bool ToEulerAnglesXYZ(float& rfYAngle, float& rfPAngle,
			float& rfRAngle) const;
		bool ToEulerAnglesXZY(float& rfYAngle, float& rfPAngle,
			float& rfRAngle) const;
		bool ToEulerAnglesYXZ(float& rfYAngle, float& rfPAngle,
			float& rfRAngle) const;
		bool ToEulerAnglesYZX(float& rfYAngle, float& rfPAngle,
			float& rfRAngle) const;
		bool ToEulerAnglesZXY(float& rfYAngle, float& rfPAngle,
			float& rfRAngle) const;
		bool ToEulerAnglesZYX(float& rfYAngle, float& rfPAngle,
			float& rfRAngle) const;
		void FromEulerAnglesXYZ(const float& fYAngle, const float& fPAngle, const float& fRAngle);
		void FromEulerAnglesXZY(const float& fYAngle, const float& fPAngle, const float& fRAngle);
		void FromEulerAnglesYXZ(const float& fYAngle, const float& fPAngle, const float& fRAngle);
		void FromEulerAnglesYZX(const float& fYAngle, const float& fPAngle, const float& fRAngle);
		void FromEulerAnglesZXY(const float& fYAngle, const float& fPAngle, const float& fRAngle);
		void FromEulerAnglesZYX(const float& fYAngle, const float& fPAngle, const float& fRAngle);
		/// Eigensolver, matrix must be symmetric
		void EigenSolveSymmetric(float afEigenvalue[3],
			Vector3 akEigenvector[3]) const;

		static void TensorProduct(const Vector3& rkU, const Vector3& rkV,
			Matrix3& rkProduct);

		/** Determines if this matrix involves a scaling. */
		inline bool hasScale() const
		{
			// check magnitude of column vectors (==local axes)
			float t = m[0][0] * m[0][0] + m[1][0] * m[1][0] + m[2][0] * m[2][0];
			if (!Math::floatEqual(t, 1.0, (float)1e-04))
				return true;
			t = m[0][1] * m[0][1] + m[1][1] * m[1][1] + m[2][1] * m[2][1];
			if (!Math::floatEqual(t, 1.0, (float)1e-04))
				return true;
			t = m[0][2] * m[0][2] + m[1][2] * m[1][2] + m[2][2] * m[2][2];
			if (!Math::floatEqual(t, 1.0, (float)1e-04))
				return true;

			return false;
		}

		/** Function for writing to a stream.
		*/
		inline _OgreExport friend std::ostream& operator <<
			(std::ostream& o, const Matrix3& mat)
		{
			o << "Matrix3(" << mat[0][0] << ", " << mat[0][1] << ", " << mat[0][2] << ", "
				<< mat[1][0] << ", " << mat[1][1] << ", " << mat[1][2] << ", "
				<< mat[2][0] << ", " << mat[2][1] << ", " << mat[2][2] << ")";
			return o;
		}

		static const float EPSILON;
		static const Matrix3 ZERO;
		static const Matrix3 IDENTITY;

	protected:
		// support for eigensolver
		void Tridiagonal(float afDiag[3], float afSubDiag[3]);
		bool QLAlgorithm(float afDiag[3], float afSubDiag[3]);

		// support for singular value decomposition
		static const float msSvdEpsilon;
		static const unsigned int msSvdMaxIterations;
		static void Bidiagonalize(Matrix3& kA, Matrix3& kL,
			Matrix3& kR);
		static void GolubKahanStep(Matrix3& kA, Matrix3& kL,
			Matrix3& kR);

		// support for spectral norm
		static float MaxCubicRoot(float afCoeff[3]);

		float m[3][3];

		// for faster access
		friend class Matrix4;
	};
	/** @} */
	/** @} */
}

#endif
