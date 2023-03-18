#include "gbcpch.h"
#include "Context.h"
#include "Platform/Renderer/OpenGL/OpenGLContext.h"

namespace gbc
{
	auto Context::CreateScope(void* nativeWindow) -> Scope<Context>
	{
		// TODO: check RendererAPI::API
		return gbc::CreateScope<OpenGLContext>(nativeWindow);
	}
}
