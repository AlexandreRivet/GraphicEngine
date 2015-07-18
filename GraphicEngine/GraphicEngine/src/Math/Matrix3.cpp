#include "Math/Matrix3.h"
#include "Math/Math.h"

const float Matrix3::EPSILON = 1e-06f;
const Matrix3 Matrix3::ZERO(0, 0, 0, 0, 0, 0, 0, 0, 0);
const Matrix3 Matrix3::IDENTITY(1, 0, 0, 0, 1, 0, 0, 0, 1);
const float Matrix3::msSvdEpsilon = 1e-04f;
const unsigned int Matrix3::msSvdMaxIterations = 32;

Vector3 Matrix3::GetColumn(size_t iCol) const
{
	assert(iCol < 3);
	return Vector3(m[0][iCol], m[1][iCol],
		m[2][iCol]);
}

void Matrix3::SetColumn(size_t iCol, const Vector3& vec)
{
	assert(iCol < 3);
	m[0][iCol] = vec.x;
	m[1][iCol] = vec.y;
	m[2][iCol] = vec.z;
}

void Matrix3::FromAxes(const Vector3& xAxis, const Vector3& yAxis, const Vector3& zAxis)
{
	SetColumn(0, xAxis);
	SetColumn(1, yAxis);
	SetColumn(2, zAxis);
}

bool Matrix3::operator== (const Matrix3& rkMatrix) const
{
	for (size_t iRow = 0; iRow < 3; iRow++)
	{
		for (size_t iCol = 0; iCol < 3; iCol++)
		{
			if (m[iRow][iCol] != rkMatrix.m[iRow][iCol])
				return false;
		}
	}
	return true;
}

Matrix3 Matrix3::operator+ (const Matrix3& rkMatrix) const
{
	Matrix3 kSum;
	for (size_t iRow = 0; iRow < 3; iRow++)
	{
		for (size_t iCol = 0; iCol < 3; iCol++)
		{
			kSum.m[iRow][iCol] = m[iRow][iCol] +
				rkMatrix.m[iRow][iCol];
		}
	}
	return kSum;
}

Matrix3 Matrix3::operator- (const Matrix3& rkMatrix) const
{
	Matrix3 kDiff;
	for (size_t iRow = 0; iRow < 3; iRow++)
	{
		for (size_t iCol = 0; iCol < 3; iCol++)
		{
			kDiff.m[iRow][iCol] = m[iRow][iCol] -
				rkMatrix.m[iRow][iCol];
		}
	}
	return kDiff;
}

Matrix3 Matrix3::operator* (const Matrix3& rkMatrix) const
{
	Matrix3 kProd;
	for (size_t iRow = 0; iRow < 3; iRow++)
	{
		for (size_t iCol = 0; iCol < 3; iCol++)
		{
			kProd.m[iRow][iCol] =
				m[iRow][0] * rkMatrix.m[0][iCol] +
				m[iRow][1] * rkMatrix.m[1][iCol] +
				m[iRow][2] * rkMatrix.m[2][iCol];
		}
	}
	return kProd;
}

Vector3 Matrix3::operator* (const Vector3& rkPoint) const
{
	Vector3 kProd;
	for (size_t iRow = 0; iRow < 3; iRow++)
	{
		kProd[iRow] =
			m[iRow][0] * rkPoint[0] +
			m[iRow][1] * rkPoint[1] +
			m[iRow][2] * rkPoint[2];
	}
	return kProd;
}

Vector3 operator* (const Vector3& rkPoint, const Matrix3& rkMatrix)
{
	Vector3 kProd;
	for (size_t iRow = 0; iRow < 3; iRow++)
	{
		kProd[iRow] =
			rkPoint[0] * rkMatrix.m[0][iRow] +
			rkPoint[1] * rkMatrix.m[1][iRow] +
			rkPoint[2] * rkMatrix.m[2][iRow];
	}
	return kProd;
}

Matrix3 Matrix3::operator- () const
{
	Matrix3 kNeg;
	for (size_t iRow = 0; iRow < 3; iRow++)
	{
		for (size_t iCol = 0; iCol < 3; iCol++)
			kNeg[iRow][iCol] = -m[iRow][iCol];
	}
	return kNeg;
}

Matrix3 Matrix3::operator* (float fScalar) const
{
	Matrix3 kProd;
	for (size_t iRow = 0; iRow < 3; iRow++)
	{
		for (size_t iCol = 0; iCol < 3; iCol++)
			kProd[iRow][iCol] = fScalar*m[iRow][iCol];
	}
	return kProd;
}

Matrix3 operator* (float fScalar, const Matrix3& rkMatrix)
{
	Matrix3 kProd;
	for (size_t iRow = 0; iRow < 3; iRow++)
	{
		for (size_t iCol = 0; iCol < 3; iCol++)
			kProd[iRow][iCol] = fScalar*rkMatrix.m[iRow][iCol];
	}
	return kProd;
}

Matrix3 Matrix3::Transpose() const
{
	Matrix3 kTranspose;
	for (size_t iRow = 0; iRow < 3; iRow++)
	{
		for (size_t iCol = 0; iCol < 3; iCol++)
			kTranspose[iRow][iCol] = m[iCol][iRow];
	}
	return kTranspose;
}

bool Matrix3::Inverse(Matrix3& rkInverse, float fTolerance) const
{
	rkInverse[0][0] = m[1][1] * m[2][2] -
		m[1][2] * m[2][1];
	rkInverse[0][1] = m[0][2] * m[2][1] -
		m[0][1] * m[2][2];
	rkInverse[0][2] = m[0][1] * m[1][2] -
		m[0][2] * m[1][1];
	rkInverse[1][0] = m[1][2] * m[2][0] -
		m[1][0] * m[2][2];
	rkInverse[1][1] = m[0][0] * m[2][2] -
		m[0][2] * m[2][0];
	rkInverse[1][2] = m[0][2] * m[1][0] -
		m[0][0] * m[1][2];
	rkInverse[2][0] = m[1][0] * m[2][1] -
		m[1][1] * m[2][0];
	rkInverse[2][1] = m[0][1] * m[2][0] -
		m[0][0] * m[2][1];
	rkInverse[2][2] = m[0][0] * m[1][1] -
		m[0][1] * m[1][0];

	float fDet =
		m[0][0] * rkInverse[0][0] +
		m[0][1] * rkInverse[1][0] +
		m[0][2] * rkInverse[2][0];

	if (fabs(fDet) <= fTolerance)
		return false;

	float fInvDet = 1.0f / fDet;
	for (size_t iRow = 0; iRow < 3; iRow++)
	{
		for (size_t iCol = 0; iCol < 3; iCol++)
			rkInverse[iRow][iCol] *= fInvDet;
	}

	return true;
}

