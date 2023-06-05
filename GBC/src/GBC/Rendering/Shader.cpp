#include "gbcpch.h"
#include "Shader.h"
#include "GBC/Rendering/RendererAPI.h"
#include "Platform/Renderer/OpenGL/OpenGLShader.h"

namespace gbc
{
	auto Shader::CreateRef(const ShaderInfo& info) -> Ref<Shader>
	{
		GBC_CORE_ASSERT_BOUNDED_ENUM_IS_VALID(RendererAPI, RendererAPI::GetType());
		constexpr Ref<Shader>(*createRefFuncs[])(const ShaderInfo&)
		{
			[](const ShaderInfo& info) -> Ref<Shader> { return gbc::CreateRef<OpenGLShader>(info); }
		};
		return createRefFuncs[RendererAPI::GetType() - RendererAPI::Begin](info);
	}
}
