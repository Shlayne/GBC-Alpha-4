#include "gbcpch.h"
#include "Context.h"
#include "Platform/Renderer/OpenGL/OpenGLContext.h"

namespace gbc
{
	Scope<Context> Context::CreateScope(void* nativeWindow)
	{
		// TODO: check RendererAPI::API
		return gbc::CreateScope<OpenGLContext>(nativeWindow);
	}
}
