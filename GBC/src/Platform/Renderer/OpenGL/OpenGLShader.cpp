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
		GBC_CORE_ASSERT_BOUNDED_ENUM_IS_VALID(ShaderType, type);
		constexpr GLuint types[]
		{
			GL_VERTEX_SHADER,          // ShaderType::Vertex
			GL_TESS_CONTROL_SHADER,    // ShaderType::TessellationControl
			GL_TESS_EVALUATION_SHADER, // ShaderType::TessellationEvaluation
			GL_GEOMETRY_SHADER,        // ShaderType::Geometry
			GL_FRAGMENT_SHADER,        // ShaderType::Fragment
			GL_COMPUTE_SHADER,         // ShaderType::Compute
		};
		return types[type - ShaderType::Begin];
	}

#if GBC_ENABLE_LOGGING
	auto ConvertShaderTypeToName(ShaderType type) -> const char*
	{
		GBC_CORE_ASSERT_BOUNDED_ENUM_IS_VALID(ShaderType, type);
		constexpr const char* names[]
		{
			"vertex",                  // ShaderType::Vertex
			"tessellation control",    // ShaderType::TessellationControl
			"tessellation evaluation", // ShaderType::TessellationEvaluation
			"geometry",                // ShaderType::Geometry
			"fragment",                // ShaderType::Fragment
			"compute",                 // ShaderType::Compute
		};
		return names[type - ShaderType::Begin];
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
			GLint length{};
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
		for (auto it{sources.begin()}; success != GL_FALSE && it != sources.end(); ++it)
			glAttachShader(program, shaders.emplace_back(CompileShaderSource(success, *it)));

		if (success != GL_FALSE)
		{
			glLinkProgram(program);
			glGetProgramiv(program, GL_LINK_STATUS, &success);
			if (success == GL_FALSE)
			{
#if GBC_ENABLE_LOGGING
				GLint length{};
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
					GLint length{};
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