Matrix3 Matrix3::Inverse(float fTolerance) const
{
	Matrix3 kInverse = Matrix3::ZERO;
	Inverse(kInverse, fTolerance);
	return kInverse;
}

float Matrix3::Determinant() const
{
	float fCofactor00 = m[1][1] * m[2][2] -
		m[1][2] * m[2][1];
	float fCofactor10 = m[1][2] * m[2][0] -
		m[1][0] * m[2][2];
	float fCofactor20 = m[1][0] * m[2][1] -
		m[1][1] * m[2][0];

	float fDet =
		m[0][0] * fCofactor00 +
		m[0][1] * fCofactor10 +
		m[0][2] * fCofactor20;

	return fDet;
}

void Matrix3::Bidiagonalize(Matrix3& kA, Matrix3& kL,
	Matrix3& kR)
{
	float afV[3], afW[3];
	float fLength, fSign, fT1, fInvT1, fT2;
	bool bIdentity;

	fLength = sqrt(kA[0][0] * kA[0][0] + kA[1][0] * kA[1][0] +
		kA[2][0] * kA[2][0]);
	if (fLength > 0.0)
	{
		fSign = (kA[0][0] > 0.0f ? 1.0f : -1.0f);
		fT1 = kA[0][0] + fSign*fLength;
		fInvT1 = 1.0f / fT1;
		afV[1] = kA[1][0] * fInvT1;
		afV[2] = kA[2][0] * fInvT1;

		fT2 = -2.0f / (1.0f + afV[1] * afV[1] + afV[2] * afV[2]);
		afW[0] = fT2*(kA[0][0] + kA[1][0] * afV[1] + kA[2][0] * afV[2]);
		afW[1] = fT2*(kA[0][1] + kA[1][1] * afV[1] + kA[2][1] * afV[2]);
		afW[2] = fT2*(kA[0][2] + kA[1][2] * afV[1] + kA[2][2] * afV[2]);
		kA[0][0] += afW[0];
		kA[0][1] += afW[1];
		kA[0][2] += afW[2];
		kA[1][1] += afV[1] * afW[1];
		kA[1][2] += afV[1] * afW[2];
		kA[2][1] += afV[2] * afW[1];
		kA[2][2] += afV[2] * afW[2];

		kL[0][0] = 1.0f + fT2;
		kL[0][1] = kL[1][0] = fT2*afV[1];
		kL[0][2] = kL[2][0] = fT2*afV[2];
		kL[1][1] = 1.0f + fT2*afV[1] * afV[1];
		kL[1][2] = kL[2][1] = fT2*afV[1] * afV[2];
		kL[2][2] = 1.0f + fT2*afV[2] * afV[2];
		bIdentity = false;
	}
	else
	{
		kL = Matrix3::IDENTITY;
		bIdentity = true;
	}

	fLength = sqrt(kA[0][1] * kA[0][1] + kA[0][2] * kA[0][2]);
	if (fLength > 0.0)
	{
		fSign = (kA[0][1] > 0.0f ? 1.0f : -1.0f);
		fT1 = kA[0][1] + fSign*fLength;
		afV[2] = kA[0][2] / fT1;

		fT2 = -2.0f / (1.0f + afV[2] * afV[2]);
		afW[0] = fT2*(kA[0][1] + kA[0][2] * afV[2]);
		afW[1] = fT2*(kA[1][1] + kA[1][2] * afV[2]);
		afW[2] = fT2*(kA[2][1] + kA[2][2] * afV[2]);
		kA[0][1] += afW[0];
		kA[1][1] += afW[1];
		kA[1][2] += afW[1] * afV[2];
		kA[2][1] += afW[2];
		kA[2][2] += afW[2] * afV[2];

		kR[0][0] = 1.0;
		kR[0][1] = kR[1][0] = 0.0;
		kR[0][2] = kR[2][0] = 0.0;
		kR[1][1] = 1.0f + fT2;
		kR[1][2] = kR[2][1] = fT2*afV[2];
		kR[2][2] = 1.0f + fT2*afV[2] * afV[2];
	}
	else
	{
		kR = Matrix3::IDENTITY;
	}


	fLength = sqrt(kA[1][1] * kA[1][1] + kA[2][1] * kA[2][1]);
	if (fLength > 0.0)
	{
		fSign = (kA[1][1] > 0.0f ? 1.0f : -1.0f);
		fT1 = kA[1][1] + fSign*fLength;
		afV[2] = kA[2][1] / fT1;

		fT2 = -2.0f / (1.0f + afV[2] * afV[2]);
		afW[1] = fT2*(kA[1][1] + kA[2][1] * afV[2]);
		afW[2] = fT2*(kA[1][2] + kA[2][2] * afV[2]);
		kA[1][1] += afW[1];
		kA[1][2] += afW[2];
		kA[2][2] += afV[2] * afW[2];

		float fA = 1.0f + fT2;
		float fB = fT2*afV[2];
		float fC = 1.0f + fB*afV[2];

		if (bIdentity)
		{
			kL[0][0] = 1.0;
			kL[0][1] = kL[1][0] = 0.0;
			kL[0][2] = kL[2][0] = 0.0;
			kL[1][1] = fA;
			kL[1][2] = kL[2][1] = fB;
			kL[2][2] = fC;
		}
		else
		{
			for (int iRow = 0; iRow < 3; iRow++)
			{
				float fTmp0 = kL[iRow][1];
				float fTmp1 = kL[iRow][2];
				kL[iRow][1] = fA*fTmp0 + fB*fTmp1;
				kL[iRow][2] = fB*fTmp0 + fC*fTmp1;
			}
		}
	}
}

