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


		for (uint32_t i{}; i < elementCount; ++i)
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
		GBC_CORE_ASSERT_BOUNDED_ENUM_IS_VALID(VertexBufferElementType, type);
		constexpr GLenum types[]
		{
			GL_FLOAT,        // VertexBufferElementType::Float
			GL_FLOAT,        // VertexBufferElementType::Float2
			GL_FLOAT,        // VertexBufferElementType::Float3
			GL_FLOAT,        // VertexBufferElementType::Float4
			GL_INT,          // VertexBufferElementType::Int
			GL_INT,          // VertexBufferElementType::Int2
			GL_INT,          // VertexBufferElementType::Int3
			GL_INT,          // VertexBufferElementType::Int4
			GL_UNSIGNED_INT, // VertexBufferElementType::UInt
			GL_UNSIGNED_INT, // VertexBufferElementType::UInt2
			GL_UNSIGNED_INT, // VertexBufferElementType::UInt3
			GL_UNSIGNED_INT, // VertexBufferElementType::UInt4
		};
		return types[type - VertexBufferElementType::Begin];
	}
}
