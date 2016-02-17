#include "Materials/MaterialManager.h"

#include "Utils\Utils.h"
#include <algorithm>

std::map<std::string, Material*> MaterialManager::m_materials;
std::map<std::string, ShaderProgram*> MaterialManager::m_programs;
std::map<std::string, Shader*> MaterialManager::m_shaders;
std::map<std::string, Texture*> MaterialManager::m_textures;

std::map<std::string, PassParamDef> MaterialManager::m_passParamDef;
std::map<std::string, AttributeAuto> MaterialManager::m_attributesAuto;
std::map<std::string, UniformAuto> MaterialManager::m_uniformsAuto;
std::map<std::string, Sampler> MaterialManager::m_samplers;
std::map<std::string, UniformNoAuto> MaterialManager::m_uniformsNoAuto;

MaterialManager::MaterialManager()
{

}

void MaterialManager::loadFromFile(const std::string& filename)
{
	// On check l'extension en premier
	std::string extension = Utils::split(filename, '.').back();

	if (extension != "mat")
	{
		std::cout << "Invalid file : " << filename << std::endl;
		return;
	}

	// On ouvre le fichier
	std::string contentMaterial;
	if (!Utils::fileToString(filename, contentMaterial))
	{
		std::cout << "Can't load material : " << filename << std::endl;
		return;
	}

	// Supprime toutes les tabulations
	contentMaterial.erase(std::remove(contentMaterial.begin(), contentMaterial.end(), '\t'), contentMaterial.end());

	size_t splitIndex = -1, splitIndex2 = -1;
	Bloc* currentBloc = nullptr;
	bool isCommented = false;
	bool bracketOpened = false, bracketClosed = false;

	std::vector<std::string> lines(Utils::split(contentMaterial, '\n'));
	uint nbLines = lines.size();
	for (uint i = 0; i < nbLines; ++i)
	{
		std::string line = lines[i];

		// Gestion de commentaires
		if (isCommented)
		{
			splitIndex = line.find("*/");
			if (splitIndex != std::string::npos)	// On vient de fermer le commentaire
			{
				line = line.substr(splitIndex + 2);
				lines[i] = line;

				isCommented = false;
				i--;
			}
			continue;
		}
		else				// On n'est pas dans un commentaire
		{
			splitIndex = line.find("/*");
			if (splitIndex != std::string::npos)	// On vient de détecter un commentaire ouvrant
			{
				splitIndex2 = line.find("*/", splitIndex);
				if (splitIndex2 != std::string::npos)		// On vient de détecter un commentaire fermant
				{
					// On doit récupérer ce qu'il y a avant et après le commentaire et le resoumettre => TODO
					std::string start(line.substr(0, splitIndex + 2));
					start.append(line.substr(splitIndex2 + 2));

					lines[i] = line;

					isCommented = false;
					i--;
					continue;
				}
				else
				{
					lines[i] = line.substr(0, splitIndex + 2);
					isCommented = true;
				}
			}
		}

		splitIndex = line.find("//");
		if (splitIndex != std::string::npos)
		{
			line = line.substr(0, splitIndex);
		}

		line = Utils::trim(line);

		if (line.length() == 0)
			continue;

		if (line.substr(0, 8) == "material")			// On ouvre un material (on n'a pas besoin d'avoir une { d'ouverte)
		{
			currentBloc = new Bloc();
			currentBloc->type = BlocType::MATERIAL;
			currentBloc->parent = nullptr;
			std::string name = Utils::trim(line.substr(8));
			if (name.length() != 0)
				currentBloc->name = name;
		}
		else if (bracketOpened && line.substr(0, 4) == "pass")			// On ouvre une pass
		{
			Bloc* tmp = new Bloc();
			tmp->type = BlocType::PASS;
			tmp->parent = currentBloc;
			currentBloc->children.push_back(tmp);
			currentBloc = tmp;
			std::string name = Utils::trim(line.substr(4));
			if (name.length() != 0)
				currentBloc->name = name;

			bracketOpened = false;
		}
		else if (bracketOpened && line.substr(0, 18) == "vertex_program_ref")			// On ouvre un vertex_program
		{
			Bloc* tmp = new Bloc();
			tmp->type = BlocType::SHADERPROGRAM_VERT;
			tmp->parent = currentBloc;
			currentBloc->children.push_back(tmp);
			currentBloc = tmp;
			std::string name = Utils::trim(line.substr(18));
			if (name.length() != 0)
				currentBloc->name = name;

			bracketOpened = false;
		}
		else if (bracketOpened && line.substr(0, 20) == "fragment_program_ref")			// On ouvre un fragment_program
		{
			Bloc* tmp = new Bloc();
			tmp->type = BlocType::SHADERPROGRAM_FRAG;
			tmp->parent = currentBloc;
			currentBloc->children.push_back(tmp);
			currentBloc = tmp;
			std::string name = Utils::trim(line.substr(20));
			if (name.length() != 0)
				currentBloc->name = name;

			bracketOpened = false;
		}
		else if (bracketOpened && line.substr(0, 20) == "geometry_program_ref")			// On ouvre un geometry_program
		{
			Bloc* tmp = new Bloc();
			tmp->type = BlocType::SHADERPROGRAM_GEOM;
			tmp->parent = currentBloc;
			currentBloc->children.push_back(tmp);
			currentBloc = tmp;
			std::string name = Utils::trim(line.substr(20));
			if (name.length() != 0)
				currentBloc->name = name;

			bracketOpened = false;
		}
		else if (bracketOpened && line.substr(0, 19) == "compute_program_ref")			// On ouvre un compute_program
		{
			Bloc* tmp = new Bloc();
			tmp->type = BlocType::SHADERPROGRAM_COMP;
			tmp->parent = currentBloc;
			currentBloc->children.push_back(tmp);
			currentBloc = tmp;
			std::string name = Utils::trim(line.substr(19));
			if (name.length() != 0)
				currentBloc->name = name;

			bracketOpened = false;
		}
		else if (bracketOpened && line.substr(0, 12) == "texture_unit")			// On ouvre une texture_unit
		{
			Bloc* tmp = new Bloc();
			tmp->type = BlocType::TEXTURE_UNIT;
			tmp->parent = currentBloc;
			currentBloc->children.push_back(tmp);
			currentBloc = tmp;
			std::string name = Utils::trim(line.substr(12));
			if (name.length() != 0)
				currentBloc->name = name;

			bracketOpened = false;
		}
		else			// On est dans un bloc
		{
			splitIndex = line.find('{');
			if (splitIndex != std::string::npos)
			{
				bracketOpened = true;
			}
			else if (bracketOpened)
			{
				splitIndex = line.find('}');
				if (splitIndex != std::string::npos)
				{
					// On sort du bloc
					bracketClosed = true;

					// Si on a des choses spécifiques à faire
					switch (currentBloc->type)
					{
					case BlocType::MATERIAL:
						_addMaterial(currentBloc);
						break;
					case BlocType::SHADERPROGRAM_VERT:
					case BlocType::SHADERPROGRAM_FRAG:
					case BlocType::SHADERPROGRAM_GEOM:
					case BlocType::SHADERPROGRAM_COMP:
						_addShaderProgram(currentBloc);
						break;
					case BlocType::TEXTURE_UNIT:
						_addTextureUnit(currentBloc);
						break;
					}

					if (currentBloc->parent != nullptr)
						currentBloc = currentBloc->parent;
				}
				else
				{
					std::size_t first = line.find_first_of(' ');
					std::string key = line.substr(0, first);
					std::string values = line.substr(first + 1);

					currentBloc->parameters.push_back(std::pair<std::string, std::string>(key, values));
				}
			}
		}
	}

	std::cout << "Material: " << currentBloc->name << " successfully loaded." << std::endl;

	int i = 0;

}

