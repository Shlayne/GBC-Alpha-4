#include "gbcpch.h"
#include "OpenGLVertexArray.h"
#include <glad/glad.h>

namespace gbc
{
	auto ConvertVertexBufferElementTypeToOpenGL(VertexBufferElementType type) -> GLenum;

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &m_RendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}

	auto OpenGLVertexArray::Bind() const -> void
	{
		glBindVertexArray(m_RendererID);
	}

	auto OpenGLVertexArray::Unbind() const -> void
	{
		glBindVertexArray(0);
	}

	auto OpenGLVertexArray::SetVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) -> void
	{
		GBC_CORE_ASSERT(!vertexBuffer->GetLayout().GetElements().empty());

		glBindVertexArray(m_RendererID);
		
		auto& layout{vertexBuffer->GetLayout()};
		auto& elements{layout.GetElements()};
		auto elementCount{static_cast<uint32_t>(elements.size())};

		// If resetting the vertex buffer, disable all attribs that won't be active with the next one.
		if (m_VertexBuffer)
		{
			auto currentElementCount{static_cast<uint32_t>(m_VertexBuffer->GetLayout().GetElements().size())};
			for (uint32_t i{elementCount}; i < currentElementCount; ++i)
				glDisableVertexAttribArray(i);
		}

		vertexBuffer->Bind();
		m_VertexBuffer = vertexBuffer;


		for (uint32_t i{0}; i < elementCount; ++i)
		{
			auto& element{elements[i]};
			glEnableVertexAttribArray(i);
			glVertexAttribPointer(
				i,
				element.count,
				ConvertVertexBufferElementTypeToOpenGL(element.type),
				element.normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)element.offset
			);
		}
	}

	auto OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) -> void
	{
		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();
		m_IndexBuffer = indexBuffer;
	}

	auto ConvertVertexBufferElementTypeToOpenGL(VertexBufferElementType type) -> GLenum
	{
		switch (type)
		{
			case VertexBufferElementType_Float:  [[fallthrough]];
			case VertexBufferElementType_Float2: [[fallthrough]];
			case VertexBufferElementType_Float3: [[fallthrough]];
			case VertexBufferElementType_Float4:
				return GL_FLOAT;
			case VertexBufferElementType_Int:  [[fallthrough]];
			case VertexBufferElementType_Int2: [[fallthrough]];
			case VertexBufferElementType_Int3: [[fallthrough]];
			case VertexBufferElementType_Int4:
				return GL_INT;
			case VertexBufferElementType_UInt:  [[fallthrough]];
			case VertexBufferElementType_UInt2: [[fallthrough]];
			case VertexBufferElementType_UInt3: [[fallthrough]];
			case VertexBufferElementType_UInt4:
				return GL_UNSIGNED_INT;
		}

		GBC_CORE_ASSERT(false, "Unknown VertexBufferElementType.");
		return 0;
	}
}
