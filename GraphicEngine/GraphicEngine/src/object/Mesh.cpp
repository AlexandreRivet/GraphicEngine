#include "Mesh.h"

Mesh::Mesh()
{}

Mesh::Mesh(const std::vector<cinder::Vec3f>& vertex, const std::vector<unsigned int>& indices, const std::vector<cinder::Vec3f>& normals)
    : m_vertex(vertex),
    m_indices(indices),
    m_normals(normals)
{}

const std::vector<cinder::Vec3f>& Mesh::getVertex() const
{
    return m_vertex;
}

const std::vector<unsigned int>& Mesh::getIndices() const
{
    return m_indices;
}

const std::vector<cinder::Vec3f>& Mesh::getNormals() const
{
    return m_normals;
}

std::vector<cinder::Vec3f>& Mesh::getVertex()
{
    return m_vertex;
}

std::vector<unsigned int>& Mesh::getIndices()
{
    return m_indices;
}

std::vector<cinder::Vec3f>& Mesh::getNormals()
{
    return m_normals;
}

void Mesh::set(const std::vector<cinder::Vec3f>& vertex, const std::vector<unsigned int>& indices, const std::vector<cinder::Vec3f>& normals)
{
    m_vertex = vertex;
    m_indices = indices;
    m_normals = normals;
}