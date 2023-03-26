#pragma once

#include <GBC.h>

namespace gbc
{
	class EditorLayer : public Layer
	{
	public:
		virtual auto OnAttach() -> void override;
		virtual auto OnDetach() -> void override;
		virtual auto OnUpdate(Timestep timestep) -> void override;
		virtual auto OnImGuiRender() -> void override;
		virtual auto OnEvent(Event& event) -> void override;
	private:
		auto OnWindowFramebufferResizeEvent(WindowFramebufferResizeEvent& event) -> void;
	private:
		// TODO: move to Renderer2D or something.
		Ref<Shader> m_Shader;
		Ref<VertexArray> m_VertexArray;
	};
}
