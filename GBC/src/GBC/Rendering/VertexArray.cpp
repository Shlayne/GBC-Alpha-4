#include "gbcpch.h"
#include "VertexArray.h"
#include "GBC/Rendering/RendererAPI.h"
#include "Platform/Renderer/OpenGL/OpenGLVertexArray.h"

namespace gbc
{
	auto VertexArray::CreateRef() -> Ref<VertexArray>
	{
		GBC_CORE_ASSERT_BOUNDED_ENUM_IS_VALID(RendererAPI, RendererAPI::GetType());
		constexpr Ref<VertexArray>(*createRefFuncs[])()
		{
			[]() -> Ref<VertexArray> { return gbc::CreateRef<OpenGLVertexArray>(); }
		};
		return createRefFuncs[RendererAPI::GetType() - RendererAPI::Begin]();
	}
}