Material* MaterialManager::_addMaterial(Bloc* b)
{
	auto m = m_materials.find(b->name);
	if (m != m_materials.end())
		return m->second;

	Material* mat = new Material(b->name);

	// On parcourt toutes les pass
	for (uint i = 0; i < b->children.size(); ++i)
	{
		Bloc* passBloc = b->children[i];

		Pass* pass = new Pass(passBloc->name);

		// On ajoute les paramètres
		std::size_t first;
		std::string key, values;
		for (uint j = 0; j < passBloc->parameters.size(); ++j)
		{
			pass->setParameter(passBloc->parameters[j].first, passBloc->parameters[j].second);
		}

		// On ajoute les shaderprogram et les texture unit
		for (uint j = 0; j < passBloc->children.size(); ++j)
		{
			Bloc* bloc_tmp = passBloc->children[j];

			switch (bloc_tmp->type)
			{
			case BlocType::SHADERPROGRAM_VERT:
			case BlocType::SHADERPROGRAM_FRAG:
			case BlocType::SHADERPROGRAM_GEOM:
			case BlocType::SHADERPROGRAM_COMP:
			{
				ShaderProgram* sp = getShaderProgram(bloc_tmp->name);

				if (sp != nullptr)
				{
					pass->setShaderProgram(sp);
				}

			}
				break;
			case BlocType::TEXTURE_UNIT:
			{
				Texture* t = getTexture(bloc_tmp->name);

				if (t != nullptr)
				{
					pass->addTextureUnit(bloc_tmp->name, t);
				}
			}


				break;
			}

		}

		mat->addPass(passBloc->name, pass);
	}

	m_materials.insert(std::pair<std::string, Material*>(b->name, mat));

	return mat;
}

ShaderProgram* MaterialManager::_addShaderProgram(Bloc* b)
{
	auto sp = m_programs.find(b->name);
	if (sp != m_programs.end())
		return sp->second;

	ShaderType type = ShaderType::VERTEX;
	switch (b->type)
	{
	case BlocType::SHADERPROGRAM_FRAG:
		type = ShaderType::FRAGMENT;
		break;
	case BlocType::SHADERPROGRAM_GEOM:
		type = ShaderType::GEOMETRY;
		break;
	case BlocType::SHADERPROGRAM_COMP:
		type = ShaderType::COMPUTE;
		break;
	}

	std::string shaderName = "";
	for (uint i = 0; i < b->parameters.size(); ++i)
	{
		std::pair<std::string, std::string> param = b->parameters[i];
		if (param.first == "source")
		{
			shaderName = param.second;
			break;
		}
	}

	Shader* shader = _addShader(shaderName, type);

	ShaderProgram* shaderProg = new ShaderProgram(b->name, type, shader);

	for (uint i = 0; i < b->parameters.size(); ++i)
	{
		std::pair<std::string, std::string> param = b->parameters[i];
		if (param.first == "source")
			continue;

		std::vector<std::string> parameters = Utils::split(param.second, ' ');

		std::vector<std::string> additionalValues;
		if (parameters.size() > 3)
		{
			for (uint i = 3; i < parameters.size(); ++i)
			{
				additionalValues.push_back(parameters.at(i));
			}
		}

		// Fair le check et toutes les sécurités => TODO
		shaderProg->setParameter(parameters[1], param.first, parameters[0], parameters[2], additionalValues);
	}

	m_programs.insert(std::pair<std::string, ShaderProgram*>(b->name, shaderProg));

	return shaderProg;
}

Shader* MaterialManager::_addShader(const std::string& name, ShaderType type)
{
	auto s = m_shaders.find(name);
	if (s != m_shaders.end())
		return s->second;

	std::string contentShader;
	if (!Utils::fileToString(name, contentShader))
	{
		std::cout << "Can't load shader : " << name << std::endl;
		return nullptr;
	}

	Shader* shader = new Shader(name, type, contentShader);

	m_shaders.insert(std::pair<std::string, Shader*>(name, shader));

	return shader;
}

