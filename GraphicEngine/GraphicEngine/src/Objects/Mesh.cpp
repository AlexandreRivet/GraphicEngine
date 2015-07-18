#include "Objects/Mesh.h"


Mesh::Mesh(Geometry geo, MaterialSPtr mat, bool useVBO)
	: mGeometry(geo),
	mMaterial(mat),
	mUseVBO(useVBO),
	mHasUvs(false),
	mHasNormals(false)
{
	if (mUseVBO)
		initVBO();
}

Mesh::~Mesh()
{

}


void Mesh::initVBO()
{
	int nbVertices = mGeometry.getNbVertices();
	int nbIndices = mGeometry.getNbIndices();
	
	int nbUvs = mGeometry.getNbUvs();
	mHasUvs = nbUvs > 0;
	
	int nbNormals = mGeometry.getNbNormals();
	mHasNormals = nbNormals > 0;

	// Vertices
	glGenBuffers(1, &mVerticesBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mVerticesBuffer);
	glBufferData(GL_ARRAY_BUFFER, nbVertices * sizeof(float), &(mGeometry.getVertices()[0]), GL_STATIC_DRAW);

	// Indices
	glGenBuffers(1, &mIndicesBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndicesBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, nbIndices * sizeof(int), &(mGeometry.getIndices()[0]), GL_STATIC_DRAW);

	// Uvs
	if (mHasUvs)
	{
		glGenBuffers(1, &mUvsBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, mUvsBuffer);
		glBufferData(GL_ARRAY_BUFFER, nbUvs * sizeof(float), &(mGeometry.getUvs()[0]), GL_STATIC_DRAW);
	}

	// Normals
	if (mHasNormals)
	{
		glGenBuffers(1, &mNormalsBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, mNormalsBuffer);
		glBufferData(GL_ARRAY_BUFFER, nbNormals * sizeof(float), &(mGeometry.getNormals()[0]), GL_STATIC_DRAW);
	}

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Mesh::checkUpdate()
{

}

void Mesh::updateVBO()
{

}

void Mesh::draw() const
{
	if (mUseVBO)
		drawWithVBO();
	else
		drawWithoutVBO();
}

void Mesh::drawWithVBO() const
{

}

void Mesh::drawWithoutVBO() const
{

}