#include "Objects/Geometry.h"


Geometry::Geometry(const floatVector& vertices, const uintVector& indices, const std::vector<floatVector>& uvs, const floatVector& colors,
	const floatVector& normals, const floatVector& tangents, const floatVector& binormals)
	: mVertices(vertices),
	mIndices(indices),
	mUvs(uvs),
	mColors(colors),
	mNormals(normals),
	mTangents(tangents),
	mBinormals(binormals)
{
}

const floatVector& Geometry::getVertices() const
{
	return mVertices;
};

const uintVector& Geometry::getIndices() const
{
	return mIndices;
}

const std::vector<floatVector>& Geometry::getUvs() const
{
	return mUvs;
}

const floatVector& Geometry::getNormals() const
{
	return mNormals;
}

const floatVector& Geometry::getColors() const
{
	return mColors;
}

const floatVector& Geometry::getTangents() const
{
	return mTangents;
}

const floatVector& Geometry::getBinormals() const
{
	return mBinormals;
}

floatVector& Geometry::getVertices() 
{
	return mVertices;
};

uintVector& Geometry::getIndices() 
{
	return mIndices;
}

std::vector<floatVector>& Geometry::getUvs() 
{
	return mUvs;
}

floatVector& Geometry::getNormals() 
{
	return mNormals;
}

floatVector& Geometry::getColors() 
{
	return mColors;
}

 floatVector& Geometry::getTangents() 
{
	return mTangents;
}

floatVector& Geometry::getBinormals()
{
	return mBinormals;
}

uint Geometry::getNbVertices() const
{
	return mVertices.size();
}

uint Geometry::getNbIndices() const
{
	return mIndices.size();
}

uint Geometry::getNbUvs() const
{
	return mUvs.size();
}

uint Geometry::getNbNormals() const
{
	return mNormals.size();
}

uint Geometry::getNbColors() const
{
	return mColors.size();
}

uint Geometry::getNbTangents() const
{
	return mTangents.size();
}

uint Geometry::getNbBinormals() const
{
	return mBinormals.size();
}