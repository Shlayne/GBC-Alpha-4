#include "gbcpch.h"
#include "Renderer.h"
#include "GBC/Rendering/RenderCommand.h"

namespace gbc
{
	struct
	{
		Ref<UniformBuffer> cameraUniformBuffer;
	} static s_RendererData;

	struct CameraBuffer
	{
		glm::mat4 viewProjection{1.0f};
	};

	auto Renderer::Init() -> void
	{
		UniformBufferInfo ubInfo;
		ubInfo.binding = 0;
		ubInfo.data = nullptr;
		ubInfo.size = sizeof(CameraBuffer);
		ubInfo.usage = BufferUsage::DynamicDraw;
		s_RendererData.cameraUniformBuffer = UniformBuffer::CreateRef(ubInfo);
	}

	auto Renderer::Shutdown() -> void
	{
		s_RendererData = {};
	}

	auto Renderer::BeginScene(const glm::mat4& viewProjection) -> void
	{
		CameraBuffer cameraBuffer;
		cameraBuffer.viewProjection = viewProjection;
		s_RendererData.cameraUniformBuffer->SetData(&cameraBuffer, sizeof(CameraBuffer));
	}

	auto Renderer::EndScene() -> void
	{

	}

	auto Renderer::Submit(const Ref<VertexArray>& vertexArray, const Ref<Shader>& shader) -> void
	{
		shader->Bind();
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}
