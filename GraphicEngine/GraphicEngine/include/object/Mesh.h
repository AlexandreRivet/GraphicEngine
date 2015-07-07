#ifndef _MESH_H_
#define _MESH_H_

#include <vector>
#include "cinder/Vector.h"

class Mesh
{
public:
    Mesh();
    Mesh(const std::vector<cinder::Vec3f>& vertex, const std::vector<unsigned int>& indices, const std::vector<cinder::Vec3f>& normals = std::vector<cinder::Vec3f>());

    const std::vector<cinder::Vec3f>& getVertex() const;
    const std::vector<unsigned int>& getIndices() const;
    const std::vector<cinder::Vec3f>& getNormals() const;

    std::vector<cinder::Vec3f>& getVertex();
    std::vector<unsigned int>& getIndices();
    std::vector<cinder::Vec3f>& getNormals();

    void set(const std::vector<cinder::Vec3f>& vertex, const std::vector<unsigned int>& indices, const std::vector<cinder::Vec3f>& normals = std::vector<cinder::Vec3f>());
    
protected:
    std::vector<cinder::Vec3f> m_vertex;
    std::vector<cinder::Vec3f> m_normals;
    std::vector<unsigned int> m_indices;
};

#endif //_MESH_H_