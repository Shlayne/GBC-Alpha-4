#pragma once

#include "GBC/Core/Core.h"
#include "GBC/Rendering/VertexArray.h"
#include <glm/glm.hpp>

namespace gbc
{
	GBC_DEFINE_BOUNDED_ENUM(
		RendererPrimitive, uint8_t,

		// OpenGL, Vulkan, Direct3D, and Metal support these
		Triangles,
		Lines,
		Points,
		TriangleStrip,
		LineStrip,

		// OpenGL, Vulkan, and Direct3D support these
		TrianglesAdjacency,
		LinesAdjacency,
		TriangleStripAdjacency,
		LineStripAdjacency,

		// OpenGL and Vulkan support these
		TriangleFan,
		LineLoop
	);

	GBC_DEFINE_MASKED_ENUM(
		ClearBuffer, uint8_t,

		Color   = 1 << 0,
		Depth   = 1 << 1,
		Stencil = 1 << 2
	);

	class RendererAPI
	{
	public:
		GBC_DEFINE_BOUNDED_CLASS_ENUM(
			RendererAPI, uint8_t,

			OpenGL,
			Vulkan
		);
	public:
		static inline auto GetType() -> uint8_t { return s_Type; }
	public:
		virtual auto SetClearColor(glm::vec4 color) -> void = 0;
		virtual auto Clear(ClearBuffer clearBuffer) -> void = 0;

		virtual auto SetViewport(glm::ivec2 position, glm::ivec2 size) -> void = 0;

		virtual auto DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t offset, uint32_t count, RendererPrimitive primitive) -> void = 0;
	private:
		static inline uint8_t s_Type{OpenGL}; // TODO: choose
	private:
		friend class RenderCommand;
		static auto CreateScope() -> Scope<RendererAPI>;
	};
}
