#include "ShaderManager.h"

#include <fstream>
#include <streambuf>
#include <iostream>
#include <cstdlib>

ShaderManager::ShaderManager()
    : m_programId(0),
    m_vertexShaderId(0),
    m_fragmentShaderId(0),
    m_geometryShaderId(0)
{}

ShaderManager::~ShaderManager()
{
    destroy();
}

bool ShaderManager::loadVertexShader(const std::string& fileName)
{
    m_vertexShaderId = loadShader(GL_VERTEX_SHADER, fileName);
    return m_vertexShaderId > 0;
}

bool ShaderManager::loadFragmentShader(const std::string& fileName)
{
    m_fragmentShaderId = loadShader(GL_FRAGMENT_SHADER, fileName);
    return m_fragmentShaderId > 0;
}

bool ShaderManager::loadGeometryShader(const std::string& fileName)
{
    m_geometryShaderId = loadShader(GL_GEOMETRY_SHADER, fileName);
    return m_geometryShaderId > 0;
}

bool ShaderManager::loadShader(const std::string& vertexShaderName, const std::string& fragmentShaderName, const std::string& geometryShaderName)
{
    bool error(false);

    if (vertexShaderName != "")
        if (!loadVertexShader(vertexShaderName))
            error = true;

    if (fragmentShaderName != "")
        if (!loadFragmentShader(fragmentShaderName))
            error = true;

    if (geometryShaderName != "")
        if (!loadGeometryShader(geometryShaderName))
            error = true;

    return !error;
}

bool ShaderManager::create()
{
    m_programId = glCreateProgram();

    if (m_programId == 0)
    {
        std::cout << "Can't create program" << std::endl;
        return false;
    }

    if (m_vertexShaderId)
    {
        glAttachShader(m_programId, m_vertexShaderId);
    }

    if (m_fragmentShaderId)
    {
        glAttachShader(m_programId, m_fragmentShaderId);
    }

    if (m_geometryShaderId)
    {
        glAttachShader(m_programId, m_geometryShaderId);
    }

    glLinkProgram(m_programId);

    GLint isLink = 0;
    GLint infoLen;

    glGetProgramiv(m_programId, GL_LINK_STATUS, &isLink);

    if (!isLink)
    {
        glGetProgramiv(m_programId, GL_INFO_LOG_LENGTH, &infoLen);

        char* errorMessage = static_cast<char*>(malloc(infoLen * sizeof(char)));

        glGetProgramInfoLog(m_programId, infoLen, NULL, errorMessage);
        std::cout << "Erreur de link du program :\n";
        std::cout.write(errorMessage, infoLen);
        std::cout << std::endl;

        free(errorMessage);

        glDeleteProgram(m_programId);

        return false;
    }

    glValidateProgram(m_programId);
    glGetProgramiv(m_programId, GL_INFO_LOG_LENGTH, &infoLen);

    if (infoLen > 1)
    {
        char* errorMessage = static_cast<char*>(malloc(infoLen * sizeof(char)));

        glGetProgramInfoLog(m_programId, infoLen, NULL, errorMessage);
        std::cout << "Resultat de la validation :\n";
        std::cout.write(errorMessage, infoLen);
        std::cout << std::endl;

        free(errorMessage);
    }

    return true;
}

bool ShaderManager::destroy()
{
    if (m_programId)
    {
        if (m_vertexShaderId)
        {
            glDetachShader(m_programId, m_vertexShaderId);
            glDeleteShader(m_vertexShaderId);
        }

        if (m_fragmentShaderId)
        {
            glDetachShader(m_programId, m_fragmentShaderId);
            glDeleteShader(m_fragmentShaderId);
        }

        if (m_geometryShaderId)
        {
            glDetachShader(m_programId, m_geometryShaderId);
            glDeleteShader(m_geometryShaderId);
        }

        glDeleteProgram(m_programId);
    }

    return true;
}

GLuint ShaderManager::bind()
{
    glUseProgram(m_programId);
    return m_programId;
}

void ShaderManager::unBind()
{
    glUseProgram(0);
}

GLuint ShaderManager::getProgram() const
{
    return m_programId;
}

GLuint ShaderManager::getVertexShader() const
{
    return m_vertexShaderId;
}

GLuint ShaderManager::getFragmentShader() const
{
    return m_fragmentShaderId;
}

GLuint ShaderManager::getGeometryShader() const
{
    return m_geometryShaderId;
}

bool ShaderManager::fileToString(const std::string& fileName, std::string& contentFile) const
{
    std::ifstream file(fileName);

    if (file.is_open())
    {
        file.seekg(0, std::ios::end);
        contentFile.reserve(static_cast<unsigned int>(file.tellg()));
        file.seekg(0, std::ios::beg);

        contentFile.assign((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    }
    else
    {
        std::cout << "Can't open file : " << fileName << std::endl;
        return false;
    }

    return true;
}

GLuint ShaderManager::loadShader(GLenum shaderType, const std::string& fileName)
{
    std::string contentShader;

    if (!fileToString(fileName, contentShader))
    {
        std::cout << "Can't load shader : " << fileName << std::endl;
        return 0;
    }

    GLuint shader = glCreateShader(shaderType);

    if (shader == 0)
    {
        std::cout << "Can't create shader " << fileName << std::endl;
        return  0;
    }

    const char* contentShaderPtr = contentShader.c_str();

    glShaderSource(shader, 1, &contentShaderPtr, NULL);

    glCompileShader(shader);

    GLint isCompile;

    glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompile);

    if (!isCompile)
    {
        GLint infoLen = 0;

        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);

        if (infoLen > 1)
        {
            char* errorMessage = static_cast<char*>(malloc(infoLen * sizeof(char)));

            glGetShaderInfoLog(shader, infoLen, NULL, errorMessage);

            std::cout << "Error compiling shader:\n";
            std::cout.write(errorMessage, infoLen);
            std::cout << std::endl;

            free(errorMessage);
        }

        glDeleteShader(shader);

        return 0;
    }

    return shader;
}