#include "gbcpch.h"
#include "OpenGLRendererAPI.h"
#include <glad/glad.h>

namespace gbc
{
	auto ConvertRendererPrimitiveToOpenGL(RendererPrimitive primitive) -> GLenum;
	auto ConvertIndexBufferElementTypeToOpenGL(IndexBufferElementType type) -> GLenum;

	auto OpenGLRendererAPI::SetClearColor(glm::vec4 color) -> void
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	auto OpenGLRendererAPI::Clear() -> void
	{
		// TODO: specify which buffers are cleared
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	}

	auto OpenGLRendererAPI::SetViewport(glm::ivec2 position, glm::ivec2 size) -> void
	{
		glViewport(position.x, position.y, size.x, size.y);
	}

	auto OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t offset, uint32_t count, RendererPrimitive primitive) -> void
	{
		auto& indexBuffer{vertexArray->GetIndexBuffer()};
		uint32_t usedCount{count ? count : indexBuffer->GetCount()};
		GBC_CORE_ASSERT(offset < usedCount, "Attempted to render non-positive number of indices.");
		usedCount -= offset;

		glDrawElements(
			ConvertRendererPrimitiveToOpenGL(primitive),
			usedCount,
			ConvertIndexBufferElementTypeToOpenGL(indexBuffer->GetType()),
			(const void*)static_cast<size_t>(offset)
		);
	}

	auto ConvertRendererPrimitiveToOpenGL(RendererPrimitive primitive) -> GLenum
	{
		GBC_CORE_ASSERT_BOUNDED_ENUM_IS_VALID(RendererPrimitive, primitive);
		constexpr GLenum primitives[]
		{
			GL_TRIANGLES,                // RendererPrimitive::Triangles
			GL_LINES,                    // RendererPrimitive::Lines
			GL_POINTS,                   // RendererPrimitive::Points
			GL_TRIANGLE_STRIP,           // RendererPrimitive::TriangleStrip
			GL_LINE_STRIP,               // RendererPrimitive::LineStrip
			GL_TRIANGLES_ADJACENCY,      // RendererPrimitive::TrianglesAdjacency
			GL_LINES_ADJACENCY,          // RendererPrimitive::LinesAdjacency
			GL_TRIANGLE_STRIP_ADJACENCY, // RendererPrimitive::TriangleStripAdjacency
			GL_LINE_STRIP_ADJACENCY,     // RendererPrimitive::LineStripAdjacency
			GL_TRIANGLE_FAN,             // RendererPrimitive::TriangleFan
			GL_LINE_LOOP,                // RendererPrimitive::LineLoop
		};
		return primitives[primitive - RendererPrimitive::Begin];
	}

	auto ConvertIndexBufferElementTypeToOpenGL(IndexBufferElementType type) -> GLenum
	{
		GBC_CORE_ASSERT_BOUNDED_ENUM_IS_VALID(IndexBufferElementType, type);
		constexpr GLenum types[]
		{
			GL_UNSIGNED_INT,   // IndexBufferElementType::UInt32
			GL_UNSIGNED_SHORT, // IndexBufferElementType::UInt16
			GL_UNSIGNED_BYTE,  // IndexBufferElementType::UInt8
		};
		return types[type - IndexBufferElementType::Begin];
	}
}
