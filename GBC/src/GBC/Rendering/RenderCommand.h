#pragma once

#include "GBC/Core/Core.h"
#include "GBC/Rendering/RendererAPI.h"

namespace gbc
{
	class RenderCommand
	{
	public:
		static inline auto SetClearColor(glm::vec4 color) -> void { s_API->SetClearColor(color); }
		static inline auto Clear(ClearBuffer clearBuffer = ClearBuffer::Mask) -> void { s_API->Clear(clearBuffer); }

		static inline auto SetViewport(glm::ivec2 position, glm::ivec2 size) -> void { s_API->SetViewport(position, size); }

		static inline auto DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t offset = 0, uint32_t count = 0, RendererPrimitive primitive = RendererPrimitive::Triangles) -> void { s_API->DrawIndexed(vertexArray, offset, count, primitive); }
	private:
		// TODO: this shouldn't be static. :/
		// Its lifetime should not be the duration of the process, but of the application.
		static inline Scope<RendererAPI> s_API{RendererAPI::CreateScope()};
	};
}
