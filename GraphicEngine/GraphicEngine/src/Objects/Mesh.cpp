#include "Objects/Mesh.h"

#include "Objects/Mesh.h"

Mesh::Mesh(Geometry geo, Material* mat)
	: mGeometry(geo),
	mMaterial(mat),
	mBuffers(mGeometry.getVertices(), mGeometry.getIndices(), mGeometry.getUvs(), mGeometry.getColors(), mGeometry.getNormals(), mGeometry.getTangents(), mGeometry.getBinormals())
{
}

Mesh::~Mesh()
{

}

Geometry& Mesh::getGeometry()
{
	return mGeometry;
}

Material* Mesh::getMaterial()
{
	return mMaterial;
}

OpenGLBuffer& Mesh::getBuffers()
{
	return mBuffers;
}

/*

Mesh::Mesh(Geometry geo, MaterialSPtr mat, bool useVBO)
	: mGeometry(geo),
	mMaterial(mat),
	mUseVBO(useVBO),
	mHasUvs(false),
	mHasNormals(false)
{
	if (mUseVBO)
		initBuffers();
}

Mesh::~Mesh()
{

}


void Mesh::initBuffers()
{
	// TODO: ADD TANGENTS

	// Get information from geometry
	const std::vector<float>& vertices = mGeometry.getVertices();
	const std::vector<uint>& indices = mGeometry.getIndices();
	const std::vector<float>& normals = mGeometry.getNormals();
	const std::vector<float>& uvs = mGeometry.getUvs();

	uint nbVertices = mGeometry.getNbVertices();
	uint nbIndices = mGeometry.getNbIndices();
	uint nbNormals = mGeometry.getNbNormals();
	uint nbUVs = mGeometry.getNbUvs();

	uint sizeVertices = nbVertices * sizeof(GLfloat);
	uint sizeIndices = nbIndices * sizeof(uint);
	uint sizeNormals = nbNormals * sizeof(GLfloat);
	uint sizeUVs = nbUVs * sizeof(GLfloat);
	uint finalSize = sizeVertices + sizeIndices + sizeNormals + sizeUVs;

	mHasNormals = sizeNormals > 0;
	mHasUvs = sizeUVs > 0;

	uint offset = 0;
	offset += (sizeVertices > 0) ? 3 : 0;
	offset += (sizeNormals > 0) ? 3 : 0;
	offset += (sizeUVs > 0) ? 2 : 0;
	
	// We create our VBO
	glGenBuffers(1, &mVBO);
	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	glBufferData(GL_ARRAY_BUFFER, finalSize, 0, GL_STREAM_DRAW);
	GLfloat* vbo_ptr = (GLfloat*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);

	uint j = 0, prev_pos = 0;
	for (uint i = 0; i < nbVertices; i += 3)
	{
		prev_pos = 0;

		// vertices
		memcpy(vbo_ptr + j + prev_pos, &vertices[i], 3 * sizeof(GLfloat));
		prev_pos += 3;

		// normals
		if (mHasNormals)
		{
			memcpy(vbo_ptr + j + prev_pos, &normals[i], 3 * sizeof(GLfloat));
			prev_pos += 3;
		}

		if (mHasUvs)
		{
			memcpy(vbo_ptr + j + prev_pos, &uvs[i - i / 3], 2 * sizeof(GLfloat));
			prev_pos += 2;
		}

		j += prev_pos;
	}
	glUnmapBuffer(GL_ARRAY_BUFFER);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// We create our VAO
	glGenVertexArrays(1, &mVAO);
	glBindVertexArray(mVAO);
	glBindBuffer(GL_ARRAY_BUFFER, mVBO);

	// positions		==> IMPORTANT: location must be 0 for this
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat)* offset, nullptr);

	prev_pos = 3;
	// normals			==> IMPORTANT: location must be 1 for this
	if (mHasNormals)
	{
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat)* offset, (GLvoid*)(prev_pos * sizeof(GLfloat)) );
		prev_pos += 3;
	}

	// uvs				==> IMPORTANT: location must be 2 for this
	if (mHasUvs)
	{
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat)* offset, (GLvoid*)(prev_pos * sizeof(GLfloat)) );
		prev_pos += 2;
	}

	// We create our IBO
	glGenBuffers(1, &mIBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint)* nbIndices, &indices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

Geometry& Mesh::getGeometry()
{
	return mGeometry;
}

MaterialSPtr& Mesh::getMaterial()
{
	return mMaterial;
}
*/