#pragma once

#include "GBC/Rendering/VertexArray.h"

namespace gbc
{
	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray();
	public:
		virtual auto Bind() const -> void override;
		virtual auto Unbind() const -> void override;

		virtual auto SetVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) -> void override;
		virtual auto SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) -> void override;

		inline virtual auto GetVertexBuffer() const -> const Ref<VertexBuffer>& override { return m_VertexBuffer; }
		inline virtual auto GetIndexBuffer() const -> const Ref<IndexBuffer>& override { return m_IndexBuffer; }
	private:
		Ref<VertexBuffer> m_VertexBuffer;
		Ref<IndexBuffer> m_IndexBuffer;
		uint32_t m_RendererID{};
	};
}
