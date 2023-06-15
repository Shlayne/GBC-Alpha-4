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
			{ShaderType::Vertex, io::ReadFile("Resources/Shaders/Shader.vert.glsl")},
			{ShaderType::Fragment, io::ReadFile("Resources/Shaders/Shader.frag.glsl")},
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
			{VertexBufferElementType::Float2, "i_Position"}
		};
		vbInfo.data = vertices;
		vbInfo.size = sizeof(vertices);
		vbInfo.usage = BufferUsage::StaticDraw;
		m_VertexArray->SetVertexBuffer(VertexBuffer::CreateRef(vbInfo));

		uint8_t indices[]
		{
			0, 1, 2, // triangle 0
		};
		IndexBufferInfo ibInfo;
		ibInfo.type = IndexBufferElementType::UInt8;
		ibInfo.data = indices;
		ibInfo.count = sizeof(indices) / sizeof(*indices);
		ibInfo.usage = BufferUsage::StaticDraw;
		m_VertexArray->SetIndexBuffer(IndexBuffer::CreateRef(ibInfo));
	}

	auto EditorLayer::OnDetach() -> void
	{
		Renderer::Shutdown();
	}

	static float time{};
	auto EditorLayer::OnUpdate(Timestep timestep) -> void
	{
		time = std::fmod(time + timestep, 1.0f);

		auto& window{Application::Get().GetWindow()};
		glm::vec2 mousePos{Input::GetRelativeMousePos(window)};
		mousePos /= glm::vec2{window.GetWidth(), window.GetHeight()};
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
		event.Dispatch(this, &EditorLayer::OnKeyPressEvent);
	}

	auto EditorLayer::OnWindowFramebufferResizeEvent(WindowFramebufferResizeEvent& event) -> void
	{
		RenderCommand::SetViewport({0, 0}, {event.GetFramebufferWidth(), event.GetFramebufferHeight()});
	}

	auto EditorLayer::OnKeyPressEvent(KeyPressEvent& event) -> void
	{
		// TODO: this would be set via a graphic settings button.
		if (event.GetKeycode() == Keycode::F11)
		{
			auto& window{Application::Get().GetWindow()};
			switch (window.GetWindowMode())
			{
			case WindowMode::Windowed:
				window.SetWindowMode(WindowMode::Fullscreen);
				break;
			case WindowMode::Fullscreen:
				window.SetWindowMode(WindowMode::BorderlessWindowed);
				break;
			case WindowMode::BorderlessWindowed:
				window.SetWindowMode(WindowMode::Windowed);
				break;
			}
		}
	}
}
