#ifndef _OBJECT3D_H_
#define _OBJECT3D_H_


#include "cinder/Vector.h"
#include "cinder/Quaternion.h"


#include "Mesh.h"

class Object3D
{
public:
    Object3D();
    Object3D(const Mesh&, const cinder::Vec3f&, const cinder::Quatf&);

    const Mesh& getMesh() const;
    const cinder::Vec3f& getPosition() const;
    const cinder::Quatf& getRotation() const;

protected:
    Mesh m_mesh;
    cinder::Vec3f m_position;
    cinder::Quatf m_rotation;
};

#endif //_OBJECT3D_H_