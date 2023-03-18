#include "gbcpch.h"
#include "Shader.h"
#include "Platform/Renderer/OpenGL/OpenGLShader.h"

namespace gbc
{
	auto Shader::CreateRef(const ShaderInfo& info) -> Ref<Shader>
	{
		// TODO: check RendererAPI::API
		return gbc::CreateRef<OpenGLShader>(info);
	}
}
