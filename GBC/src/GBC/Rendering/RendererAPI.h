#pragma once

#include "GBC/Core/Core.h"
#include "GBC/Rendering/VertexArray.h"
#include <glm/glm.hpp>

namespace gbc
{
	using RendererPrimitive = uint8_t;
	enum : RendererPrimitive
	{
		RendererPrimitive_None,

		// OpenGL, Vulkan, Direct3D, and Metal support these
		RendererPrimitive_Triangles,
		RendererPrimitive_Lines,
		RendererPrimitive_Points,
		RendererPrimitive_TriangleStrip,
		RendererPrimitive_LineStrip,

		// OpenGL, Vulkan, and Direct3D support these
		RendererPrimitive_TrianglesAdjacency,
		RendererPrimitive_LinesAdjacency,
		RendererPrimitive_TriangleStripAdjacency,
		RendererPrimitive_LineStripAdjacency,

		// OpenGL and Vulkan support these
		RendererPrimitive_TriangleFan,
		RendererPrimitive_LineLoop,

		RendererPrimitiveCount
	};

	using RendererAPIType = uint8_t;
	enum : RendererAPIType
	{
		RendererAPI_None,

		RendererAPI_OpenGL
	};

	class RendererAPI
	{
	public:
		static inline auto GetType() -> RendererAPIType { return s_Type; }
	public:
		virtual auto SetClearColor(const glm::vec4& color) -> void = 0;
		virtual auto Clear() -> void = 0;

		virtual auto DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t offset, uint32_t count, RendererPrimitive primitive) -> void = 0;
	private:
		static inline RendererAPIType s_Type{RendererAPI_OpenGL}; // TODO: choose
	private:
		friend class RenderCommand;
		static auto CreateScope() -> Scope<RendererAPI>;
	};
}
