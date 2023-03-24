#include "gbcpch.h"
#include "RendererAPI.h"
#include "Platform/Renderer/OpenGL/OpenGLRendererAPI.h"

namespace gbc
{
	auto RendererAPI::CreateScope() -> Scope<RendererAPI>
	{
		switch (RendererAPI::GetType())
		{
			case RendererAPI_OpenGL: return gbc::CreateScope<OpenGLRendererAPI>();
		}

		GBC_CORE_ASSERT(false, "Unknown RendererAPI.");
		return nullptr;
	}
}