void Matrix3::GolubKahanStep(Matrix3& kA, Matrix3& kL,
	Matrix3& kR)
{
	float fT11 = kA[0][1] * kA[0][1] + kA[1][1] * kA[1][1];
	float fT22 = kA[1][2] * kA[1][2] + kA[2][2] * kA[2][2];
	float fT12 = kA[1][1] * kA[1][2];
	float fTrace = fT11 + fT22;
	float fDiff = fT11 - fT22;
	float fDiscr = sqrt(fDiff*fDiff + 4.0f*fT12*fT12);
	float fRoot1 = 0.5f*(fTrace + fDiscr);
	float fRoot2 = 0.5f*(fTrace - fDiscr);

	float fY = kA[0][0] - (fabs(fRoot1 - fT22) <=
		fabs(fRoot2 - fT22) ? fRoot1 : fRoot2);
	float fZ = kA[0][1];
	float fInvLength = 1.0f / sqrt(fY*fY + fZ*fZ);
	float fSin = fZ*fInvLength;
	float fCos = -fY*fInvLength;

	float fTmp0 = kA[0][0];
	float fTmp1 = kA[0][1];
	kA[0][0] = fCos*fTmp0 - fSin*fTmp1;
	kA[0][1] = fSin*fTmp0 + fCos*fTmp1;
	kA[1][0] = -fSin*kA[1][1];
	kA[1][1] *= fCos;

	size_t iRow;
	for (iRow = 0; iRow < 3; iRow++)
	{
		fTmp0 = kR[0][iRow];
		fTmp1 = kR[1][iRow];
		kR[0][iRow] = fCos*fTmp0 - fSin*fTmp1;
		kR[1][iRow] = fSin*fTmp0 + fCos*fTmp1;
	}

	fY = kA[0][0];
	fZ = kA[1][0];
	fInvLength = 1.0f / sqrt(fY*fY + fZ*fZ);
	fSin = fZ*fInvLength;
	fCos = -fY*fInvLength;

	kA[0][0] = fCos*kA[0][0] - fSin*kA[1][0];
	fTmp0 = kA[0][1];
	fTmp1 = kA[1][1];
	kA[0][1] = fCos*fTmp0 - fSin*fTmp1;
	kA[1][1] = fSin*fTmp0 + fCos*fTmp1;
	kA[0][2] = -fSin*kA[1][2];
	kA[1][2] *= fCos;

	size_t iCol;
	for (iCol = 0; iCol < 3; iCol++)
	{
		fTmp0 = kL[iCol][0];
		fTmp1 = kL[iCol][1];
		kL[iCol][0] = fCos*fTmp0 - fSin*fTmp1;
		kL[iCol][1] = fSin*fTmp0 + fCos*fTmp1;
	}

	fY = kA[0][1];
	fZ = kA[0][2];
	fInvLength = 1.0f / sqrt(fY*fY + fZ*fZ);
	fSin = fZ*fInvLength;
	fCos = -fY*fInvLength;

	kA[0][1] = fCos*kA[0][1] - fSin*kA[0][2];
	fTmp0 = kA[1][1];
	fTmp1 = kA[1][2];
	kA[1][1] = fCos*fTmp0 - fSin*fTmp1;
	kA[1][2] = fSin*fTmp0 + fCos*fTmp1;
	kA[2][1] = -fSin*kA[2][2];
	kA[2][2] *= fCos;

	for (iRow = 0; iRow < 3; iRow++)
	{
		fTmp0 = kR[1][iRow];
		fTmp1 = kR[2][iRow];
		kR[1][iRow] = fCos*fTmp0 - fSin*fTmp1;
		kR[2][iRow] = fSin*fTmp0 + fCos*fTmp1;
	}

	fY = kA[1][1];
	fZ = kA[2][1];
	fInvLength = 1.0f / (fY*fY + fZ*fZ);
	fSin = fZ*fInvLength;
	fCos = -fY*fInvLength;

	kA[1][1] = fCos*kA[1][1] - fSin*kA[2][1];
	fTmp0 = kA[1][2];
	fTmp1 = kA[2][2];
	kA[1][2] = fCos*fTmp0 - fSin*fTmp1;
	kA[2][2] = fSin*fTmp0 + fCos*fTmp1;

	for (iCol = 0; iCol < 3; iCol++)
	{
		fTmp0 = kL[iCol][1];
		fTmp1 = kL[iCol][2];
		kL[iCol][1] = fCos*fTmp0 - fSin*fTmp1;
		kL[iCol][2] = fSin*fTmp0 + fCos*fTmp1;
	}
}

void Matrix3::SingularValueDecomposition(Matrix3& kL, Vector3& kS,
	Matrix3& kR) const
{
	size_t iRow, iCol;

	Matrix3 kA = *this;
	Bidiagonalize(kA, kL, kR);

	for (unsigned int i = 0; i < msSvdMaxIterations; i++)
	{
		float fTmp, fTmp0, fTmp1;
		float fSin0, fCos0, fTan0;
		float fSin1, fCos1, fTan1;

		bool bTest1 = (fabs(kA[0][1]) <=
			msSvdEpsilon*(fabs(kA[0][0]) + fabs(kA[1][1])));
		bool bTest2 = (fabs(kA[1][2]) <=
			msSvdEpsilon*(fabs(kA[1][1]) + fabs(kA[2][2])));
		if (bTest1)
		{
			if (bTest2)
			{
				kS[0] = kA[0][0];
				kS[1] = kA[1][1];
				kS[2] = kA[2][2];
				break;
			}
			else
			{
				fTmp = (kA[1][1] * kA[1][1] - kA[2][2] * kA[2][2] +
					kA[1][2] * kA[1][2]) / (kA[1][2] * kA[2][2]);
				fTan0 = 0.5f*(fTmp + sqrt(fTmp*fTmp + 4.0f));
				fCos0 = 1.0f / sqrt(1.0f + fTan0*fTan0);
				fSin0 = fTan0*fCos0;

				for (iCol = 0; iCol < 3; iCol++)
				{
					fTmp0 = kL[iCol][1];
					fTmp1 = kL[iCol][2];
					kL[iCol][1] = fCos0*fTmp0 - fSin0*fTmp1;
					kL[iCol][2] = fSin0*fTmp0 + fCos0*fTmp1;
				}

				fTan1 = (kA[1][2] - kA[2][2] * fTan0) / kA[1][1];
				fCos1 = 1.0f / sqrt(1.0f + fTan1*fTan1);
				fSin1 = -fTan1*fCos1;

				for (iRow = 0; iRow < 3; iRow++)
				{
					fTmp0 = kR[1][iRow];
					fTmp1 = kR[2][iRow];
					kR[1][iRow] = fCos1*fTmp0 - fSin1*fTmp1;
					kR[2][iRow] = fSin1*fTmp0 + fCos1*fTmp1;
				}

				kS[0] = kA[0][0];
				kS[1] = fCos0*fCos1*kA[1][1] -
					fSin1*(fCos0*kA[1][2] - fSin0*kA[2][2]);
				kS[2] = fSin0*fSin1*kA[1][1] +
					fCos1*(fSin0*kA[1][2] + fCos0*kA[2][2]);
				break;
			}
		}
		else
		{
			if (bTest2)
			{
				fTmp = (kA[0][0] * kA[0][0] + kA[1][1] * kA[1][1] -
					kA[0][1] * kA[0][1]) / (kA[0][1] * kA[1][1]);
				fTan0 = 0.5f*(-fTmp + 1.0f / sqrt(fTmp*fTmp + 4.0f));
				fCos0 = 1.0f / sqrt(1.0f + fTan0*fTan0);
				fSin0 = fTan0*fCos0;

				for (iCol = 0; iCol < 3; iCol++)
				{
					fTmp0 = kL[iCol][0];
					fTmp1 = kL[iCol][1];
					kL[iCol][0] = fCos0*fTmp0 - fSin0*fTmp1;
					kL[iCol][1] = fSin0*fTmp0 + fCos0*fTmp1;
				}

				fTan1 = (kA[0][1] - kA[1][1] * fTan0) / kA[0][0];
				fCos1 = 1.0f / sqrt(1.0f + fTan1*fTan1);
				fSin1 = -fTan1*fCos1;

				for (iRow = 0; iRow < 3; iRow++)
				{
					fTmp0 = kR[0][iRow];
					fTmp1 = kR[1][iRow];
					kR[0][iRow] = fCos1*fTmp0 - fSin1*fTmp1;
					kR[1][iRow] = fSin1*fTmp0 + fCos1*fTmp1;
				}

				kS[0] = fCos0*fCos1*kA[0][0] -
					fSin1*(fCos0*kA[0][1] - fSin0*kA[1][1]);
				kS[1] = fSin0*fSin1*kA[0][0] +
					fCos1*(fSin0*kA[0][1] + fCos0*kA[1][1]);
				kS[2] = kA[2][2];
				break;
			}
			else
			{
				GolubKahanStep(kA, kL, kR);
			}
		}
	}

	for (iRow = 0; iRow < 3; iRow++)
	{
		if (kS[iRow] < 0.0)
		{
			kS[iRow] = -kS[iRow];
			for (iCol = 0; iCol < 3; iCol++)
				kR[iRow][iCol] = -kR[iRow][iCol];
		}
	}
}