Texture* MaterialManager::_addTextureUnit(Bloc* textureUnit)
{
	auto t = m_textures.find(textureUnit->name);
	if (t != m_textures.end())
		return t->second;

	std::string textureName = "";
	for (uint i = 0; i < textureUnit->parameters.size(); ++i)
	{
		std::pair<std::string, std::string> param = textureUnit->parameters[i];
		if (param.first == "texture")
		{
			textureName = param.second;
			break;
		}
	}

	Texture* texture = new Texture(textureName);

	if (texture->hasImage())
	{
		m_textures.insert(std::pair<std::string, Texture*>(textureUnit->name, texture));
		return texture;
	}

	return nullptr;

}

Shader* MaterialManager::getShader(const std::string& name)
{
	auto s = m_shaders.find(name);
	if (s != m_shaders.end())
		return s->second;

	return nullptr;
}

Material* MaterialManager::getMaterial(const std::string& name)
{
	auto m = m_materials.find(name);
	if (m != m_materials.end())
		return m->second;

	return nullptr;
}

ShaderProgram* MaterialManager::getShaderProgram(const std::string& name)
{
	auto p = m_programs.find(name);
	if (p != m_programs.end())
		return p->second;

	return nullptr;
}

Texture* MaterialManager::getTexture(const std::string& name)
{
	auto t = m_textures.find(name);
	if (t != m_textures.end())
		return t->second;

	return nullptr;
}

