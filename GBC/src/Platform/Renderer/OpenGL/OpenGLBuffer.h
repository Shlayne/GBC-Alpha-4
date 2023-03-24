#pragma once

#include "GBC/Rendering/Buffer.h"

namespace gbc
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(const VertexBufferInfo& info);
		virtual ~OpenGLVertexBuffer();
	public:
		virtual auto Bind() const -> void override;
		virtual auto SetData(const void* data, uint32_t size) -> void override;
		inline virtual auto GetSize() const -> uint32_t override { return m_Size; }
		inline virtual auto GetLayout() const -> const VertexBufferLayout& override { return m_Layout; }
	private:
		uint32_t m_RendererID{0};
		uint32_t m_Size{0};
		VertexBufferLayout m_Layout;
	};
 
	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(const IndexBufferInfo& info);
		virtual ~OpenGLIndexBuffer();
	public:
		virtual auto Bind() const -> void override;
		virtual auto SetData(const void* data, uint32_t count) -> void override;
		inline virtual auto GetCount() const -> uint32_t override { return m_Count; }
		inline virtual auto GetType() const -> IndexBufferElementType override { return m_Type; }
	private:
		uint32_t m_RendererID{0};
		uint32_t m_Count{0};
		IndexBufferElementType m_Type{IndexBufferElementType_None};
		uint8_t m_ElementSize{0};
	};

	class OpenGLUniformBuffer : public UniformBuffer
	{
	public:
		OpenGLUniformBuffer(const UniformBufferInfo& info);
		virtual ~OpenGLUniformBuffer();
	public:
		virtual auto SetData(const void* data, uint32_t size, uint32_t offset) -> void override;
		inline virtual auto GetSize() const -> uint32_t override { return m_Size; }
	private:
		uint32_t m_RendererID{0};
		uint32_t m_Size{0};
	};
}
