#include "EditorLayer.h"
#include "GBC/Rendering/Renderer.h"
#include <imgui.h>
#include <glm/gtx/transform.hpp>

namespace gbc
{
	auto EditorLayer::OnAttach() -> void
	{
		Renderer::Init();

		m_Shader = Shader::CreateRef({{
			{ShaderType_Vertex, io::ReadFile("Resources/Shaders/Shader.vert.glsl")},
			{ShaderType_Fragment, io::ReadFile("Resources/Shaders/Shader.frag.glsl")},
		}});

		m_VertexArray = VertexArray::CreateRef();

		float vertices[]
		{
			-0.5f, -0.5f, // bottom left
			+0.5f, -0.5f, // bottom right
			 0.0f, +0.5f, // top center
		};
		VertexBufferInfo vbInfo;
		vbInfo.layout = {
			{VertexBufferElementType_Float2, "i_Position"}
		};
		vbInfo.data = vertices;
		vbInfo.size = sizeof(vertices);
		vbInfo.usage = BufferUsage_StaticDraw;
		m_VertexArray->SetVertexBuffer(VertexBuffer::CreateRef(vbInfo));

		uint8_t indices[]
		{
			0, 1, 2, // triangle 0
		};
		IndexBufferInfo ibInfo;
		ibInfo.type = IndexBufferElementType_UInt8;
		ibInfo.data = indices;
		ibInfo.count = sizeof(indices) / sizeof(*indices);
		ibInfo.usage = BufferUsage_StaticDraw;
		m_VertexArray->SetIndexBuffer(IndexBuffer::CreateRef(ibInfo));
	}

	auto EditorLayer::OnDetach() -> void
	{
		Renderer::Shutdown();
	}

	static float time{0.0f};
	static bool up{true};
	auto EditorLayer::OnUpdate(Timestep timestep) -> void
	{
		if (up)
		{
			time += timestep;
			if (time >= 1.0f)
				up = false;
		}
		else
		{
			time -= timestep;
			if (time <= 0.0f)
				up = true;
		}

		auto& window{Application::Get().GetWindow()};
		glm::vec2 mousePos{Input::GetRelativeMousePos(window)};
		mousePos /= window.GetSize();
		mousePos = glm::clamp(mousePos, 0.0f, 1.0f);

		RenderCommand::SetClearColor({mousePos, time, 1.0f});
		RenderCommand::Clear();

		Renderer::BeginScene(glm::inverse(glm::translate(glm::vec3{mousePos.x, 1.0f - mousePos.y, 1.0f})));
		Renderer::Submit(m_VertexArray, m_Shader);
		Renderer::EndScene();
	}

	auto EditorLayer::OnImGuiRender() -> void
	{
		ImGui::ShowDemoWindow();
	}

	auto EditorLayer::OnEvent(Event& event) -> void
	{
		event.Dispatch(this, &EditorLayer::OnWindowFramebufferResizeEvent);
	}

	auto EditorLayer::OnWindowFramebufferResizeEvent(WindowFramebufferResizeEvent& event) -> void
	{
		RenderCommand::SetViewport({0, 0}, event.GetFramebufferSize());
	}
}
