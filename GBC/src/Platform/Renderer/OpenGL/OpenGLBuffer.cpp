#include "gbcpch.h"
#include "OpenGLBuffer.h"
#include <glad/glad.h>

namespace gbc
{
	auto ConvertBufferUsageToOpenGL(BufferUsage usage) -> GLenum;

	OpenGLVertexBuffer::OpenGLVertexBuffer(const VertexBufferInfo& info)
		: m_Size{info.size}
		, m_Layout{info.layout}
	{
		glCreateBuffers(1, &m_RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glNamedBufferData(m_RendererID, m_Size, info.data, ConvertBufferUsageToOpenGL(info.usage));
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}

	auto OpenGLVertexBuffer::Bind() const -> void
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	}

	auto OpenGLVertexBuffer::SetData(const void* data, uint32_t size) -> void
	{
		GBC_CORE_ASSERT(size <= m_Size, "OpenGLVertexBuffer::SetData: size out of bounds.");

		glNamedBufferSubData(m_RendererID, 0, size, data);
	}

	OpenGLIndexBuffer::OpenGLIndexBuffer(const IndexBufferInfo& info)
		: m_Count{info.count}
		, m_Type{info.type}
		, m_ElementSize{GetIndexBufferElementSize(m_Type)}
	{
		glCreateBuffers(1, &m_RendererID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
		GLsizeiptr size{static_cast<GLsizeiptr>(m_Count) * m_ElementSize};
		glNamedBufferData(m_RendererID, size, info.data, ConvertBufferUsageToOpenGL(info.usage));
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}

	auto OpenGLIndexBuffer::Bind() const -> void
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	}

	auto OpenGLIndexBuffer::SetData(const void* data, uint32_t count) -> void
	{
		GBC_CORE_ASSERT(count <= m_Count, "OpenGLIndexBuffer::SetData: count out of bounds.");

		GLsizeiptr size{static_cast<GLsizeiptr>(count) * m_ElementSize};
		glNamedBufferSubData(m_RendererID, 0, size, data);
	}

	OpenGLUniformBuffer::OpenGLUniformBuffer(const UniformBufferInfo& info)
		: m_Size{info.size}
	{
		glCreateBuffers(1, &m_RendererID);
		glNamedBufferData(m_RendererID, m_Size, info.data, ConvertBufferUsageToOpenGL(info.usage));
		glBindBufferBase(GL_UNIFORM_BUFFER, info.binding, m_RendererID);
	}

	OpenGLUniformBuffer::~OpenGLUniformBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}

	auto OpenGLUniformBuffer::SetData(const void* data, uint32_t size, uint32_t offset) -> void
	{
		GBC_CORE_ASSERT(size <= m_Size, "OpenGLUniformBuffer::SetData: size out of bounds.");

		glNamedBufferSubData(m_RendererID, offset, size, data);
	}

	auto ConvertBufferUsageToOpenGL(BufferUsage usage) -> GLenum
	{
		switch (usage)
		{
			case BufferUsage_StaticDraw:  return GL_STATIC_DRAW;
			case BufferUsage_StaticRead:  return GL_STATIC_READ;
			case BufferUsage_StaticCopy:  return GL_STATIC_COPY;
			case BufferUsage_DynamicDraw: return GL_DYNAMIC_DRAW;
			case BufferUsage_DynamicRead: return GL_DYNAMIC_READ;
			case BufferUsage_DynamicCopy: return GL_DYNAMIC_COPY;
			case BufferUsage_StreamDraw:  return GL_STREAM_DRAW;
			case BufferUsage_StreamRead:  return GL_STREAM_READ;
			case BufferUsage_StreamCopy:  return GL_STREAM_COPY;
		}

		GBC_CORE_ASSERT(false, "Unknown BufferUsage.");
		return 0;
	}
}
