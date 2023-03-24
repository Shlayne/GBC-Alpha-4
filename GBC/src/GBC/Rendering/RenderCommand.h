#pragma once

#include "GBC/Core/Core.h"
#include "GBC/Rendering/RendererAPI.h"

namespace gbc
{
	class RenderCommand
	{
	public:
		static inline auto SetClearColor(const glm::vec4& color) -> void { s_API->SetClearColor(color); }
		static inline auto Clear() -> void { s_API->Clear(); }

		static inline auto DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t offset = 0, uint32_t count = 0, RendererPrimitive primitive = RendererPrimitive_Triangles) -> void { s_API->DrawIndexed(vertexArray, offset, count, primitive); }
	private:
		static inline Scope<RendererAPI> s_API{RendererAPI::CreateScope()};
	};
}
