#include "gbcpch.h"
#include "VertexArray.h"
#include "GBC/Rendering/RendererAPI.h"
#include "Platform/Renderer/OpenGL/OpenGLVertexArray.h"

namespace gbc
{
	auto VertexArray::CreateRef() -> Ref<VertexArray>
	{
		switch (RendererAPI::GetType())
		{
			case RendererAPI_OpenGL: return gbc::CreateScope<OpenGLVertexArray>();
		}

		GBC_CORE_ASSERT(false, "Unknown RendererAPI.");
		return nullptr;
	}
}
