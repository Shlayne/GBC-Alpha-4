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
		switch (primitive)
		{
			case RendererPrimitive_Triangles:              return GL_TRIANGLES;
			case RendererPrimitive_Lines:                  return GL_LINES;
			case RendererPrimitive_Points:                 return GL_POINTS;
			case RendererPrimitive_TriangleStrip:          return GL_TRIANGLE_STRIP;
			case RendererPrimitive_LineStrip:              return GL_LINE_STRIP;
			case RendererPrimitive_TrianglesAdjacency:     return GL_TRIANGLES_ADJACENCY;
			case RendererPrimitive_LinesAdjacency:         return GL_LINES_ADJACENCY;
			case RendererPrimitive_TriangleStripAdjacency: return GL_TRIANGLE_STRIP_ADJACENCY;
			case RendererPrimitive_LineStripAdjacency:     return GL_LINE_STRIP_ADJACENCY;
			case RendererPrimitive_TriangleFan:            return GL_TRIANGLE_FAN;
			case RendererPrimitive_LineLoop:               return GL_LINE_LOOP;
		}

		GBC_CORE_ASSERT(false, "Unknown RendererPrimitive.");
		return 0;
	}

	auto ConvertIndexBufferElementTypeToOpenGL(IndexBufferElementType type) -> GLenum
	{
		switch (type)
		{
			case IndexBufferElementType_UInt32: return GL_UNSIGNED_INT;
			case IndexBufferElementType_UInt16: return GL_UNSIGNED_SHORT;
			case IndexBufferElementType_UInt8:  return GL_UNSIGNED_BYTE;
		}

		GBC_CORE_ASSERT(false, "Unknown IndexBufferElementType.");
		return 0;
	}
}
