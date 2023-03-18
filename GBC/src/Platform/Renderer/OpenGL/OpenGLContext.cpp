#include "gbcpch.h"
#include "OpenGLContext.h"
#include <glad/glad.h>

namespace gbc
{
	OpenGLContext::OpenGLContext(void* nativeWindow)
		: m_Handle{static_cast<GLFWwindow*>(nativeWindow)}
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
