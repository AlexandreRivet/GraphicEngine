#include "Objects/OpenGLBuffer.h"

void deleteBuffer(BufferInfo* bi)
{
	if (bi == nullptr || bi->numItems == 0)
		return;

	glDeleteBuffers(1, &(bi->id));
	delete bi;
}

OpenGLBuffer::OpenGLBuffer(const floatVector& vertices, const uintVector& indices, const std::vector<floatVector>& uvs, const floatVector& colors,
	const floatVector& normals, const floatVector& tangents, const floatVector& binormals)
{
	mVertexBuffer = createBuffer(GL_ARRAY_BUFFER, vertices, 3, vertices.size() / 3);
	mIndexBuffer = createBuffer(GL_ELEMENT_ARRAY_BUFFER, indices, 1, indices.size());
	mNormalBuffer = createBuffer(GL_ARRAY_BUFFER, normals, 3, normals.size() / 3);
	mColorBuffer = createBuffer(GL_ARRAY_BUFFER, colors, 4, colors.size() / 4);
	mTangentBuffer = createBuffer(GL_ARRAY_BUFFER, tangents, 3, tangents.size() / 3);
	mBinormalBuffer = createBuffer(GL_ARRAY_BUFFER, binormals, 3, binormals.size() / 3);
	for (uint i = 0; i < uvs.size(); ++i)
		mUvsBuffer.push_back(createBuffer(GL_ARRAY_BUFFER, uvs[i], 2, uvs[i].size() / 2));

}

OpenGLBuffer::~OpenGLBuffer()
{
	deleteBuffer(mVertexBuffer);
	deleteBuffer(mIndexBuffer);
	deleteBuffer(mNormalBuffer);
	deleteBuffer(mColorBuffer);
	deleteBuffer(mTangentBuffer);
	deleteBuffer(mBinormalBuffer);
	for (auto& b : mUvsBuffer)
		deleteBuffer(b);
	mUvsBuffer.clear();
}

template <typename T> BufferInfo* createBuffer(GLuint type, T data, uint itemSize, uint numItems)
{
	BufferInfo* bi = new BufferInfo();
	bi->itemSize = itemSize;
	bi->numItems = numItems;

	if (numItems == 0) {
		return bi;
	}

	glGenBuffers(1, &bi->id);
	glBindBuffer(type, bi->id);
	glBufferData(type, sizeof(float) * data.size(), &data[0], GL_STATIC_DRAW);

	glBindBuffer(type, 0);

	return bi;
}
