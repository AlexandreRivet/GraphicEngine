#ifndef _SHADERLOADER_H_
#define _SHADERLOADER_H_

#include <string>
#include <map>

#include "GL/glew.h"

#include "Utils/Utils.h"
#include "Materials/Shader.h"


class ShaderLoader
{
public:

	static ShaderSPtr loadShader(const std::string& name, const std::string& vs, const std::string& fs, const std::string& gs);
	static ShaderSPtr getShader(const std::string& name);
 
protected:

	static GLuint loadVertexShader(const std::string&);
	static GLuint loadFragmentShader(const std::string&);
	static GLuint loadGeometryShader(const std::string&);
	static GLuint create(GLuint vs, GLuint fs, GLuint gs);
	static GLuint loadShader(GLenum, const std::string&);

	static void destroyShaders(GLuint vs, GLuint fs, GLuint gs);

private:

	ShaderLoader();

	static std::map<std::string, ShaderSPtr> mShaders;
};

#endif //_SHADERLOADER_H_