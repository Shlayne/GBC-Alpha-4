#pragma once

#include "GBC/Rendering/Context.h"
#define GLFW_INCLUDE_NONE
#include <glfw/glfw3.h>

namespace gbc
{
	class OpenGLContext : public Context
	{
	public:
		OpenGLContext(void* nativeWindow);
	public:
		virtual auto SwapBuffers() -> void override;
	private:
		GLFWwindow* m_Handle;
	};
}
