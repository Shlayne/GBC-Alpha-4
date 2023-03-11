#pragma once

#include "GBC/Core/Layer.h"

namespace gbc
{
	class EditorLayer : public Layer
	{
	public:
		virtual auto OnAttach() -> void override;
		virtual auto OnDetach() -> void override;
		virtual auto OnUpdate(float timestep) -> void override;
		virtual auto OnEvent(Event& event) -> void override;
	};
}
