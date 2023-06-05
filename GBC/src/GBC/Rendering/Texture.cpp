#include "gbcpch.h"
#include "Texture.h"
#include "GBC/Rendering/RendererAPI.h"
#include "Platform/Renderer/OpenGL/OpenGLTexture.h"

namespace gbc
{
	auto Texture2D::CreateRef(const Texture2DInfo& info) -> Ref<Texture2D>
	{
		GBC_CORE_ASSERT_BOUNDED_ENUM_IS_VALID(RendererAPI, RendererAPI::GetType());
		constexpr Ref<Texture2D>(*createRefFuncs[])(const Texture2DInfo&)
		{
			[](const Texture2DInfo& info) -> Ref<Texture2D> { return gbc::CreateRef<OpenGLTexture2D>(info); }
		};
		return createRefFuncs[RendererAPI::GetType() - RendererAPI::Begin](info);
	}
}
