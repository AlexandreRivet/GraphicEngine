#include "Materials/Shader.h"

#include "Utils/Utils.h"

Shader::Shader(const std::string& name, ShaderType type, const std::string& code)
	: m_name(name),
	m_type(type),
	m_code(code),
	m_isCompiled(false)

{
	switch (m_type)
	{
		case ShaderType::VERTEX:
			m_OpenGLShader = glCreateShader(GL_VERTEX_SHADER);
			break;
		case ShaderType::FRAGMENT:
			m_OpenGLShader = glCreateShader(GL_FRAGMENT_SHADER);
			break;
		case ShaderType::GEOMETRY:
			m_OpenGLShader = glCreateShader(GL_GEOMETRY_SHADER);
			break;
		case ShaderType::COMPUTE:
			m_OpenGLShader = glCreateShader(GL_COMPUTE_SHADER);
			break;
	}
}

Shader::~Shader()
{
	glDeleteShader(m_OpenGLShader);
}

std::string Shader::getName() const
{
	return m_name;
}

ShaderType Shader::getType() const
{
	return m_type;
}

void Shader::setCode(const std::string& code)
{
	m_code = code;
	m_isCompiled = false;
}

std::string Shader::getCode() const
{
	return m_code;
}

bool Shader::isCompiled() const
{
	return m_isCompiled;
}

GLuint Shader::getOpenGLShader() const
{
	return m_OpenGLShader;
}

bool Shader::compile()
{
	// Il est déjà compilé on n'a pas besoin de le refaire
	if (m_isCompiled)
		return m_isCompiled;

	const char* contentShaderPtr = m_code.c_str();
	glShaderSource(m_OpenGLShader, 1, &contentShaderPtr, NULL);

	glCompileShader(m_OpenGLShader);
	
	GLint isCompiled;
	glGetShaderiv(m_OpenGLShader, GL_COMPILE_STATUS, &isCompiled);

	m_isCompiled = isCompiled;

	if (!m_isCompiled)
	{
		GLint infoLen = 0;

		glGetShaderiv(m_OpenGLShader, GL_INFO_LOG_LENGTH, &infoLen);

		if (infoLen > 1)
		{
			char* errorMessage = static_cast<char*>(malloc(infoLen * sizeof(char)));

			glGetShaderInfoLog(m_OpenGLShader, infoLen, NULL, errorMessage);

			std::cout << "Error compiling shader:\n";
			std::cout.write(errorMessage, infoLen);
			std::cout << std::endl;

			free(errorMessage);
		}

		glDeleteShader(m_OpenGLShader);
	}

	return m_isCompiled;
}