#pragma once

#include "GBC/Core/Layer.h"

namespace gbc
{
	class ImGuiOverlay : public Layer
	{
	public:
		virtual auto OnAttach() -> void override;
		virtual auto OnDetach() -> void override;
		virtual auto OnEvent(Event& event) -> void override;
	public:
		auto Begin() -> void;
		auto End() -> void;

		inline auto SetBlockEvents(bool blockEvents) noexcept { m_BlockingEvents = blockEvents; }
	private:
		bool m_BlockingEvents{false};
	};
}
