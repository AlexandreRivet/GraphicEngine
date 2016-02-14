#ifndef _SHADER_H_
#define _SHADER_H_

#include "GL/glew.h"
#include "prerequisites.h"

enum ShaderType
{
	VERTEX,
	FRAGMENT,
	GEOMETRY,
	COMPUTE
};

class Shader
{
public:

	Shader(const std::string& name, ShaderType type, const std::string& code = std::string());
	~Shader();

	std::string getName() const;
	ShaderType getType() const;

	void setCode(const std::string& code = std::string());
	std::string getCode() const;

	bool isCompiled() const;

	GLuint getOpenGLShader() const;

	bool compile();

private:

	std::string m_name;
	ShaderType m_type;
	std::string m_code;

	bool m_isCompiled;

	GLuint m_OpenGLShader;
};

#endif