void Matrix3::SingularValueComposition(const Matrix3& kL,
	const Vector3& kS, const Matrix3& kR)
{
	size_t iRow, iCol;
	Matrix3 kTmp;

	for (iRow = 0; iRow < 3; iRow++)
	{
		for (iCol = 0; iCol < 3; iCol++)
			kTmp[iRow][iCol] = kS[iRow] * kR[iRow][iCol];
	}

	for (iRow = 0; iRow < 3; iRow++)
	{
		for (iCol = 0; iCol < 3; iCol++)
		{
			m[iRow][iCol] = 0.0;
			for (int iMid = 0; iMid < 3; iMid++)
				m[iRow][iCol] += kL[iRow][iMid] * kTmp[iMid][iCol];
		}
	}
}

void Matrix3::Orthonormalize()
{
	float fInvLength = 1.0f / sqrt(m[0][0] * m[0][0]
		+ m[1][0] * m[1][0] +
		m[2][0] * m[2][0]);

	m[0][0] *= fInvLength;
	m[1][0] *= fInvLength;
	m[2][0] *= fInvLength;

	float fDot0 =
		m[0][0] * m[0][1] +
		m[1][0] * m[1][1] +
		m[2][0] * m[2][1];

	m[0][1] -= fDot0*m[0][0];
	m[1][1] -= fDot0*m[1][0];
	m[2][1] -= fDot0*m[2][0];

	fInvLength = 1.0f / sqrt(m[0][1] * m[0][1] +
		m[1][1] * m[1][1] +
		m[2][1] * m[2][1]);

	m[0][1] *= fInvLength;
	m[1][1] *= fInvLength;
	m[2][1] *= fInvLength;

	float fDot1 =
		m[0][1] * m[0][2] +
		m[1][1] * m[1][2] +
		m[2][1] * m[2][2];

	fDot0 =
		m[0][0] * m[0][2] +
		m[1][0] * m[1][2] +
		m[2][0] * m[2][2];

	m[0][2] -= fDot0*m[0][0] + fDot1*m[0][1];
	m[1][2] -= fDot0*m[1][0] + fDot1*m[1][1];
	m[2][2] -= fDot0*m[2][0] + fDot1*m[2][1];

	fInvLength = 1.0f / sqrt(m[0][2] * m[0][2] +
		m[1][2] * m[1][2] +
		m[2][2] * m[2][2]);

	m[0][2] *= fInvLength;
	m[1][2] *= fInvLength;
	m[2][2] *= fInvLength;
}

