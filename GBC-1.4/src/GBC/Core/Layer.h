#pragma once

#include "GBC/Event/Event.h"

namespace gbc
{
	class Layer
	{
	public:
		virtual ~Layer() = default;
		virtual auto OnAttach() -> void {}
		virtual auto OnDetach() -> void {}
		virtual auto OnUpdate(float timestep) -> void {}
		virtual auto OnEvent(Event& event) -> void {}
	};
}
