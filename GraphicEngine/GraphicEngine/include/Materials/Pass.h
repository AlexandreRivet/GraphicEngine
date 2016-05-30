#ifndef _PASS_H_
#define _PASS_H_

#include "Materials/ShaderProgram.h"
#include "Materials/Texture.h"

class Pass
{
public:

	Pass(const std::string& name);
	~Pass();

	void setParameter(const std::string& name, const std::string& value);
	
	void setShaderProgram(ShaderProgram* shaderProgram);
	void setShaderProgram(const std::string& name, ShaderType type);
	void _setVertexProgram(const std::string& name);
	void _setFragmentProgram(const std::string& name);
	void _setGeometryProgram(const std::string& name);
	void _setComputeProgram(const std::string& name);

	void addTextureUnit(const std::string& name, Texture* t);
	Texture* getTexture(const std::string& name);

	bool checkLinked();
	void unlink();

	bool checkShaderProgramAttached(ShaderType type);
	bool _checkVertexProgramAttached();
	bool _checkFragmentProgramAttached();
	bool _checkGeometryProgramAttached();
	bool _checkComputeProgramAttached();

	bool isTransparent() const;
	GLuint getRenderMethod() const;

	GLuint m_OpenGLProgram;
	ShaderProgram* m_vertexProgram;
	ShaderProgram* m_fragmentProgram;
	ShaderProgram* m_geometryProgram;
	ShaderProgram* m_computeProgram;
	std::map<std::string, Texture*> m_textures;
	std::map<std::string, std::string> m_parameters;

private:

	std::string m_name;

	bool m_useGeometryProgram;
	bool m_useComputeProgram;
	bool m_isLinked;
	bool m_isTransparent;

	GLuint m_renderMethod;

};

#endif