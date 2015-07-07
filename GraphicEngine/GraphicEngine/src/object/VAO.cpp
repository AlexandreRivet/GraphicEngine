#include "VAO.h"

VAO::VAO(const Mesh& m)
    : m_mesh(m),
    m_id(0),
    m_vertexVBO(0),
    m_normalsVBO(0),
    m_indicesVBO(0)
{
    if (m_mesh.getVertex().size() == 0)
        return;

    glGenVertexArrays(1, &m_id);
    glBindVertexArray(m_id);

    glGenBuffers(1, &m_vertexVBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexVBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * m_mesh.getVertex().size(), &m_mesh.getVertex()[0][0], GL_STATIC_DRAW);
    /* It's the location in shader */
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    if (m_mesh.getNormals().size() > 0)
    {
        glGenBuffers(1, &m_normalsVBO);
        glBindBuffer(GL_ARRAY_BUFFER, m_normalsVBO);

        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * m_mesh.getNormals().size(), &m_mesh.getNormals()[0][0], GL_STATIC_DRAW);
        /* It's the location in shader */
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    }

    if (m_mesh.getIndices().size() > 0)
    {
        glGenBuffers(1, &m_indicesVBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indicesVBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * m_mesh.getIndices().size(), &m_mesh.getIndices()[0], GL_STATIC_DRAW);
    }

    glBindVertexArray(0);
}

VAO::VAO(VAO&& vao)
    : m_id(vao.m_id),
    m_vertexVBO(vao.m_vertexVBO),
    m_indicesVBO(vao.m_indicesVBO),
    m_normalsVBO(vao.m_normalsVBO),
    m_mesh(vao.m_mesh)
{
    vao.m_id = 0;
    vao.m_vertexVBO = 0;
    vao.m_indicesVBO = 0;
    vao.m_normalsVBO = 0;
}

VAO::~VAO()
{
    if (m_vertexVBO != 0)
        glDeleteBuffers(1, &m_vertexVBO);

    if (m_indicesVBO != 0)
        glDeleteBuffers(1, &m_indicesVBO);

    if (m_normalsVBO != 0)
        glDeleteBuffers(1, &m_normalsVBO);

    if (m_id != 0)
        glDeleteVertexArrays(1, &m_id);
}

GLuint VAO::getId() const
{
    return m_id;
}

GLuint VAO::getVertexVBO() const
{
    return m_vertexVBO;
}

GLuint VAO::getNormalsVBO() const
{
    return m_normalsVBO;
}

GLuint VAO::getIndicesVBO() const
{
    return m_indicesVBO;
}

const Mesh& VAO::getMesh() const
{
    return m_mesh;
}

void VAO::swap(VAO& vao)
{
    std::swap(m_id, vao.m_id);
    std::swap(m_vertexVBO, vao.m_vertexVBO);
    std::swap(m_indicesVBO, vao.m_indicesVBO);
    std::swap(m_normalsVBO, vao.m_normalsVBO);
    std::swap(m_mesh, vao.m_mesh);
}