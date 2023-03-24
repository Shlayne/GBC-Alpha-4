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

		virtual auto AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) -> void override;
		virtual auto SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) -> void override;

		inline virtual auto GetVertexBuffers() const -> const std::vector<Ref<VertexBuffer>>& override { return m_VertexBuffers; }
		inline virtual auto GetIndexBuffer() const -> const Ref<IndexBuffer>& override { return m_IndexBuffer; }
	private:
		std::vector<Ref<VertexBuffer>> m_VertexBuffers;
		Ref<IndexBuffer> m_IndexBuffer;
		uint32_t m_RendererID;
	};
}
