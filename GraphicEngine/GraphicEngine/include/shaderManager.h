#ifndef _SHADERMANAGER_H_
#define _SHADERMANAGER_H_

#include <string>
#include <map>

#include "GL/glew.h"

class ShaderManager
{
public:

    ShaderManager();
    ~ShaderManager();

    bool loadVertexShader(const std::string&);
    bool loadFragmentShader(const std::string&);
    bool loadGeometryShader(const std::string&);
    bool loadShader(const std::string& vertexShader, const std::string& fragmentShader, const std::string& geometryShader);

    bool create();
    bool destroy();
    GLuint bind();
    void unBind();

    GLuint getProgram() const;
    GLuint getVertexShader() const;
    GLuint getFragmentShader() const;
    GLuint getGeometryShader() const;

protected:
    GLuint m_programId;

    GLuint m_vertexShaderId;
    GLuint m_fragmentShaderId;
    GLuint m_geometryShaderId;

    bool fileToString(const std::string& fileName, std::string& contentFile) const;
    GLuint loadShader(GLenum, const std::string&);
    std::map<std::string, GLint> m_uniform;
    std::map<std::string, GLint> m_attribut;
};

#endif //_SHADERMANAGER_H_