void MaterialManager::initPassParamDef()
{
	// SCENE BLEND
	PassParamDef ppd = PassParamDef(
		std::vector<std::string>({ "zero", "one", "dest_color", "src_color", "one_minus_src_color",
		"one_minus_dest_color", "src_alpha", "dest_alpha", "one_minus_src_alpha",
		"one_minus_dest_alpha", "src_alpha_saturate"
	}),
	[](const std::vector<std::string>& values) {

		GLuint sFactor = GL_ONE;
		GLuint dFactor = GL_ZERO;

		if (values.size() > 1)
		{
			std::vector<GLuint> validFactor;
			for (uint i = 0; i < values.size(); ++i)
			{
				std::string value = values[i];

				if (value == "zero")									//Multiply by all colors by 0.
					validFactor.push_back(GL_ZERO);
				else if (value == "one")								//Multiplies all colors by 1.
					validFactor.push_back(GL_ONE);
				else if (value == "dest_color")							//Multiply by destination color value.
					validFactor.push_back(GL_DST_COLOR);
				else if (value == "src_color")							//Multiply by source color value.
					validFactor.push_back(GL_SRC_COLOR);
				else if (value == "one_minus_src_color")				//Multiply by 1 minus each color value.
					validFactor.push_back(GL_ONE_MINUS_SRC_COLOR);
				else if (value == "one_minus_dest_color")				//Multiply by 1 minus each color value.
					validFactor.push_back(GL_ONE_MINUS_DST_COLOR);
				else if (value == "src_alpha")							//Multiply all colors by source alpha value.
					validFactor.push_back(GL_SRC_ALPHA);
				else if (value == "dest_alpha")							//Multiply all colors by dest alpha value.
					validFactor.push_back(GL_DST_ALPHA);
				else if (value == "one_minus_src_alpha")				//Multiply all colors by 1 minus source alpha value.
					validFactor.push_back(GL_ONE_MINUS_SRC_ALPHA);
				else if (value == "one_minus_dest_alpha")				//Multiply all colors by 1 minus destination alpha value.
					validFactor.push_back(GL_ONE_MINUS_DST_ALPHA);
				else if (value == "src_alpha_saturate")					//Multiply by the smaller of either source or destination alpha value.
					validFactor.push_back(GL_SRC_ALPHA_SATURATE);

				// On a trouvé les facteurs voulus
				if (validFactor.size() >= 2)
					break;

			}

			if (validFactor.size() > 0)
				sFactor = validFactor.at(0);
			if (validFactor.size() > 1)
				dFactor = validFactor.at(1);
		}

		glBlendFunc(sFactor, dFactor);
		glEnable(GL_BLEND);

	});

	m_passParamDef.insert(std::pair<std::string, PassParamDef>("scene_blend", ppd));

	// SEPARATE SCENE BLEND
	ppd = PassParamDef(
		std::vector<std::string>({ "zero", "one", "dest_color", "src_color", "one_minus_src_color",
		"one_minus_dest_color", "src_alpha", "dest_alpha", "one_minus_src_alpha",
		"one_minus_dest_alpha", "src_alpha_saturate"
	}),
	[](const std::vector<std::string>& values) {

		GLuint sFactor = GL_ONE;
		GLuint dFactor = GL_ZERO;
		GLuint sFactorAlpha = GL_ONE;
		GLuint dFactorAlpha = GL_ZERO;

		if (values.size() > 2)
		{
			std::vector<GLuint> validFactor;
			for (uint i = 0; i < values.size(); ++i)
			{
				std::string value = values[i];

				if (value == "zero")									//Multiply by all colors by 0.
					validFactor.push_back(GL_ZERO);
				else if (value == "one")								//Multiplies all colors by 1.
					validFactor.push_back(GL_ONE);
				else if (value == "dest_color")							//Multiply by destination color value.
					validFactor.push_back(GL_DST_COLOR);
				else if (value == "src_color")							//Multiply by source color value.
					validFactor.push_back(GL_SRC_COLOR);
				else if (value == "one_minus_src_color")				//Multiply by 1 minus each color value.
					validFactor.push_back(GL_ONE_MINUS_SRC_COLOR);
				else if (value == "one_minus_dest_color")				//Multiply by 1 minus each color value.
					validFactor.push_back(GL_ONE_MINUS_DST_COLOR);
				else if (value == "src_alpha")							//Multiply all colors by source alpha value.
					validFactor.push_back(GL_SRC_ALPHA);
				else if (value == "dest_alpha")							//Multiply all colors by dest alpha value.
					validFactor.push_back(GL_DST_ALPHA);
				else if (value == "one_minus_src_alpha")				//Multiply all colors by 1 minus source alpha value.
					validFactor.push_back(GL_ONE_MINUS_SRC_ALPHA);
				else if (value == "one_minus_dest_alpha")				//Multiply all colors by 1 minus destination alpha value.
					validFactor.push_back(GL_ONE_MINUS_DST_ALPHA);
				else if (value == "src_alpha_saturate")					//Multiply by the smaller of either source or destination alpha value.
					validFactor.push_back(GL_SRC_ALPHA_SATURATE);

				// On a trouvé les facteurs voulus
				if (validFactor.size() >= 4)
					break;
			}

			if (validFactor.size() > 0)
				sFactor = validFactor.at(0);
			if (validFactor.size() > 1)
				dFactor = validFactor.at(1);
			if (validFactor.size() > 2)
				sFactorAlpha = validFactor.at(2);
			if (validFactor.size() > 3)
				dFactorAlpha = validFactor.at(3);

		}

		glBlendFuncSeparate(sFactor, dFactor, sFactorAlpha, dFactorAlpha);
		glEnable(GL_BLEND);

	});

	m_passParamDef.insert(std::pair<std::string, PassParamDef>("separate_scene_blend", ppd));


	// DEPTH TEST
	ppd = PassParamDef(
		std::vector<std::string>({ "on", "off" }),
		[](const std::vector<std::string>& values) {

		if (values.size() == 0)
			return;

		std::string value = values.at(0);

		if (value == "on")
			glEnable(GL_DEPTH_TEST);
		else
			glDisable(GL_DEPTH_TEST);

	});

	m_passParamDef.insert(std::pair<std::string, PassParamDef>("depth_test", ppd));

	// DEPTH FUNC
	ppd = PassParamDef(
		std::vector<std::string>({ "always_fail", "always_pass", "less", "less_equal", "equal", "not_equal", "greater_equal", "greater" }),
		[](const std::vector<std::string>& values) {

		if (values.size() == 0)
			return;

		std::string value = values.at(0);
		GLuint finalVal = GL_ALWAYS;

		if (value == "always_fail")
			finalVal = GL_NEVER;
		else if (value == "always_pass")
			finalVal = GL_ALWAYS;
		else if (value == "less")
			finalVal = GL_LESS;
		else if (value == "less_equal")
			finalVal = GL_LEQUAL;
		else if (value == "equal")
			finalVal = GL_EQUAL;
		else if (value == "not_equal")
			finalVal = GL_NOTEQUAL;
		else if (value == "greater_equal")
			finalVal = GL_GEQUAL;
		else if (value == "greater")
			finalVal = GL_GREATER;

		glDepthFunc(finalVal);

	});

	m_passParamDef.insert(std::pair<std::string, PassParamDef>("depth_func", ppd));

	// DEPTH CHECK WRITE
	ppd = PassParamDef(
		std::vector<std::string>({ "on", "off" }),
		[](const std::vector<std::string>& values) {

		bool depth_check = true;
		bool depth_write = true;

		if (values.size() > 0)
			depth_check = (values.at(0) == "on");
		if (values.size() > 1)
			depth_write = (values.at(1) == "on");

		if (depth_check)
		{
			glEnable(GL_DEPTH_TEST);
			glDepthFunc(GL_LEQUAL);
		}
		else
		{
			glDisable(GL_DEPTH_TEST);
		}

		if (depth_write)
		{
			glDepthMask(true);
		}
		else
		{
			glDepthMask(false);
		}



	});

	m_passParamDef.insert(std::pair<std::string, PassParamDef>("depth_check_write", ppd));

	// DEPTH RANGE
	ppd = PassParamDef(
		std::vector<std::string>({ "float" }),
		[](const std::vector<std::string>& values) {

		float zNear = 0.0f;
		float zFar = 1.0f;

		if (values.size() > 0)
			zNear = std::atof(values.at(0).c_str());
		if (values.size() > 1)
			zFar = std::atof(values.at(1).c_str());

		glDepthRange(zNear, zFar);

	});

	m_passParamDef.insert(std::pair<std::string, PassParamDef>("depth_range", ppd));

	// DEPTH BIAS
	ppd = PassParamDef(
		std::vector<std::string>({ "float" }),
		[](const std::vector<std::string>& values) {

		float zNear = 0.0f;
		float zFar = 1.0f;
		float offset = 0.0f;
		float scale = 1.0f;

		if (values.size() > 0)
			offset = std::atof(values.at(0).c_str());
		if (values.size() > 1)
			scale = std::atof(values.at(1).c_str());

		zNear += offset;
		zFar *= scale;
		zFar += offset;

		glDepthRange(zNear, zFar);

	});

	m_passParamDef.insert(std::pair<std::string, PassParamDef>("depth_bias", ppd));

	// CULL SOFTWARE
	ppd = PassParamDef(
		std::vector<std::string>({ "front", "back", "doubleside", "none" }),
		[](const std::vector<std::string>& values) {

		if (values.size() == 0)
			return;

		bool haveCullFace = false;
		GLuint cullFace = GL_BACK;

		std::string value = values.at(0);

		if (value == "front")
		{
			haveCullFace = true;
			cullFace = GL_FRONT;
		}
		else if (value == "back")
		{
			haveCullFace = true;
			cullFace = GL_BACK;
		}
		else if (value == "doubleside")
		{
			haveCullFace = true;
			cullFace = GL_FRONT_AND_BACK;
		}
		else if (value == "none")
		{
			haveCullFace = false;
		}

		if (haveCullFace)
		{
			glEnable(GL_CULL_FACE);
			glCullFace(cullFace);
		}
		else
		{
			glDisable(GL_CULL_FACE);
		}

	});

	m_passParamDef.insert(std::pair<std::string, PassParamDef>("cull_software", ppd));

	// CULL HARDWARE
	ppd = PassParamDef(
		std::vector<std::string>({ "clockwise", "counterclockwise", "none" }),
		[](const std::vector<std::string>& values) {

		if (values.size() == 0)
			return;

		bool haveCullFace = false;
		GLuint frontFace = GL_CCW;

		std::string value = values.at(0);

		if (value == "clockwise")
		{
			haveCullFace = true;
			frontFace = GL_CW;
		}
		else if (value == "counterclockwise")
		{
			haveCullFace = true;
			frontFace = GL_CCW;
		}
		else if (value == "none")
		{
			haveCullFace = false;
		}

		if (haveCullFace)
		{
			glEnable(GL_CULL_FACE);
			glFrontFace(frontFace);
		}
		else
		{
			glDisable(GL_CULL_FACE);
		}

	});

	m_passParamDef.insert(std::pair<std::string, PassParamDef>("cull_hardware", ppd));

	// POLYGON MODE
	ppd = PassParamDef(
		std::vector<std::string>({ "solid", "wireframe", "points" }),
		[](const std::vector<std::string>& values) {

		if (values.size() == 0)
			return;

		// TODO: GERER CELA

	});

	m_passParamDef.insert(std::pair<std::string, PassParamDef>("polygon_mode", ppd));

}

