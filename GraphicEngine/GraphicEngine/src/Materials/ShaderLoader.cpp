#include "Materials/ShaderLoader.h"

std::map<std::string, ShaderSPtr> ShaderLoader::mShaders;

ShaderLoader::ShaderLoader()
{}

GLuint ShaderLoader::loadVertexShader(const std::string& fileName)
{
    return loadShader(GL_VERTEX_SHADER, fileName);
}

GLuint ShaderLoader::loadFragmentShader(const std::string& fileName)
{
    return loadShader(GL_FRAGMENT_SHADER, fileName);
}

GLuint ShaderLoader::loadGeometryShader(const std::string& fileName)
{
    return loadShader(GL_GEOMETRY_SHADER, fileName);
}

GLuint ShaderLoader::create(GLuint vs, GLuint fs, GLuint gs)
{
    GLuint prog = glCreateProgram();

    if (prog == 0)
    {
        std::cout << "Can't create program" << std::endl;
        return 0;
    }

    if (vs)
    {
        glAttachShader(prog, vs);
    }

    if (fs)
    {
        glAttachShader(prog, fs);
    }

    if (gs)
    {
        glAttachShader(prog, gs);
    }

    glLinkProgram(prog);

    GLint isLink = 0;
    GLint infoLen;

    glGetProgramiv(prog, GL_LINK_STATUS, &isLink);

    if (!isLink)
    {
        glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &infoLen);

        char* errorMessage = static_cast<char*>(malloc(infoLen * sizeof(char)));

        glGetProgramInfoLog(prog, infoLen, NULL, errorMessage);
        std::cout << "Erreur de link du program :\n";
        std::cout.write(errorMessage, infoLen);
        std::cout << std::endl;

        free(errorMessage);

        glDeleteProgram(prog);

        return 0;
    }

    glValidateProgram(prog);
    glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &infoLen);

    if (infoLen > 1)
    {
        char* errorMessage = static_cast<char*>(malloc(infoLen * sizeof(char)));

        glGetProgramInfoLog(prog, infoLen, NULL, errorMessage);
        std::cout << "Resultat de la validation :" << std::endl;
        std::cout.write(errorMessage, infoLen);
        std::cout << std::endl;

        free(errorMessage);
    }

    return prog;
}

GLuint ShaderLoader::loadShader(GLenum shaderType, const std::string& fileName)
{
    std::string contentShader;

    if (!Utils::fileToString(fileName, contentShader))
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

ShaderSPtr ShaderLoader::loadShader(const std::string& name, const std::string& vsName, const std::string& fsName, const std::string& gsName)
{
	GLuint vs = 0, fs = 0, gs = 0;
	if (vsName != "")
	{
		vs = loadVertexShader(vsName);
		if (vs == 0)
		{
			throw std::exception("vs can't load");
		}
	}
	

	if (fsName != "")
	{
		fs = loadFragmentShader(fsName);
		if (fs == 0)
		{
			destroyShaders(vs, fs, gs);
		}
	}

	if (gsName != "")
	{
		gs = loadGeometryShader(gsName);
		if (gs == 0)
		{
			destroyShaders(vs, fs, gs);
		}
	}

	GLuint prog = create(vs, fs, gs);

	if (prog == 0)
	{
		destroyShaders(vs, fs, gs);
	}

	std::shared_ptr<Shader> s(new Shader(prog, vs, fs, gs));

	mShaders[name] = s;

	return s;
}

void ShaderLoader::destroyShaders(GLuint vs, GLuint fs, GLuint gs)
{
	if (vs != 0)
		glDeleteShader(vs);

	if (fs != 0)
		glDeleteShader(fs);

	if (gs != 0)
		glDeleteShader(gs);
}

ShaderSPtr ShaderLoader::getShader(const std::string& name)
{
	return mShaders[name];
}