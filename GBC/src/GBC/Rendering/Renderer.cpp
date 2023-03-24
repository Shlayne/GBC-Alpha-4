#include "gbcpch.h"
#include "Renderer.h"
#include "GBC/Rendering/RenderCommand.h"

namespace gbc
{
	auto Renderer::BeginScene() -> void
	{

	}

	auto Renderer::EndScene() -> void
	{

	}

	auto Renderer::Submit(const Ref<VertexArray>& vertexArray) -> void
	{
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}