void MaterialManager::initShaderProgramParametersAutoDef()
{
	/* *************

	ATTRIBUTES CONNUS

	************* */

	// POSITION
	AttributeAuto aa = AttributeAuto(
		[](GLuint program, const std::string& name) {
		return MaterialManager::_initShaderProgramAttributeAuto(program, name);
	},
		[](GLuint program, GLint location, OpenGLBuffer buffer) {
		MaterialManager::_renderShaderProgramAttributeAuto(program, location, "POSITION", buffer);
	}
	);
	m_attributesAuto.insert(std::pair<std::string, AttributeAuto>("POSITION", aa));

	// NORMAL
	aa = AttributeAuto(
		[](GLuint program, const std::string& name) {
		return MaterialManager::_initShaderProgramAttributeAuto(program, name);
	},
		[](GLuint program, GLint location, OpenGLBuffer buffer) {
		MaterialManager::_renderShaderProgramAttributeAuto(program, location, "NORMAL", buffer);
	}
	);
	m_attributesAuto.insert(std::pair<std::string, AttributeAuto>("NORMAL", aa));

	// TANGENT
	aa = AttributeAuto(
		[](GLuint program, const std::string& name) {
		return MaterialManager::_initShaderProgramAttributeAuto(program, name);
	},
		[](GLuint program, GLint location, OpenGLBuffer buffer) {
		MaterialManager::_renderShaderProgramAttributeAuto(program, location, "TANGENT", buffer);
	}
	);
	m_attributesAuto.insert(std::pair<std::string, AttributeAuto>("TANGENT", aa));

	// BINORMAL
	aa = AttributeAuto(
		[](GLuint program, const std::string& name) {
		return MaterialManager::_initShaderProgramAttributeAuto(program, name);
	},
		[](GLuint program, GLint location, OpenGLBuffer buffer) {
		MaterialManager::_renderShaderProgramAttributeAuto(program, location, "BINORMAL", buffer);
	}
	);
	m_attributesAuto.insert(std::pair<std::string, AttributeAuto>("BINORMAL", aa));

	// VERTEXCOLOR
	aa = AttributeAuto(
		[](GLuint program, const std::string& name) {
		return MaterialManager::_initShaderProgramAttributeAuto(program, name);
	},
		[](GLuint program, GLint location, OpenGLBuffer buffer) {
		MaterialManager::_renderShaderProgramAttributeAuto(program, location, "VERTEXCOLOR", buffer);
	}
	);
	m_attributesAuto.insert(std::pair<std::string, AttributeAuto>("VERTEXCOLOR", aa));

	// TEXCOORD0
	aa = AttributeAuto(
		[](GLuint program, const std::string& name) {
		return MaterialManager::_initShaderProgramAttributeAuto(program, name);
	},
		[](GLuint program, GLint location, OpenGLBuffer buffer) {
		MaterialManager::_renderShaderProgramAttributeAuto(program, location, "TEXCOORD0", buffer);
	}
	);
	m_attributesAuto.insert(std::pair<std::string, AttributeAuto>("TEXCOORD0", aa));

	// TEXCOORD1
	aa = AttributeAuto(
		[](GLuint program, const std::string& name) {
		return MaterialManager::_initShaderProgramAttributeAuto(program, name);
	},
		[](GLuint program, GLint location, OpenGLBuffer buffer) {
		MaterialManager::_renderShaderProgramAttributeAuto(program, location, "TEXCOORD1", buffer);
	}
	);
	m_attributesAuto.insert(std::pair<std::string, AttributeAuto>("TEXCOORD1", aa));

	// TEXCOORD2
	aa = AttributeAuto(
		[](GLuint program, const std::string& name) {
		return MaterialManager::_initShaderProgramAttributeAuto(program, name);
	},
		[](GLuint program, GLint location, OpenGLBuffer buffer) {
		MaterialManager::_renderShaderProgramAttributeAuto(program, location, "TEXCOORD2", buffer);
	}
	);
	m_attributesAuto.insert(std::pair<std::string, AttributeAuto>("TEXCOORD2", aa));

	// TEXCOORD3
	aa = AttributeAuto(
		[](GLuint program, const std::string& name) {
		return MaterialManager::_initShaderProgramAttributeAuto(program, name);
	},
		[](GLuint program, GLint location, OpenGLBuffer buffer) {
		MaterialManager::_renderShaderProgramAttributeAuto(program, location, "TEXCOORD3", buffer);
	}
	);
	m_attributesAuto.insert(std::pair<std::string, AttributeAuto>("TEXCOORD3", aa));

	// TEXCOORD4
	aa = AttributeAuto(
		[](GLuint program, const std::string& name) {
		return MaterialManager::_initShaderProgramAttributeAuto(program, name);
	},
		[](GLuint program, GLint location, OpenGLBuffer buffer) {
		MaterialManager::_renderShaderProgramAttributeAuto(program, location, "TEXCOORD4", buffer);
	}
	);
	m_attributesAuto.insert(std::pair<std::string, AttributeAuto>("TEXCOORD4", aa));


	/* *************

	UNIFORMS CONNUS

	************* */

	// WORLD MATRIX
	UniformAuto ua = UniformAuto(
		[](GLuint program, const std::string& name) {
		return MaterialManager::_initShaderProgramUniformAuto(program, name);
	},
		[](GLuint program, GLint location, const std::string& paramName, Scene* s, Object3D* obj, Camera* cam, int numSampler) {
		MaterialManager::_renderShaderProgramUniformAuto(program, location, paramName, "world_matrix", s, obj, cam);
	}
	);
	m_uniformsAuto.insert(std::pair<std::string, UniformAuto>("world_matrix", ua));

	// VIEW MATRIX
	ua = UniformAuto(
		[](GLuint program, const std::string& name) {
		return MaterialManager::_initShaderProgramUniformAuto(program, name);
	},
		[](GLuint program, GLint location, const std::string& paramName, Scene* s, Object3D* obj, Camera* cam, int numSampler) {
		MaterialManager::_renderShaderProgramUniformAuto(program, location, paramName, "view_matrix", s, obj, cam);
	}
	);
	m_uniformsAuto.insert(std::pair<std::string, UniformAuto>("view_matrix", ua));

	// PROJ MATRIX
	ua = UniformAuto(
		[](GLuint program, const std::string& name) {
		return MaterialManager::_initShaderProgramUniformAuto(program, name);
	},
		[](GLuint program, GLint location, const std::string& paramName, Scene* s, Object3D* obj, Camera* cam, int numSampler) {
		MaterialManager::_renderShaderProgramUniformAuto(program, location, paramName, "proj_matrix", s, obj, cam);
	}
	);
	m_uniformsAuto.insert(std::pair<std::string, UniformAuto>("proj_matrix", ua));

	// VIEWPROJ MATRIX
	ua = UniformAuto(
		[](GLuint program, const std::string& name) {
		return MaterialManager::_initShaderProgramUniformAuto(program, name);
	},
		[](GLuint program, GLint location, const std::string& paramName, Scene* s, Object3D* obj, Camera* cam, int numSampler) {
		MaterialManager::_renderShaderProgramUniformAuto(program, location, paramName, "viewproj_matrix", s, obj, cam);
	}
	);
	m_uniformsAuto.insert(std::pair<std::string, UniformAuto>("viewproj_matrix", ua));

	// WORLD VIEW MATRIX
	ua = UniformAuto(
		[](GLuint program, const std::string& name) {
		return MaterialManager::_initShaderProgramUniformAuto(program, name);
	},
		[](GLuint program, GLint location, const std::string& paramName, Scene* s, Object3D* obj, Camera* cam, int numSampler) {
		MaterialManager::_renderShaderProgramUniformAuto(program, location, paramName, "worldview_matrix", s, obj, cam);
	}
	);
	m_uniformsAuto.insert(std::pair<std::string, UniformAuto>("worldview_matrix", ua));

	// WORLDVIEWPROJ MATRIX
	ua = UniformAuto(
		[](GLuint program, const std::string& name) {
		return MaterialManager::_initShaderProgramUniformAuto(program, name);
	},
		[](GLuint program, GLint location, const std::string& paramName, Scene* s, Object3D* obj, Camera* cam, int numSampler) {
		MaterialManager::_renderShaderProgramUniformAuto(program, location, paramName, "worldviewproj_matrix", s, obj, cam);
	}
	);
	m_uniformsAuto.insert(std::pair<std::string, UniformAuto>("worldviewproj_matrix", ua));

	// CAMERA POSITION
	ua = UniformAuto(
		[](GLuint program, const std::string& name) {
		return MaterialManager::_initShaderProgramUniformAuto(program, name);
	},
		[](GLuint program, GLint location, const std::string& paramName, Scene* s, Object3D* obj, Camera* cam, int numSampler) {
		MaterialManager::_renderShaderProgramUniformAuto(program, location, paramName, "camera_position", s, obj, cam);
	}
	);
	m_uniformsAuto.insert(std::pair<std::string, UniformAuto>("camera_position", ua));


	// DIRECTIONAL LIGHT
	ua = UniformAuto(
		[](GLuint program, const std::string& name) {
		return MaterialManager::_initShaderProgramUniformAuto(program, name);
	},
		[](GLuint program, GLint location, const std::string& paramName, Scene* s, Object3D* obj, Camera* cam, int numSampler) {
		MaterialManager::_renderShaderProgramUniformAuto(program, 0, paramName, "directionlight", s, obj, cam);	// pour biaiser le système on force avec un 0
	}
	);
	m_uniformsAuto.insert(std::pair<std::string, UniformAuto>("directionlight", ua));

	// POINT LIGHTS
	ua = UniformAuto(
		[](GLuint program, const std::string& name) {
		return MaterialManager::_initShaderProgramUniformAuto(program, name);
	},
		[](GLuint program, GLint location, const std::string& paramName, Scene* s, Object3D* obj, Camera* cam, int numSampler) {
		MaterialManager::_renderShaderProgramUniformAuto(program, 0, paramName, "pointlights", s, obj, cam);	// pour biaiser le système on force avec un 0
	}
	);
	m_uniformsAuto.insert(std::pair<std::string, UniformAuto>("pointlights", ua));

	
	// LIGHTS COUNT
	ua = UniformAuto(
		[](GLuint program, const std::string& name) {
		return MaterialManager::_initShaderProgramUniformAuto(program, name);
	},
		[](GLuint program, GLint location, const std::string& paramName, Scene* s, Object3D* obj, Camera* cam, int numSampler) {
		MaterialManager::_renderShaderProgramUniformAuto(program, location, paramName, "pointlights_count", s, obj, cam);
	}
	);
	m_uniformsAuto.insert(std::pair<std::string, UniformAuto>("pointlights_count", ua));

	// SHADOWMAP
	ua = UniformAuto(
		[](GLuint program, const std::string& name) {
		return MaterialManager::_initShaderProgramUniformAuto(program, name);
	},
		[](GLuint program, GLint location, const std::string& paramName, Scene* s, Object3D* obj, Camera* cam, int numSampler) {
		MaterialManager::_renderShaderProgramUniformAuto(program, location, paramName, "shadow_map", s, obj, cam, numSampler);
	}
	);
	m_uniformsAuto.insert(std::pair<std::string, UniformAuto>("shadow_map", ua));




	/* *************

	SAMPLERS

	************* */
	Sampler s = Sampler(
		[](GLuint program, const std::string& name) {
		return MaterialManager::_initShaderProgramUniformAuto(program, name);
	},
		[](GLuint program, GLint location, Pass* pass, const std::string& textureName, int numSampler) {
		MaterialManager::_renderShaderProgramSampler(program, location, pass, textureName, numSampler);
	}
	);
	m_samplers.insert(std::pair<std::string, Sampler>("sampler", s));
}

