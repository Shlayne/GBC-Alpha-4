#include "gbcpch.h"
#include "RendererAPI.h"
#include "Platform/Renderer/OpenGL/OpenGLRendererAPI.h"

namespace gbc
{
	auto RendererAPI::CreateScope() -> Scope<RendererAPI>
	{
		GBC_CORE_ASSERT_BOUNDED_ENUM_IS_VALID(RendererAPI, RendererAPI::GetType());
		constexpr Scope<RendererAPI>(*createScopeFuncs[])()
		{
			[]() -> Scope<RendererAPI> { return gbc::CreateScope<OpenGLRendererAPI>(); }
		};
		return createScopeFuncs[RendererAPI::GetType() - RendererAPI::Begin]();
	}
}
