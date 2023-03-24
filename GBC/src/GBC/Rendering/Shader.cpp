#include "gbcpch.h"
#include "Shader.h"
#include "GBC/Rendering/RendererAPI.h"
#include "Platform/Renderer/OpenGL/OpenGLShader.h"

namespace gbc
{
	auto Shader::CreateRef(const ShaderInfo& info) -> Ref<Shader>
	{
		switch (RendererAPI::GetType())
		{
			case RendererAPI_OpenGL: return gbc::CreateScope<OpenGLShader>(info);
		}

		GBC_CORE_ASSERT(false, "Unknown RendererAPI.");
		return nullptr;
	}
}