void Matrix3::QDUDecomposition(Matrix3& kQ,
	Vector3& kD, Vector3& kU) const
{
	float fInvLength = m[0][0] * m[0][0] + m[1][0] * m[1][0] + m[2][0] * m[2][0];
	if (!Math::FloatEqual(fInvLength, 0)) fInvLength = 1.0f / sqrt(fInvLength);

	kQ[0][0] = m[0][0] * fInvLength;
	kQ[1][0] = m[1][0] * fInvLength;
	kQ[2][0] = m[2][0] * fInvLength;

	float fDot = kQ[0][0] * m[0][1] + kQ[1][0] * m[1][1] +
		kQ[2][0] * m[2][1];
	kQ[0][1] = m[0][1] - fDot*kQ[0][0];
	kQ[1][1] = m[1][1] - fDot*kQ[1][0];
	kQ[2][1] = m[2][1] - fDot*kQ[2][0];
	fInvLength = kQ[0][1] * kQ[0][1] + kQ[1][1] * kQ[1][1] + kQ[2][1] * kQ[2][1];
	if (!Math::FloatEqual(fInvLength, 0, (float)1e-04)) fInvLength = 1.0f / sqrt(fInvLength);

	kQ[0][1] *= fInvLength;
	kQ[1][1] *= fInvLength;
	kQ[2][1] *= fInvLength;

	fDot = kQ[0][0] * m[0][2] + kQ[1][0] * m[1][2] +
		kQ[2][0] * m[2][2];
	kQ[0][2] = m[0][2] - fDot*kQ[0][0];
	kQ[1][2] = m[1][2] - fDot*kQ[1][0];
	kQ[2][2] = m[2][2] - fDot*kQ[2][0];
	fDot = kQ[0][1] * m[0][2] + kQ[1][1] * m[1][2] +
		kQ[2][1] * m[2][2];
	kQ[0][2] -= fDot*kQ[0][1];
	kQ[1][2] -= fDot*kQ[1][1];
	kQ[2][2] -= fDot*kQ[2][1];
	fInvLength = kQ[0][2] * kQ[0][2] + kQ[1][2] * kQ[1][2] + kQ[2][2] * kQ[2][2];
	if (!Math::FloatEqual(fInvLength, 0)) fInvLength = Math::invSqrt(fInvLength);

	kQ[0][2] *= fInvLength;
	kQ[1][2] *= fInvLength;
	kQ[2][2] *= fInvLength;

	float fDet = kQ[0][0] * kQ[1][1] * kQ[2][2] + kQ[0][1] * kQ[1][2] * kQ[2][0] +
		kQ[0][2] * kQ[1][0] * kQ[2][1] - kQ[0][2] * kQ[1][1] * kQ[2][0] -
		kQ[0][1] * kQ[1][0] * kQ[2][2] - kQ[0][0] * kQ[1][2] * kQ[2][1];

	if (fDet < 0.0)
	{
		for (size_t iRow = 0; iRow < 3; iRow++)
		for (size_t iCol = 0; iCol < 3; iCol++)
			kQ[iRow][iCol] = -kQ[iRow][iCol];
	}

	Matrix3 kR;
	kR[0][0] = kQ[0][0] * m[0][0] + kQ[1][0] * m[1][0] +
		kQ[2][0] * m[2][0];
	kR[0][1] = kQ[0][0] * m[0][1] + kQ[1][0] * m[1][1] +
		kQ[2][0] * m[2][1];
	kR[1][1] = kQ[0][1] * m[0][1] + kQ[1][1] * m[1][1] +
		kQ[2][1] * m[2][1];
	kR[0][2] = kQ[0][0] * m[0][2] + kQ[1][0] * m[1][2] +
		kQ[2][0] * m[2][2];
	kR[1][2] = kQ[0][1] * m[0][2] + kQ[1][1] * m[1][2] +
		kQ[2][1] * m[2][2];
	kR[2][2] = kQ[0][2] * m[0][2] + kQ[1][2] * m[1][2] +
		kQ[2][2] * m[2][2];

	kD[0] = kR[0][0];
	kD[1] = kR[1][1];
	kD[2] = kR[2][2];

	float fInvD0 = 1.0f / kD[0];
	kU[0] = kR[0][1] * fInvD0;
	kU[1] = kR[0][2] * fInvD0;
	kU[2] = kR[1][2] / kD[1];
}

float Matrix3::MaxCubicRoot(float afCoeff[3])
{

	const float fOneThird = 1.0f / 3.0f;
	const float fEpsilon = 1e-06f;
	float fDiscr = afCoeff[2] * afCoeff[2] - 3.0f*afCoeff[1];
	if (fDiscr <= fEpsilon)
		return -fOneThird*afCoeff[2];

	float fX = 1.0;
	float fPoly = afCoeff[0] + fX*(afCoeff[1] + fX*(afCoeff[2] + fX));
	if (fPoly < 0.0)
	{
		fX = std::abs(afCoeff[0]);
		float fTmp = 1.0f + std::abs(afCoeff[1]);
		if (fTmp > fX)
			fX = fTmp;
		fTmp = 1.0f + std::abs(afCoeff[2]);
		if (fTmp > fX)
			fX = fTmp;
	}

	float fTwoC2 = 2.0f*afCoeff[2];
	for (int i = 0; i < 16; i++)
	{
		fPoly = afCoeff[0] + fX*(afCoeff[1] + fX*(afCoeff[2] + fX));
		if (std::abs(fPoly) <= fEpsilon)
			return fX;

		float fDeriv = afCoeff[1] + fX*(fTwoC2 + 3.0f*fX);
		fX -= fPoly / fDeriv;
	}

	return fX;
}

float Matrix3::SpectralNorm() const
{
	Matrix3 kP;
	size_t iRow, iCol;
	float fPmax = 0.0;
	for (iRow = 0; iRow < 3; iRow++)
	{
		for (iCol = 0; iCol < 3; iCol++)
		{
			kP[iRow][iCol] = 0.0;
			for (int iMid = 0; iMid < 3; iMid++)
			{
				kP[iRow][iCol] +=
					m[iMid][iRow] * m[iMid][iCol];
			}
			if (kP[iRow][iCol] > fPmax)
				fPmax = kP[iRow][iCol];
		}
	}

	float fInvPmax = 1.0f / fPmax;
	for (iRow = 0; iRow < 3; iRow++)
	{
		for (iCol = 0; iCol < 3; iCol++)
			kP[iRow][iCol] *= fInvPmax;
	}

	float afCoeff[3];
	afCoeff[0] = -(kP[0][0] * (kP[1][1] * kP[2][2] - kP[1][2] * kP[2][1]) +
		kP[0][1] * (kP[2][0] * kP[1][2] - kP[1][0] * kP[2][2]) +
		kP[0][2] * (kP[1][0] * kP[2][1] - kP[2][0] * kP[1][1]));
	afCoeff[1] = kP[0][0] * kP[1][1] - kP[0][1] * kP[1][0] +
		kP[0][0] * kP[2][2] - kP[0][2] * kP[2][0] +
		kP[1][1] * kP[2][2] - kP[1][2] * kP[2][1];
	afCoeff[2] = -(kP[0][0] + kP[1][1] + kP[2][2]);

	float fRoot = MaxCubicRoot(afCoeff);
	float fNorm = std::sqrt(fPmax*fRoot);
	return fNorm;
}

