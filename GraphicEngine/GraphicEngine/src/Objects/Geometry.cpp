#include "Objects/Geometry.h"

Geometry::Geometry(const std::vector<float>& vertices, const std::vector<unsigned int>& indices, const std::vector<float>& uvs, const std::vector<float>& normals)
	: mVertices(vertices),
	mIndices(indices),
	mUvs(uvs),
	mNormals(normals),
	mNeedsUpdate(true)
{
	mHasUvs = mUvs.size() > 0;
	mHasNormals = mNormals.size() > 0;
}

void Geometry::setVertices(const std::vector<float>& vertices)
{
	mVertices = vertices;
	mNeedsUpdate = true;
}

void Geometry::setIndices(const std::vector<uint>& indices)
{
	mIndices = indices;
	mNeedsUpdate = true;
}

void Geometry::setUvs(const std::vector<float>& uvs)
{
	mUvs = uvs;
	mHasUvs = uvs.size() > 0;
	mNeedsUpdate = true;
}

void Geometry::setNormals(const std::vector<float>& normals)
{
	mNormals = normals;
	mHasNormals = normals.size() > 0;
	mNeedsUpdate = true;
}

const std::vector<float>& Geometry::getVertices() const
{
	return mVertices;
}

const std::vector<uint>& Geometry::getIndices() const
{
	return mIndices;
}

const std::vector<float>& Geometry::getUvs() const
{
	return mUvs;
}

const std::vector<float>& Geometry::getNormals() const
{
	return mNormals;
}

int Geometry::getNbVertices() const
{
	return mVertices.size();
}

int Geometry::getNbIndices() const
{
	return mIndices.size();
}

int Geometry::getNbUvs() const
{
	return mUvs.size();
}

int Geometry::getNbNormals() const
{
	return mNormals.size();
}

bool Geometry::hasUvs() const
{
	return mHasUvs;
}
bool Geometry::hasNormals() const
{
	return mHasNormals;
}

bool Geometry::needsUpdate() const
{
	return mNeedsUpdate;
}

void Geometry::setNeedsUpdate(bool update)
{
	mNeedsUpdate = update;
}