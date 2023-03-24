#pragma once

#include "GBC/Core/Core.h"
#include "GBC/Rendering/VertexArray.h"

namespace gbc
{
	class Renderer
	{
	public:
		static auto BeginScene() -> void;
		static auto EndScene() -> void;

		static auto Submit(const Ref<VertexArray>& vertexArray) -> void;
	};
}