void Matrix3::ToAngleAxis(Vector3& rkAxis, float& rfAngle) const
{

	float fTrace = m[0][0] + m[1][1] + m[2][2];
	float fCos = 0.5f*(fTrace - 1.0f);
	rfAngle = std::acos(fCos); 

	if (rfAngle > 0.0)
	{
		if (rfAngle < M_PI)
		{
			rkAxis.x = m[2][1] - m[1][2];
			rkAxis.y = m[0][2] - m[2][0];
			rkAxis.z = m[1][0] - m[0][1];
			rkAxis.normalise();
		}
		else
		{
			float fHalfInverse;
			if (m[0][0] >= m[1][1])
			{
				if (m[0][0] >= m[2][2])
				{
					rkAxis.x = 0.5f * std::sqrt(m[0][0] -
						m[1][1] - m[2][2] + 1.0f);
					fHalfInverse = 0.5f / rkAxis.x;
					rkAxis.y = fHalfInverse*m[0][1];
					rkAxis.z = fHalfInverse*m[0][2];
				}
				else
				{
					rkAxis.z = 0.5f*std::sqrt(m[2][2] -
						m[0][0] - m[1][1] + 1.0f);
					fHalfInverse = 0.5f / rkAxis.z;
					rkAxis.x = fHalfInverse*m[0][2];
					rkAxis.y = fHalfInverse*m[1][2];
				}
			}
			else
			{
				if (m[1][1] >= m[2][2])
				{
					rkAxis.y = 0.5f*std::sqrt(m[1][1] -
						m[0][0] - m[2][2] + 1.0f);
					fHalfInverse = 0.5f / rkAxis.y;
					rkAxis.x = fHalfInverse*m[0][1];
					rkAxis.z = fHalfInverse*m[1][2];
				}
				else
				{
					rkAxis.z = 0.5f*std::sqrt(m[2][2] -
						m[0][0] - m[1][1] + 1.0f);
					fHalfInverse = 0.5f / rkAxis.z;
					rkAxis.x = fHalfInverse*m[0][2];
					rkAxis.y = fHalfInverse*m[1][2];
				}
			}
		}
	}
	else
	{
		rkAxis.x = 1.0;
		rkAxis.y = 0.0;
		rkAxis.z = 0.0;
	}
}

void Matrix3::FromAngleAxis(const Vector3& rkAxis, const float& fRadians)
{
	float fCos = std::cos(fRadians);
	float fSin = std::sin(fRadians);
	float fOneMinusCos = 1.0f - fCos;
	float fX2 = rkAxis.x*rkAxis.x;
	float fY2 = rkAxis.y*rkAxis.y;
	float fZ2 = rkAxis.z*rkAxis.z;
	float fXYM = rkAxis.x*rkAxis.y*fOneMinusCos;
	float fXZM = rkAxis.x*rkAxis.z*fOneMinusCos;
	float fYZM = rkAxis.y*rkAxis.z*fOneMinusCos;
	float fXSin = rkAxis.x*fSin;
	float fYSin = rkAxis.y*fSin;
	float fZSin = rkAxis.z*fSin;

	m[0][0] = fX2*fOneMinusCos + fCos;
	m[0][1] = fXYM - fZSin;
	m[0][2] = fXZM + fYSin;
	m[1][0] = fXYM + fZSin;
	m[1][1] = fY2*fOneMinusCos + fCos;
	m[1][2] = fYZM - fXSin;
	m[2][0] = fXZM - fYSin;
	m[2][1] = fYZM + fXSin;
	m[2][2] = fZ2*fOneMinusCos + fCos;
}

bool Matrix3::ToEulerAnglesXYZ(float& rfYAngle, float& rfPAngle, float& rfRAngle) const
{

	rfPAngle = std::asin(m[0][2]);
	if (rfPAngle < Math::HALF_PI)
	{
		if (rfPAngle > -Math::HALF_PI)
		{
			rfYAngle = std::atan2(-m[1][2], m[2][2]);
			rfRAngle = std::atan2(-m[0][1], m[0][0]);
			return true;
		}
		else
		{
			float fRmY = std::atan2(m[1][0], m[1][1]);
			rfRAngle = 0.0;
			rfYAngle = rfRAngle - fRmY;
			return false;
		}
	}
	else
	{
		float fRpY = std::atan2(m[1][0], m[1][1]);
		rfRAngle = 0.0; 
		rfYAngle = fRpY - rfRAngle;
		return false;
	}
}

bool Matrix3::ToEulerAnglesXZY(float& rfYAngle, float& rfPAngle, float& rfRAngle) const
{

	rfPAngle = std::asin(-m[0][1]);
	if (rfPAngle < Math::HALF_PI)
	{
		if (rfPAngle > -Math::HALF_PI)
		{
			rfYAngle = std::atan2(m[2][1], m[1][1]);
			rfRAngle = std::atan2(m[0][2], m[0][0]);
			return true;
		}
		else
		{
			float fRmY = std::atan2(-m[2][0], m[2][2]);
			rfRAngle = 0.0;  
			rfYAngle = rfRAngle - fRmY;
			return false;
		}
	}
	else
	{
		float fRpY = std::atan2(-m[2][0], m[2][2]);
		rfRAngle = 0.0; 
		rfYAngle = fRpY - rfRAngle;
		return false;
	}
}

bool Matrix3::ToEulerAnglesYXZ(float& rfYAngle, float& rfPAngle, float& rfRAngle) const
{
	rfPAngle = std::asin(-m[1][2]);
	if (rfPAngle < Math::HALF_PI)
	{
		if (rfPAngle > -Math::HALF_PI)
		{
			rfYAngle = std::atan2(m[0][2], m[2][2]);
			rfRAngle = std::atan2(m[1][0], m[1][1]);
			return true;
		}
		else
		{
			float fRmY = std::atan2(-m[0][1], m[0][0]);
			rfRAngle = 0.0; 
			rfYAngle = rfRAngle - fRmY;
			return false;
		}
	}
	else
	{
		float fRpY = std::atan2(-m[0][1], m[0][0]);
		rfRAngle = 0.0; 
		rfYAngle = fRpY - rfRAngle;
		return false;
	}
}

bool Matrix3::ToEulerAnglesYZX(float& rfYAngle, float& rfPAngle, float& rfRAngle) const
{
	rfPAngle = std::asin(m[1][0]);
	if (rfPAngle < Math::HALF_PI)
	{
		if (rfPAngle > -Math::HALF_PI)
		{
			rfYAngle = std::atan2(-m[2][0], m[0][0]);
			rfRAngle = std::atan2(-m[1][2], m[1][1]);
			return true;
		}
		else
		{
			float fRmY = std::atan2(m[2][1], m[2][2]);
			rfRAngle = 0.0;
			rfYAngle = rfRAngle - fRmY;
			return false;
		}
	}
	else
	{
		float fRpY = std::atan2(m[2][1], m[2][2]);
		rfRAngle = 0.0;
		rfYAngle = fRpY - rfRAngle;
		return false;
	}
}

