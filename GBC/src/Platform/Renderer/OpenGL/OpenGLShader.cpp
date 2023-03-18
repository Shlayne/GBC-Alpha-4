#include "gbcpch.h"
#include "OpenGLShader.h"
#include <glad/glad.h>

namespace gbc
{
	static auto ConvertShaderTypeToOpenGL(ShaderType type) -> GLuint;
#if GBC_ENABLE_LOGGING
	static auto ConvertShaderTypeToName(ShaderType type) -> const char*;
#endif
	static auto CompileShaderSource(GLint& success, const ShaderSource& source) -> GLuint;
	static auto CreateProgram(const std::vector<ShaderSource>& sources) -> GLuint;

	OpenGLShader::OpenGLShader(const ShaderInfo& info)
	{
		m_RendererID = CreateProgram(info.sources);
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_RendererID);
	}

	auto OpenGLShader::Bind() -> void
	{
		glUseProgram(m_RendererID);
	}

	auto ConvertShaderTypeToOpenGL(ShaderType type) -> GLuint
	{
		switch (type)
		{
		break;case ShaderType_Vertex:				  return GL_VERTEX_SHADER;
		break;case ShaderType_TessellationControl:	  return GL_TESS_CONTROL_SHADER;
		break;case ShaderType_TessellationEvaluation: return GL_TESS_EVALUATION_SHADER;
		break;case ShaderType_Geometry:				  return GL_GEOMETRY_SHADER;
		break;case ShaderType_Fragment:				  return GL_FRAGMENT_SHADER;
		break;case ShaderType_Compute:				  return GL_COMPUTE_SHADER;
		break;default:
			GBC_CORE_ASSERT(false, "Unknown ShaderType.");
			return 0;
		}
	}

#if GBC_ENABLE_LOGGING
	auto ConvertShaderTypeToName(ShaderType type) -> const char*
	{
		switch (type)
		{
		break;case ShaderType_Vertex:				  return "vertex";
		break;case ShaderType_TessellationControl:	  return "tessellation control";
		break;case ShaderType_TessellationEvaluation: return "tessellation evaluation";
		break;case ShaderType_Geometry:				  return "geometry";
		break;case ShaderType_Fragment:				  return "fragment";
		break;case ShaderType_Compute:				  return "compute";
		break;default:
			GBC_CORE_ASSERT(false, "Unknown ShaderType.");
			return nullptr;
		}
	}
#endif

	auto CompileShaderSource(GLint& success, const ShaderSource& source) -> GLuint
	{
		if (success == GL_FALSE) return 0;

		GLuint shader{glCreateShader(ConvertShaderTypeToOpenGL(source.type))};

		const GLchar* code{source.code.data()};
		glShaderSource(shader, 1, &code, nullptr);
		glCompileShader(shader);

		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (success == GL_FALSE)
		{
#if GBC_ENABLE_LOGGING
			GLint length{0};
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
			std::vector<GLchar> infoLog;
			infoLog.resize(length);
			glGetShaderInfoLog(shader, length, &length, infoLog.data());
			GBC_CORE_ERROR("Failed to compile {} shader source: {}", ConvertShaderTypeToName(source.type), infoLog.data());
#endif
			glDeleteShader(shader);
			shader = 0;
		}

		return shader;
	}

	auto CreateProgram(const std::vector<ShaderSource>& sources) -> GLuint
	{
		GLuint program{glCreateProgram()};
		GLint success{GL_TRUE};

		std::vector<GLuint> shaders;
		shaders.reserve(sources.size());
		for (auto it = sources.begin(); success != GL_FALSE && it != sources.end(); ++it)
			glAttachShader(program, shaders.emplace_back(CompileShaderSource(success, *it)));

		if (success != GL_FALSE)
		{
			glLinkProgram(program);
			glGetProgramiv(program, GL_LINK_STATUS, &success);
			if (success == GL_FALSE)
			{
#if GBC_ENABLE_LOGGING
				GLint length{0};
				glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
				std::vector<GLchar> infoLog;
				infoLog.resize(length);
				glGetProgramInfoLog(program, length, &length, infoLog.data());
				GBC_CORE_ERROR("Failed to link shader: {}", infoLog.data());
#endif
			}
			else
			{
				glValidateProgram(program);
				glGetProgramiv(program, GL_VALIDATE_STATUS, &success);
				if (success == GL_FALSE)
				{
#if GBC_ENABLE_LOGGING
					GLint length{0};
					glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
					std::vector<GLchar> infoLog;
					infoLog.resize(length);
					glGetProgramInfoLog(program, length, &length, infoLog.data());
					GBC_CORE_ERROR("Failed to validate shader: {}", infoLog.data());
#endif
				}
			}

			// Do this regardles of link or validate success.
			for (GLuint shader : shaders)
			{
				glDetachShader(program, shader);
				glDeleteShader(shader);
			}
		}

		if (success == GL_FALSE)
		{
			GBC_CORE_ERROR("Failed to create shader.");
			glDeleteProgram(program);
			program = 0;
		}

		return program;
	}
}
