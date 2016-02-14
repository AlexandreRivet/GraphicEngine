#ifndef _SHADERPROGRAM_H_
#define _SHADERPROGRAM_H_

#include "Materials/Shader.h"

struct ShaderParameter
{
	std::string key;
	GLint location;
	bool isInit;

	ShaderParameter(const std::string& _key) : key(_key), location(-1), isInit(false) { }
};

struct StringParameter : ShaderParameter
{
	std::string value;

	StringParameter(const std::string& key) : ShaderParameter(key) { }

	void addData(const std::string& data) { value = data; }
};

struct FloatParameter : ShaderParameter
{
	std::vector<float> values;

	FloatParameter(const std::string& key) : ShaderParameter(key) { }

	void addData(float data) { values.push_back(data); }
	void popData() { values.pop_back(); }
};











class ShaderProgram
{
public:

	ShaderProgram(const std::string& name, ShaderType type, Shader* shader);
	ShaderProgram(const ShaderProgram& other);
	~ShaderProgram();

	std::string getName() const;
	ShaderType getShaderType() const;
	Shader* getShader() const;

	void attach(bool attach);
	bool isAttached() const;

	bool setParameter(const std::string& name, const std::string& typeParameter, const std::string& attributeOrUniform, const std::string& typeData, const std::vector<std::string>& values = std::vector<std::string>());
	bool setParameterAuto(const std::string& name, const std::string& attributeOrUniform, const std::string& typeData, const std::vector<std::string>& values);

	std::map< std::string, ShaderParameter > m_attributes_auto;
	std::map< std::string, ShaderParameter > m_uniforms_auto;
	std::map< std::string, StringParameter > m_samplers;
	std::map< std::string, FloatParameter > m_uniforms_noauto;

private:

	std::string m_name;
	Shader* m_shader;
	ShaderType m_type;

	bool m_isAttached;

};

#endif