bool Matrix3::ToEulerAnglesZXY(float& rfYAngle, float& rfPAngle, float& rfRAngle) const
{

	rfPAngle = std::asin(m[2][1]);
	if (rfPAngle < Math::HALF_PI)
	{
		if (rfPAngle > -Math::HALF_PI)
		{
			rfYAngle = std::atan2(-m[0][1], m[1][1]);
			rfRAngle = std::atan2(-m[2][0], m[2][2]);
			return true;
		}
		else
		{
			float fRmY = std::atan2(m[0][2], m[0][0]);
			rfRAngle = 0.0;
			rfYAngle = rfRAngle - fRmY;
			return false;
		}
	}
	else
	{
		float fRpY = std::atan2(m[0][2], m[0][0]);
		rfRAngle = 0.0;
		rfYAngle = fRpY - rfRAngle;
		return false;
	}
}

bool Matrix3::ToEulerAnglesZYX(float& rfYAngle, float& rfPAngle, float& rfRAngle) const
{
	rfPAngle = std::asin(-m[2][0]);
	if (rfPAngle < Math::HALF_PI)
	{
		if (rfPAngle > -Math::HALF_PI)
		{
			rfYAngle = std::atan2(m[1][0], m[0][0]);
			rfRAngle = std::atan2(m[2][1], m[2][2]);
			return true;
		}
		else
		{
			float fRmY = std::atan2(-m[0][1], m[0][2]);
			rfRAngle = 0.0;
			rfYAngle = rfRAngle - fRmY;
			return false;
		}
	}
	else
	{
		float fRpY = std::atan2(-m[0][1], m[0][2]);
		rfRAngle = 0.0;
		rfYAngle = fRpY - rfRAngle;
		return false;
	}
}

void Matrix3::FromEulerAnglesXYZ(const float& fYAngle, const float& fPAngle, const float& fRAngle)
{
	float fCos, fSin;

	fCos = std::cos(fYAngle);
	fSin = std::sin(fYAngle);
	Matrix3 kXMat(1.0, 0.0, 0.0, 0.0, fCos, -fSin, 0.0, fSin, fCos);

	fCos = std::cos(fPAngle);
	fSin = std::sin(fPAngle);
	Matrix3 kYMat(fCos, 0.0, fSin, 0.0, 1.0, 0.0, -fSin, 0.0, fCos);

	fCos = std::cos(fRAngle);
	fSin = std::sin(fRAngle);
	Matrix3 kZMat(fCos, -fSin, 0.0, fSin, fCos, 0.0, 0.0, 0.0, 1.0);

	*this = kXMat*(kYMat*kZMat);
}

void Matrix3::FromEulerAnglesXZY(const float& fYAngle, const float& fPAngle, const float& fRAngle)
{
	float fCos, fSin;

	fCos = std::cos(fYAngle);
	fSin = std::sin(fYAngle);
	Matrix3 kXMat(1.0, 0.0, 0.0, 0.0, fCos, -fSin, 0.0, fSin, fCos);

	fCos = std::cos(fPAngle);
	fSin = std::sin(fPAngle);
	Matrix3 kZMat(fCos, -fSin, 0.0, fSin, fCos, 0.0, 0.0, 0.0, 1.0);

	fCos = std::cos(fRAngle);
	fSin = std::sin(fRAngle);
	Matrix3 kYMat(fCos, 0.0, fSin, 0.0, 1.0, 0.0, -fSin, 0.0, fCos);

	*this = kXMat*(kZMat*kYMat);
}

void Matrix3::FromEulerAnglesYXZ(const float& fYAngle, const float& fPAngle, const float& fRAngle)
{
	float fCos, fSin;

	fCos = std::cos(fYAngle);
	fSin = std::sin(fYAngle);
	Matrix3 kYMat(fCos, 0.0, fSin, 0.0, 1.0, 0.0, -fSin, 0.0, fCos);

	fCos = std::cos(fPAngle);
	fSin = std::sin(fPAngle);
	Matrix3 kXMat(1.0, 0.0, 0.0, 0.0, fCos, -fSin, 0.0, fSin, fCos);

	fCos = std::cos(fRAngle);
	fSin = std::sin(fRAngle);
	Matrix3 kZMat(fCos, -fSin, 0.0, fSin, fCos, 0.0, 0.0, 0.0, 1.0);

	*this = kYMat*(kXMat*kZMat);
}

void Matrix3::FromEulerAnglesYZX(const float& fYAngle, const float& fPAngle, const float& fRAngle)
{
	float fCos, fSin;

	fCos = std::cos(fYAngle);
	fSin = std::sin(fYAngle);
	Matrix3 kYMat(fCos, 0.0, fSin, 0.0, 1.0, 0.0, -fSin, 0.0, fCos);

	fCos = std::cos(fPAngle);
	fSin = std::sin(fPAngle);
	Matrix3 kZMat(fCos, -fSin, 0.0, fSin, fCos, 0.0, 0.0, 0.0, 1.0);

	fCos = std::cos(fRAngle);
	fSin = std::sin(fRAngle);
	Matrix3 kXMat(1.0, 0.0, 0.0, 0.0, fCos, -fSin, 0.0, fSin, fCos);

	*this = kYMat*(kZMat*kXMat);
}

void Matrix3::FromEulerAnglesZXY(const float& fYAngle, const float& fPAngle, const float& fRAngle)
{
	float fCos, fSin;

	fCos = std::cos(fYAngle);
	fSin = std::sin(fYAngle);
	Matrix3 kZMat(fCos, -fSin, 0.0, fSin, fCos, 0.0, 0.0, 0.0, 1.0);

	fCos = std::cos(fPAngle);
	fSin = std::sin(fPAngle);
	Matrix3 kXMat(1.0, 0.0, 0.0, 0.0, fCos, -fSin, 0.0, fSin, fCos);

	fCos = std::cos(fRAngle);
	fSin = std::sin(fRAngle);
	Matrix3 kYMat(fCos, 0.0, fSin, 0.0, 1.0, 0.0, -fSin, 0.0, fCos);

	*this = kZMat*(kXMat*kYMat);
}

