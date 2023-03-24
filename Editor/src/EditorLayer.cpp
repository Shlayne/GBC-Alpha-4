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
			{ShaderType_Vertex, R"(
				#version 450 core

				layout(location = 0) in vec3 i_Position;

				layout(std140, binding = 0) uniform Camera
				{
					mat4 viewProjection;
				};

				layout(location = 0) out vec3 o_Position;

				void main()
				{
					o_Position = i_Position;
					gl_Position = viewProjection * vec4(i_Position, 1.0);
				}
			)"},
			{ShaderType_Fragment, R"(
				#version 450 core

				layout(location = 0) in vec3 i_Position;

				layout(location = 0) out vec4 o_Color;

				void main()
				{
					o_Color = vec4(i_Position / 2.0 + 0.5, 1.0);
				}
			)"},
		}});

		m_VertexArray = VertexArray::CreateRef();

		float vertices[] = {
			-0.5f, -0.5f,  0.0f, // bottom left
			+0.5f, -0.5f,  0.0f, // bottom right
			 0.0f, +0.5f,  0.0f, // top center
		};
		VertexBufferInfo vbInfo;
		vbInfo.layout = {
			{ VertexBufferElementType_Float3, "i_Position" }
		};
		vbInfo.data = vertices;
		vbInfo.size = sizeof(vertices);
		vbInfo.usage = BufferUsage_StaticDraw;
		m_VertexArray->SetVertexBuffer(VertexBuffer::CreateRef(vbInfo));

		uint8_t indices[] = {
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

	}
}
