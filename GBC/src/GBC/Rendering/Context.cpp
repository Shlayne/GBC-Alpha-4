#include "gbcpch.h"
#include "Context.h"
#include "GBC/Rendering/RendererAPI.h"
#include "Platform/Renderer/OpenGL/OpenGLContext.h"

namespace gbc
{
	auto Context::CreateScope(const ContextInfo& info) -> Scope<Context>
	{
		GBC_CORE_ASSERT_BOUNDED_ENUM_IS_VALID(RendererAPI, RendererAPI::GetType());
		constexpr Scope<Context>(*createScopeFuncs[])(const ContextInfo&)
		{
			[](const ContextInfo& info) -> Scope<Context> { return gbc::CreateScope<OpenGLContext>(info); }
		};
		return createScopeFuncs[RendererAPI::GetType() - RendererAPI::Begin](info);
	}
}