void Matrix3::FromEulerAnglesZYX(const float& fYAngle, const float& fPAngle, const float& fRAngle)
{
	float fCos, fSin;

	fCos = std::cos(fYAngle);
	fSin = std::sin(fYAngle);
	Matrix3 kZMat(fCos, -fSin, 0.0, fSin, fCos, 0.0, 0.0, 0.0, 1.0);

	fCos = std::cos(fPAngle);
	fSin = std::sin(fPAngle);
	Matrix3 kYMat(fCos, 0.0, fSin, 0.0, 1.0, 0.0, -fSin, 0.0, fCos);

	fCos = std::cos(fRAngle);
	fSin = std::sin(fRAngle);
	Matrix3 kXMat(1.0, 0.0, 0.0, 0.0, fCos, -fSin, 0.0, fSin, fCos);

	*this = kZMat*(kYMat*kXMat);
}

void Matrix3::Tridiagonal(float afDiag[3], float afSubDiag[3])
{
	float fA = m[0][0];
	float fB = m[0][1];
	float fC = m[0][2];
	float fD = m[1][1];
	float fE = m[1][2];
	float fF = m[2][2];

	afDiag[0] = fA;
	afSubDiag[2] = 0.0;
	if (std::abs(fC) >= EPSILON)
	{
		float fLength = std::sqrt(fB*fB + fC*fC);
		float fInvLength = 1.0f / fLength;
		fB *= fInvLength;
		fC *= fInvLength;
		float fQ = 2.0f*fB*fE + fC*(fF - fD);
		afDiag[1] = fD + fC*fQ;
		afDiag[2] = fF - fC*fQ;
		afSubDiag[0] = fLength;
		afSubDiag[1] = fE - fB*fQ;
		m[0][0] = 1.0;
		m[0][1] = 0.0;
		m[0][2] = 0.0;
		m[1][0] = 0.0;
		m[1][1] = fB;
		m[1][2] = fC;
		m[2][0] = 0.0;
		m[2][1] = fC;
		m[2][2] = -fB;
	}
	else
	{
		afDiag[1] = fD;
		afDiag[2] = fF;
		afSubDiag[0] = fB;
		afSubDiag[1] = fE;
		m[0][0] = 1.0;
		m[0][1] = 0.0;
		m[0][2] = 0.0;
		m[1][0] = 0.0;
		m[1][1] = 1.0;
		m[1][2] = 0.0;
		m[2][0] = 0.0;
		m[2][1] = 0.0;
		m[2][2] = 1.0;
	}
}

bool Matrix3::QLAlgorithm(float afDiag[3], float afSubDiag[3])
{
	for (int i0 = 0; i0 < 3; i0++)
	{
		const unsigned int iMaxIter = 32;
		unsigned int iIter;
		for (iIter = 0; iIter < iMaxIter; iIter++)
		{
			int i1;
			for (i1 = i0; i1 <= 1; i1++)
			{
				float fSum = fabs(afDiag[i1]) +
					fabs(afDiag[i1 + 1]);
				if (fabs(afSubDiag[i1]) + fSum == fSum)
					break;
			}
			if (i1 == i0)
				break;

			float fTmp0 = (afDiag[i0 + 1] - afDiag[i0]) / (2.0f*afSubDiag[i0]);
			float fTmp1 = sqrt(fTmp0*fTmp0 + 1.0f);
			if (fTmp0 < 0.0)
				fTmp0 = afDiag[i1] - afDiag[i0] + afSubDiag[i0] / (fTmp0 - fTmp1);
			else
				fTmp0 = afDiag[i1] - afDiag[i0] + afSubDiag[i0] / (fTmp0 + fTmp1);
			float fSin = 1.0;
			float fCos = 1.0;
			float fTmp2 = 0.0;
			for (int i2 = i1 - 1; i2 >= i0; i2--)
			{
				float fTmp3 = fSin*afSubDiag[i2];
				float fTmp4 = fCos*afSubDiag[i2];
				if (fabs(fTmp3) >= fabs(fTmp0))
				{
					fCos = fTmp0 / fTmp3;
					fTmp1 = sqrt(fCos*fCos + 1.0f);
					afSubDiag[i2 + 1] = fTmp3*fTmp1;
					fSin = 1.0f / fTmp1;
					fCos *= fSin;
				}
				else
				{
					fSin = fTmp3 / fTmp0;
					fTmp1 = sqrt(fSin*fSin + 1.0f);
					afSubDiag[i2 + 1] = fTmp0*fTmp1;
					fCos = 1.0f / fTmp1;
					fSin *= fCos;
				}
				fTmp0 = afDiag[i2 + 1] - fTmp2;
				fTmp1 = (afDiag[i2] - fTmp0)*fSin + 2.0f*fTmp4*fCos;
				fTmp2 = fSin*fTmp1;
				afDiag[i2 + 1] = fTmp0 + fTmp2;
				fTmp0 = fCos*fTmp1 - fTmp4;

				for (int iRow = 0; iRow < 3; iRow++)
				{
					fTmp3 = m[iRow][i2 + 1];
					m[iRow][i2 + 1] = fSin*m[iRow][i2] +
						fCos*fTmp3;
					m[iRow][i2] = fCos*m[iRow][i2] -
						fSin*fTmp3;
				}
			}
			afDiag[i0] -= fTmp2;
			afSubDiag[i0] = fTmp0;
			afSubDiag[i1] = 0.0;
		}

		if (iIter == iMaxIter)
		{
			return false;
		}
	}

	return true;
}

void Matrix3::EigenSolveSymmetric(float afEigenvalue[3],
	Vector3 akEigenvector[3]) const
{
	Matrix3 kMatrix = *this;
	float afSubDiag[3];
	kMatrix.Tridiagonal(afEigenvalue, afSubDiag);
	kMatrix.QLAlgorithm(afEigenvalue, afSubDiag);

	for (size_t i = 0; i < 3; i++)
	{
		akEigenvector[i][0] = kMatrix[0][i];
		akEigenvector[i][1] = kMatrix[1][i];
		akEigenvector[i][2] = kMatrix[2][i];
	}

	Vector3 kCross = akEigenvector[1].crossProduct(akEigenvector[2]);
	float fDet = akEigenvector[0].dotProduct(kCross);
	if (fDet < 0.0)
	{
		akEigenvector[2][0] = -akEigenvector[2][0];
		akEigenvector[2][1] = -akEigenvector[2][1];
		akEigenvector[2][2] = -akEigenvector[2][2];
	}
}

void Matrix3::TensorProduct(const Vector3& rkU, const Vector3& rkV,
	Matrix3& rkProduct)
{
	for (size_t iRow = 0; iRow < 3; iRow++)
	{
		for (size_t iCol = 0; iCol < 3; iCol++)
			rkProduct[iRow][iCol] = rkU[iRow] * rkV[iCol];
	}
}