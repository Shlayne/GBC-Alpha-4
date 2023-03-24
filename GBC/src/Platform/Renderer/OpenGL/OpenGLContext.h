#pragma once

#include "GBC/Rendering/Context.h"

struct GLFWwindow;

namespace gbc
{
	class OpenGLContext : public Context
	{
	public:
		OpenGLContext(const ContextInfo& info);
	public:
		virtual auto SwapBuffers() -> void override;
	private:
		GLFWwindow* m_Handle;
	};
}
