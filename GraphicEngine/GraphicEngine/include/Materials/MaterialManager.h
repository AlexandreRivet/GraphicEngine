#ifndef _MATERIALMANAGER_H_
#define _MATERIALMANAGER_H_

#include "Materials/Material.h"
#include "Cameras/Camera.h"
#include "Objects/Scene.h"
#include <functional>

enum BlocType
{
	MATERIAL,
	PASS,
	SHADERPROGRAM_VERT,
	SHADERPROGRAM_FRAG,
	SHADERPROGRAM_GEOM,
	SHADERPROGRAM_COMP,
	TEXTURE_UNIT
};

struct Bloc
{
	std::string name;
	BlocType type;

	std::vector<std::pair<std::string, std::string>> parameters;
	std::vector<Bloc*> children;

	Bloc* parent;
};

struct PassParamDef
{
	std::vector<std::string> values;
	std::function<void(std::vector<std::string> values)> render;

	PassParamDef(const std::vector<std::string>& _values, const std::function<void(std::vector<std::string> values)>& _render)
		: values(_values),
		render(_render)
	{

	}
};





struct AttributeAuto
{
	std::function<GLint(GLuint program, const std::string& name)> init;
	std::function<void(GLuint program, GLint location, OpenGLBuffer& buffer)> render;

	AttributeAuto(const std::function<GLint(GLuint program, const std::string& name)>& _init, const std::function<void(GLuint program, GLint location, OpenGLBuffer& buffer)>& _render)
		: init(_init),
		render(_render)
	{

	}
};

struct UniformAuto
{
	std::function<GLint(GLuint program, const std::string& name)> init;
	std::function<void(GLuint program, GLint location, const std::string& paramName, Scene* s, Object3D* obj, Camera* cam, int numSampler)> render;

	UniformAuto(const std::function<GLint(GLuint program, const std::string& name)>& _init, const std::function<void(GLuint program, GLint location, const std::string& paramName, Scene* s, Object3D* obj, Camera* cam, int numSampler)>& _render)
		: init(_init),
		render(_render)
	{

	}
};

struct Sampler
{
	std::function<GLint(GLuint program, const std::string& name)> init;
	std::function<void(GLuint program, GLint location, Pass* pass, const std::string& textureName, int numSampler)> render;

	Sampler(const std::function<GLint(GLuint program, const std::string& name)>& _init, const std::function<void(GLuint program, GLint location, Pass* pass, const std::string& textureName, int numSampler)>& _render)
		: init(_init),
		render(_render)
	{

	}
};

struct UniformNoAuto
{
	std::function<GLint(GLuint program, const std::string& name)> init;
	std::function<void(GLuint program, GLint location, const std::string& paramType, std::vector<float>& values)> render;

	UniformNoAuto(const std::function<GLint(GLuint program, const std::string& name)>& _init, const std::function<void(GLuint program, GLint location, const std::string& paramType, std::vector<float>& values)>& _render)
		: init(_init),
		render(_render)
	{

	}
};






class MaterialManager
{
public:

	static void loadFromFile(const std::string& filename);

	static Shader* getShader(const std::string& name);
	static Material* getMaterial(const std::string& name);
	static ShaderProgram* getShaderProgram(const std::string& name);
	static Texture* getTexture(const std::string& name);

	static void initPassParamDef();			// Va juste définir les paramètres autorisés pour la pass
	static void initShaderProgramParametersAutoDef();

	// Attribute auto
	static GLint _initShaderProgramAttributeAuto(GLuint program, const std::string& name);
	static void _renderShaderProgramAttributeAuto(GLuint program, GLint location, const std::string& paramAutoName, OpenGLBuffer& buffer);

	// Uniform auto
	static GLint _initShaderProgramUniformAuto(GLuint program, const std::string& name);
	static void _renderShaderProgramUniformAuto(GLuint program, GLint location, const std::string& paramName, const std::string& paramUniformName, Scene* s, Object3D* obj, Camera* cam, int numSampler = -1);

	// Sampler
	static void _renderShaderProgramSampler(GLuint program, GLint location, Pass* pass, const std::string& textureName, int numSampler);
	static void _renderSampler(GLint location, GLuint idTexture, int numSampler);

	// Uniform No Auto
	static void _renderShaderProgramUniformNoAuto(GLuint program, GLint location, const std::vector<float>& values);

	// Permet de stocker toutes les values que l'on accepte pour les pass
	static std::map<std::string, PassParamDef> m_passParamDef;

	// Permet de stocker toutes les values que l'on connait pour les shader (aussi bien attributes, qu'uniform) => TODO: Faire les textures
	static std::map<std::string, AttributeAuto> m_attributesAuto;
	static std::map<std::string, UniformAuto> m_uniformsAuto;
	static std::map<std::string, Sampler> m_samplers;
	static std::map<std::string, UniformNoAuto> m_uniformsNoAuto;

protected:

	static Material* _addMaterial(Bloc* mat);
	static void addMaterial(Material* mat);
	static void cloneMaterial(const std::string& name);

	static Shader* _addShader(const std::string& name, ShaderType type);

	static ShaderProgram* _addShaderProgram(Bloc* shaderProg);
	static void addShaderProgram(ShaderProgram* sp);

	static Texture* _addTextureUnit(Bloc* textureUnit);

	

private:

	MaterialManager();

	static std::map<std::string, Material*> m_materials;
	static std::map<std::string, ShaderProgram*> m_programs;
	static std::map<std::string, Shader*> m_shaders;
	static std::map<std::string, Texture*> m_textures;

};



#endif