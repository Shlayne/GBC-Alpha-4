#pragma once

#include "GBC/Event/Event.h"
#include "GBC/Core/Timestep.h"

namespace gbc
{
	class Window;

	class Layer
	{
	public:
		constexpr Layer(bool enabled = true) : m_Enabled{enabled} {}
		virtual ~Layer() = default;
	public:
		virtual auto OnAttach() -> void {}
		virtual auto OnDetach() -> void {}
		virtual auto OnUpdate(Timestep timestep) -> void {}
		virtual auto OnImGuiRender() -> void {}
		virtual auto OnEvent(Event& event) -> void {}
	public:
		inline auto IsEnabled() const noexcept -> bool { return m_Enabled; }
		inline auto SetEnabled(bool enabled) noexcept -> void { m_Enabled = enabled; }
	private:
		bool m_Enabled;
	};
}