GLint MaterialManager::_initShaderProgramAttributeAuto(GLuint program, const std::string& name)
{
	return glGetAttribLocation(program, name.c_str());
}

void MaterialManager::_renderShaderProgramAttributeAuto(GLuint program, GLint location, const std::string& paramAutoName, OpenGLBuffer buffer)
{
	BufferInfo* bi = nullptr;

	if (paramAutoName == "POSITION")
		bi = buffer.mVertexBuffer;
	else if (paramAutoName == "NORMAL")
		bi = buffer.mNormalBuffer;
	else if (paramAutoName == "TANGENT")
		bi = buffer.mTangentBuffer;
	else if (paramAutoName == "BINORMAL")
		bi = buffer.mBinormalBuffer;
	else if (paramAutoName == "VERTEXCOLOR")
		bi = buffer.mColorBuffer;
	else if (paramAutoName == "TEXCOORD0")
		bi = (buffer.mUvsBuffer.size() > 0) ? buffer.mUvsBuffer.at(0) : nullptr;
	else if (paramAutoName == "TEXCOORD1")
		bi = (buffer.mUvsBuffer.size() > 1) ? buffer.mUvsBuffer.at(1) : nullptr;
	else if (paramAutoName == "TEXCOOR2")
		bi = (buffer.mUvsBuffer.size() > 2) ? buffer.mUvsBuffer.at(2) : nullptr;
	else if (paramAutoName == "TEXCOORD3")
		bi = (buffer.mUvsBuffer.size() > 3) ? buffer.mUvsBuffer.at(3) : nullptr;
	else if (paramAutoName == "TEXCOORD4")
		bi = (buffer.mUvsBuffer.size() > 4) ? buffer.mUvsBuffer.at(4) : nullptr;

	if (bi != nullptr && bi->numItems > 0)
	{
		glBindBuffer(GL_ARRAY_BUFFER, bi->id);
		glVertexAttribPointer(location, bi->itemSize, GL_FLOAT, false, 0, 0);
		glEnableVertexAttribArray(location);
	}
}

