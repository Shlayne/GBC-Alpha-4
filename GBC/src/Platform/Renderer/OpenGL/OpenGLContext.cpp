#include "gbcpch.h"
#include "OpenGLContext.h"
#define GLFW_INCLUDE_NONE
#include <glfw/glfw3.h>
#include <glad/glad.h>

namespace gbc
{
#if GBC_CONFIG_DEBUG
	auto OpenGLDebugMessage(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) -> void;
#endif

	OpenGLContext::OpenGLContext(const ContextInfo& info)
		: m_Handle{static_cast<GLFWwindow*>(info.nativeWindow)}
	{
		// TODO: profile function
		glfwMakeContextCurrent(m_Handle);
		GBC_CORE_VERIFY(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress), "Failed to initialize GLAD.");

#if GBC_CONFIG_DEBUG
		glEnable(GL_DEBUG_OUTPUT);
		glDebugMessageCallback(OpenGLDebugMessage, nullptr);
#endif
	}

	auto OpenGLContext::SwapBuffers() -> void
	{
		glfwSwapBuffers(m_Handle);
	}

#if GBC_CONFIG_DEBUG
	auto OpenGLDebugMessage(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) -> void
	{
		switch (severity)
		{
		case GL_DEBUG_SEVERITY_NOTIFICATION:
			GBC_CORE_TRACE("OpenGL({}): {}", source, message);
			break;
		case GL_DEBUG_SEVERITY_LOW:
			GBC_CORE_DEBUG("OpenGL({}): {}", source, message);
			break;
		case GL_DEBUG_SEVERITY_MEDIUM:
			GBC_CORE_WARN("OpenGL({}): {}", source, message);
			break;
		case GL_DEBUG_SEVERITY_HIGH:
			GBC_CORE_ERROR("OpenGL({}): {}", source, message);
			break;
		}
	}
#endif
}
