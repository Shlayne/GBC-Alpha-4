#include "EditorLayer.h"
#include "GBC/Rendering/Shader.h"
#include <imgui.h>

namespace gbc
{
	auto EditorLayer::OnAttach() -> void
	{
		auto shader = Shader::CreateRef({{
			{ShaderType_Vertex, R"(
				#version 450 core

				layout(location = 0) in vec3 a_Position;

				layout(location = 0) out vec3 o_Position;

				void main()
				{
					o_Position = a_Position;
					gl_Position = vec4(a_Position, 1.0);
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
	}

	auto EditorLayer::OnDetach() -> void
	{

	}

	auto EditorLayer::OnUpdate(Timestep timestep) -> void
	{
		GBC_TRACE("{} {}", Input::GetRelativeMousePos().x, Input::GetRelativeMousePos().y);
	}

	auto EditorLayer::OnImGuiRender() -> void
	{
		// NOTE: the window is currently not being cleared, so it looks ew
		ImGui::ShowDemoWindow();
	}

	auto EditorLayer::OnEvent(Event& event) -> void
	{

	}
}
