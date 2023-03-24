#include "gbcpch.h"
#include "OpenGLContext.h"
#define GLFW_INCLUDE_NONE
#include <glfw/glfw3.h>
#include <glad/glad.h>

namespace gbc
{
	OpenGLContext::OpenGLContext(const ContextInfo& info)
		: m_Handle{static_cast<GLFWwindow*>(info.nativeWindow)}
	{
		// TODO: profile function
		glfwMakeContextCurrent(m_Handle);
		GBC_CORE_VERIFY(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress), "Failed to initialize GLAD.");
	}

	auto OpenGLContext::SwapBuffers() -> void
	{
		glfwSwapBuffers(m_Handle);
	}
}
