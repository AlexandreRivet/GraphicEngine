#ifndef _VAO_H_
#define _VAO_H_

#include "cinder/gl/gl.h"

#include "Mesh.h"

class VAO
{
public:
    VAO(const Mesh&);
    VAO(VAO&&);

    ~VAO();

    GLuint getId() const;
    GLuint getVertexVBO() const;
    GLuint getNormalsVBO() const;
    GLuint getIndicesVBO() const;
    const Mesh& getMesh() const;

    void swap(VAO&);

protected:
    GLuint m_id;
    GLuint m_vertexVBO;
    GLuint m_normalsVBO;
    GLuint m_indicesVBO;

    Mesh m_mesh;

private:
    VAO(const VAO&) = delete;
};

#endif //_VAO_H_