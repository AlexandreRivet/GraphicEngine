#include "Objects/OpenGLBuffer.h"

OpenGLBuffer::OpenGLBuffer()
{
}

void OpenGLBuffer::bind() const
{
	glBindVertexArray(mVAO.id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO.id);
}

void OpenGLBuffer::unbind() const
{
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void OpenGLBuffer::pushVertices(const std::vector<ShaderData>& newVertices, const std::vector<ShaderData>& allVertices)
{
	// Ajout des vertices
}

void OpenGLBuffer::pushIndices(const std::vector<float>& newIndices, const std::vector<float>& allIndices)
{

}

void OpenGLBuffer::updateGeometry(const Geometry& geo)
{

}