#include "EditorLayer.h"
#include <imgui.h>

namespace gbc
{
	auto EditorLayer::OnAttach() -> void
	{

	}

	auto EditorLayer::OnDetach() -> void
	{

	}

	auto EditorLayer::OnUpdate(Timestep timestep) -> void
	{

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