GLint MaterialManager::_initShaderProgramUniformAuto(GLuint program, const std::string& name)
{
	return glGetUniformLocation(program, name.c_str());
}

void MaterialManager::_renderShaderProgramUniformAuto(GLuint program, GLint location, const std::string& paramName, const std::string& paramUniformName, Scene* s, Object3D* obj, Camera* cam, int numSampler)
{
	if (location < 0)
		return;

	Matrix4 worldMatrix = obj->getWorldMatrix();
	Matrix4 viewMatrix = cam->getWorldMatrix().inverse();
	Matrix4 projMatrix = cam->getProjectionMatrix();

	Matrix4 mat_tmp = Matrix4::IDENTITY;
	float real = 0.f;
	Vector3 vec3 = Vector3::ZERO;
	std::vector<PointLight*> pointlights;
	Light* directionalLight = nullptr;

	enum TypeData
	{
		MATRIX4,
		REAL,
		VECTOR3,
		DIRECTIONALLIGHT,
		POINTLIGHTS,
		SHADOWMAP
	};

	TypeData t = TypeData::MATRIX4;

	// Alors la liste est longue mais np
	if (paramUniformName == "world_matrix")
		mat_tmp = worldMatrix;
	else if (paramUniformName == "view_matrix")
		mat_tmp = viewMatrix;
	else if (paramUniformName == "proj_matrix")
		mat_tmp = projMatrix;
	else if (paramUniformName == "viewproj_matrix")
		mat_tmp = projMatrix * viewMatrix;
	else if (paramUniformName == "worldview_matrix")
		mat_tmp = viewMatrix.concatenateAffine(worldMatrix);
	else if (paramUniformName == "worldviewproj_matrix")
		mat_tmp = projMatrix * (viewMatrix.concatenateAffine(worldMatrix));

	else if (paramUniformName == "camera_position")
	{
		vec3 = cam->getWorldPosition();
		t = TypeData::VECTOR3;
	}
	else if (paramUniformName == "pointlights")
	{
		pointlights = s->getPointLights();
		real = pointlights.size();
		t = TypeData::POINTLIGHTS;
	}
	else if (paramUniformName == "pointlights_count")
	{
		real = s->getPointLights().size();
		t = TypeData::REAL;
	}
	else if (paramUniformName == "directionlight")
	{
		directionalLight = s->getDirectionalLight();
		t = TypeData::DIRECTIONALLIGHT;
	}
	else if (paramUniformName == "shadow_map")
	{
		directionalLight = s->getDirectionalLight();
		t = TypeData::SHADOWMAP;
	}

	switch (t)
	{
	case TypeData::MATRIX4:
	{
		float arr[16];
		mat_tmp.toArray(arr);
		glUniformMatrix4fv(location, 1, GL_FALSE, arr);
		break;
	}
	case TypeData::VECTOR3:
	{
		glUniform3f(location, vec3.x, vec3.y, vec3.z);
		break;
	}
	case TypeData::REAL:
	{
		glUniform1f(location, real);
		break;
	}
	case TypeData::DIRECTIONALLIGHT:
	{
		if (directionalLight == nullptr)
		{
			glUniform1i(glGetUniformLocation(program, "uHasDirectionalLight"), false);
			break;
		}

		glUniform1i(glGetUniformLocation(program, "uHasDirectionalLight"), true);

		Vector3 pos = directionalLight->getWorldPosition();
		Color ambient = directionalLight->m_ambient;
		Color diffuse = directionalLight->m_diffuse;
		Color specular = directionalLight->m_specular;

		// Position
		glUniform3f(glGetUniformLocation(program, (paramName + ".position").c_str()), pos.x, pos.y, pos.z);

		// Light color
		glUniform3f(glGetUniformLocation(program, (paramName + ".ambient").c_str()), ambient.getRed(), ambient.getGreen(), ambient.getBlue());
		glUniform3f(glGetUniformLocation(program, (paramName + ".diffuse").c_str()), diffuse.getRed(), diffuse.getGreen(), diffuse.getBlue());
		glUniform3f(glGetUniformLocation(program, (paramName + ".specular").c_str()), specular.getRed(), specular.getGreen(), specular.getBlue());

		break;
	}
	case TypeData::POINTLIGHTS:
	{
		int i = 0;
		for (auto it = pointlights.begin(); it != pointlights.end(); ++it)
		{
			PointLight* pl = *it;

			Vector3 pos = pl->getWorldPosition();
			Color ambient = pl->m_ambient;
			Color diffuse = pl->m_diffuse;
			Color specular = pl->m_specular;
			float constant = pl->m_constant;
			float linear = pl->m_linear;
			float quadratic = pl->m_quadratic;

			// Position
			glUniform3f(glGetUniformLocation(program, (paramName + "[" + std::to_string(i) + "].position").c_str()), pos.x, pos.y, pos.z);

			// Light color
			glUniform3f(glGetUniformLocation(program, (paramName + "[" + std::to_string(i) + "].ambient").c_str()), ambient.getRed(), ambient.getGreen(), ambient.getBlue());
			glUniform3f(glGetUniformLocation(program, (paramName + "[" + std::to_string(i) + "].diffuse").c_str()), diffuse.getRed(), diffuse.getGreen(), diffuse.getBlue());
			glUniform3f(glGetUniformLocation(program, (paramName + "[" + std::to_string(i) + "].specular").c_str()), specular.getRed(), specular.getGreen(), specular.getBlue());
			
			// Light variable
			glUniform1f(glGetUniformLocation(program, (paramName + "[" + std::to_string(i) + "].constant").c_str()), constant);
			glUniform1f(glGetUniformLocation(program, (paramName + "[" + std::to_string(i) + "].linear").c_str()), linear);
			glUniform1f(glGetUniformLocation(program, (paramName + "[" + std::to_string(i) + "].quadratic").c_str()), quadratic);

			++i;
		}

		break;
	}
	case TypeData::SHADOWMAP:
	{
		if (directionalLight == nullptr || numSampler < 0 || !obj->canReceiveShadow())
			return;

		GLint spaceLocation = glGetUniformLocation(program, "uLightSpaceMatrix");
		GLint samplerShadowLocation = glGetUniformLocation(program, paramName.c_str());

		float arr[16];

		// On envoit la depth map
		_renderSampler(samplerShadowLocation, directionalLight->getDepthMapTexture(), numSampler);

		// On envoit le reste des uniforms
		Matrix4 lightProjMat = directionalLight->getProjectionLight();
		Matrix4 spaceMatrix = lightProjMat * Matrix4().lookAt(directionalLight->getWorldPosition(), Vector3(0.0, 0.0, 0.0), Vector3(0.0, 1.0, 0.0));
		spaceMatrix.toArray(arr);
		glUniformMatrix4fv(spaceLocation, 1, GL_FALSE, arr);

		break;
	}
}
}

