#ifndef _INSTANCINGOBJECT_H_
#define _INSTANCINGOBJECT_H_

#include "cinder/Vector.h"

#include "VAO.h"

template<typename T>
class InstancingObject
{
public:
    InstancingObject(const Mesh& m, const std::vector<T>& params = std::vector<T>())
        : m_vao(m),
        m_params(params)
    {
        glBindVertexArray(m_vao.getId());

        glGenBuffers(1, &m_paramsVBO);
        glBindBuffer(GL_ARRAY_BUFFER, m_paramsVBO);

        /* It's the location in shader */
        glEnableVertexAttribArray(2);

        glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(T), nullptr);
        glVertexAttribDivisor(2, 1);
    }

    InstancingObject(InstancingObject&& i)
        : m_vao(std::move(i.m_vao)),
        m_paramsVBO(i.m_paramsVBO)
        m_params(std::move(m_params))
    {
        i.m_paramsVBO = 0;
    }

    ~InstancingObject()
    {
        if (m_paramsVBO != 0)
            glDeleteBuffers(1, &m_paramsVBO);
    }

    const std::vector<T>& getParamsVector() const
    {
        return m_params;
    }

    std::vector<T>& getParamsVector()
    {
        return m_params;
    }
    
    void setParamsVector(const std::vector<T>& params)
    {
        m_params = params;
    }

    void draw() const
    {
        if (m_params.size() > 0)
        {
            glBindVertexArray(m_vao.getId());

            glBindBuffer(GL_ARRAY_BUFFER, m_paramsVBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(T) * m_params.size(), &m_params[0], GL_DYNAMIC_DRAW);

            glDrawElementsInstancedARB(GL_TRIANGLES, m_vao.getMesh().getIndices().size(), GL_UNSIGNED_INT, 0, m_params.size());
        }
    }

private:
    VAO m_vao;
    GLuint m_paramsVBO;
    std::vector<T> m_params;

    InstancingObject(const InstancingObject&) = delete;
    InstancingObject& operator=(const InstancingObject&) = delete;
};

#endif //_INSTANCINGOBJECT_H_