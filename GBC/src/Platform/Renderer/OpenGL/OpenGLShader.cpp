#include "gbcpch.h"
#include "OpenGLShader.h"
#include <glad/glad.h>

namespace gbc
{
	auto ConvertShaderTypeToOpenGL(ShaderType type) -> GLuint;
#if GBC_ENABLE_LOGGING
	auto ConvertShaderTypeToName(ShaderType type) -> const char*;
#endif
	auto CompileShaderSource(GLint& success, const ShaderSource& source) -> GLuint;
	auto CreateProgram(const std::vector<ShaderSource>& sources) -> GLuint;

	OpenGLShader::OpenGLShader(const ShaderInfo& info)
	{
		m_RendererID = CreateProgram(info.sources);
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_RendererID);
	}

	auto OpenGLShader::Bind() const -> void
	{
		glUseProgram(m_RendererID);
	}

	auto ConvertShaderTypeToOpenGL(ShaderType type) -> GLuint
	{
		switch (type)
		{
			case ShaderType_Vertex:                 return GL_VERTEX_SHADER;
			case ShaderType_TessellationControl:    return GL_TESS_CONTROL_SHADER;
			case ShaderType_TessellationEvaluation: return GL_TESS_EVALUATION_SHADER;
			case ShaderType_Geometry:               return GL_GEOMETRY_SHADER;
			case ShaderType_Fragment:               return GL_FRAGMENT_SHADER;
			case ShaderType_Compute:                return GL_COMPUTE_SHADER;
		}

		GBC_CORE_ASSERT(false, "Unknown ShaderType.");
		return 0;
	}

#if GBC_ENABLE_LOGGING
	auto ConvertShaderTypeToName(ShaderType type) -> const char*
	{
		switch (type)
		{
			case ShaderType_Vertex:                 return "vertex";
			case ShaderType_TessellationControl:    return "tessellation control";
			case ShaderType_TessellationEvaluation: return "tessellation evaluation";
			case ShaderType_Geometry:               return "geometry";
			case ShaderType_Fragment:               return "fragment";
			case ShaderType_Compute:                return "compute";
		}

		GBC_CORE_ASSERT(false, "Unknown ShaderType.");
		return nullptr;
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
