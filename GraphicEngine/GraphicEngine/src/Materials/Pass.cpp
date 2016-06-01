#include "Materials/Pass.h"

Pass::Pass(const std::string& name)
	: m_name(name),
	m_vertexProgram(nullptr),
	m_fragmentProgram(nullptr),
	m_geometryProgram(nullptr),
	m_computeProgram(nullptr),
	m_useGeometryProgram(false),
	m_useComputeProgram(false),
	m_isLinked(false),
	m_isTransparent(false),
	m_renderMethod(GL_TRIANGLES)
{
	m_OpenGLProgram = glCreateProgram();
}

Pass::~Pass()
{

}

void Pass::setParameter(const std::string& name, const std::string& value)
{
	// TODO: checker au niveau du material manager avant d'appeler cette fonction (histoire de gérer les cas non valides)
	if (name == "render_method") {

		static std::map<std::string, GLenum> _renderMethod = {
			{ "points", GL_POINTS },
			{ "lines", GL_LINES},
			{ "triangles", GL_TRIANGLES}
		};
		
		m_renderMethod = _renderMethod[value];

		return;
	}

	m_parameters.insert(std::pair<std::string, std::string>(name, value));

	if ((name == "scene_blend" || name == "separate_scene_blend") && (value.find("alpha_blend") != std::string::npos || value.find("one_minus_src_alpha") != std::string::npos))
		m_isTransparent = true;
}

void Pass::setShaderProgram(ShaderProgram* shaderProgram)
{
	switch (shaderProgram->getShaderType())
	{
	case ShaderType::VERTEX:
		m_vertexProgram = shaderProgram;
		break;
	case ShaderType::FRAGMENT:
		m_fragmentProgram = shaderProgram;
		break;
	case ShaderType::GEOMETRY:
		m_geometryProgram = shaderProgram;
		m_useGeometryProgram = true;
		break;
	case ShaderType::COMPUTE:
		m_computeProgram = shaderProgram;
		m_useComputeProgram = true;
		break;
	}
}

void Pass::addTextureUnit(const std::string& name, Texture* t)
{
	m_textures.insert(std::pair<std::string, Texture*>(name, t));
}

Texture* Pass::getTexture(const std::string& name)
{
	auto texture = m_textures.find(name);
	if (texture != m_textures.end())
		return texture->second;

	return nullptr;
}

bool Pass::checkLinked()
{
	if (m_isLinked)
		return true;

	bool allAttached = (checkShaderProgramAttached(ShaderType::VERTEX) && checkShaderProgramAttached(ShaderType::FRAGMENT) 
						&& checkShaderProgramAttached(ShaderType::GEOMETRY) && checkShaderProgramAttached(ShaderType::COMPUTE));

	if (!allAttached)
		return false;

	glLinkProgram(m_OpenGLProgram);

	GLint isLink = 0;
	GLint infoLen;

	glGetProgramiv(m_OpenGLProgram, GL_LINK_STATUS, &isLink);
	m_isLinked = (isLink == GL_TRUE);

	if (!m_isLinked)
	{
		glGetProgramiv(m_OpenGLProgram, GL_INFO_LOG_LENGTH, &infoLen);

		char* errorMessage = static_cast<char*>(malloc(infoLen * sizeof(char)));

		glGetProgramInfoLog(m_OpenGLProgram, infoLen, NULL, errorMessage);
		std::cout << "Erreur de link du program :\n";
		std::cout.write(errorMessage, infoLen);
		std::cout << std::endl;

		free(errorMessage);

		glDeleteProgram(m_OpenGLProgram);

		return 0;
	}

	/*
	glValidateProgram(m_OpenGLProgram);
	glGetProgramiv(m_OpenGLProgram, GL_INFO_LOG_LENGTH, &infoLen);

	if (infoLen > 1)
	{
		char* errorMessage = static_cast<char*>(malloc(infoLen * sizeof(char)));

		glGetProgramInfoLog(m_OpenGLProgram, infoLen, NULL, errorMessage);
		std::cout << "Resultat de la validation :" << std::endl;
		std::cout.write(errorMessage, infoLen);
		std::cout << std::endl;

		free(errorMessage);
	}
	*/
	return m_isLinked;
	
}

void Pass::unlink()
{

}

bool Pass::checkShaderProgramAttached(ShaderType type)
{
	switch (type)
	{
	case ShaderType::VERTEX:
		return _checkVertexProgramAttached();
		break;
	case ShaderType::FRAGMENT:
		return _checkFragmentProgramAttached();
		break;
	case ShaderType::GEOMETRY:
		return _checkGeometryProgramAttached();
		break;
	case ShaderType::COMPUTE:
		return _checkComputeProgramAttached();
		break;
	}

	return false;
}

bool Pass::_checkVertexProgramAttached()
{
	if (m_vertexProgram == nullptr)
		return true;

	if (m_vertexProgram->isAttached())
		return true;

	if (!m_vertexProgram->getShader()->isCompiled())
	{
		m_vertexProgram->getShader()->compile();
	}
	else
	{
		glAttachShader(m_OpenGLProgram, m_vertexProgram->getShader()->getOpenGLShader());
		m_vertexProgram->attach(true);
		return true;
	}

	return false;
}

bool Pass::_checkFragmentProgramAttached()
{
	if (m_fragmentProgram == nullptr)
		return true;

	if (m_fragmentProgram->isAttached())
		return true;

	if (!m_fragmentProgram->getShader()->isCompiled())
	{
		m_fragmentProgram->getShader()->compile();
	}
	else
	{
		glAttachShader(m_OpenGLProgram, m_fragmentProgram->getShader()->getOpenGLShader());
		m_fragmentProgram->attach(true);
		return true;
	}

	return false;
}
bool Pass::_checkGeometryProgramAttached()
{
	if (m_geometryProgram == nullptr)
		return true;

	if (m_geometryProgram->isAttached())
		return true;

	if (!m_geometryProgram->getShader()->isCompiled())
	{
		m_geometryProgram->getShader()->compile();
	}
	else
	{
		glAttachShader(m_OpenGLProgram, m_geometryProgram->getShader()->getOpenGLShader());
		m_geometryProgram->attach(true);
		return true;
	}

	return false;
}

bool Pass::_checkComputeProgramAttached()
{
	if (m_computeProgram == nullptr)
		return true;

	if (m_computeProgram->isAttached())
		return true;

	if (!m_computeProgram->getShader()->isCompiled())
	{
		m_computeProgram->getShader()->compile();
	}
	else
	{
		glAttachShader(m_OpenGLProgram, m_computeProgram->getShader()->getOpenGLShader());
		m_computeProgram->attach(true);
		return true;
	}

	return false;
}

bool Pass::isTransparent() const
{
	return m_isTransparent;
}

GLuint Pass::getRenderMethod() const
{
	return m_renderMethod;
}