#pragma once

#include "GBC/Rendering/RendererAPI.h"

namespace gbc
{
	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		virtual auto SetClearColor(glm::vec4 color) -> void override;
		virtual auto Clear() -> void override;

		virtual auto SetViewport(glm::ivec2 position, glm::ivec2 size) -> void override;

		virtual auto DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t offset, uint32_t count, RendererPrimitive primitive) -> void override;
	};
}
