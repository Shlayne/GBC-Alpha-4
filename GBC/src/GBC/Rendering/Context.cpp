#include "gbcpch.h"
#include "Context.h"
#include "GBC/Rendering/RendererAPI.h"
#include "Platform/Renderer/OpenGL/OpenGLContext.h"

namespace gbc
{
	auto Context::CreateScope(const ContextInfo& info) -> Scope<Context>
	{
		switch (RendererAPI::GetType())
		{
			case RendererAPI_OpenGL: return gbc::CreateScope<OpenGLContext>(info);
		}

		GBC_CORE_ASSERT(false, "Unknown RendererAPI.");
		return nullptr;
	}
}