void MaterialManager::_renderShaderProgramSampler(GLuint program, GLint location, Pass* pass, const std::string& textureName, int numSampler)
{
	Texture* t = pass->getTexture(textureName);

	if (t == nullptr)
		return;

	_renderSampler(location, t->mGLuid, numSampler);
}

void MaterialManager::_renderSampler(GLint location, GLuint idTexture, int numSampler)
{
	switch (numSampler)
	{
	case 0: glActiveTexture(GL_TEXTURE0); break;
	case 1: glActiveTexture(GL_TEXTURE1); break;
	case 2: glActiveTexture(GL_TEXTURE2); break;
	case 3: glActiveTexture(GL_TEXTURE3); break;
	case 4: glActiveTexture(GL_TEXTURE4); break;
	case 5: glActiveTexture(GL_TEXTURE5); break;
	default: return;
	}

	glBindTexture(GL_TEXTURE_2D, idTexture);
	glUniform1i(location, numSampler);
}

void MaterialManager::_renderShaderProgramUniformNoAuto(GLuint program, GLint location, const std::vector<float>& values)
{
	switch (values.size())
	{
	case 0:
		return;
	case 1:
		glUniform1f(location, values.at(0));
		break;
	case 2:
		glUniform2f(location, values.at(0), values.at(1));
		break;
	case 3:
		glUniform3f(location, values.at(0), values.at(1), values.at(2));
		break;
	case 4:
		glUniform4f(location, values.at(0), values.at(1), values.at(2), values.at(3));
		break;
	default:
		glUniform1fv(location, values.size(), values.data());
	}


}