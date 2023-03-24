#pragma once

#include "GBC/Core/Core.h"
#include "GBC/Rendering/Buffer.h"

namespace gbc
{
	class VertexArray
	{
	public:
		static auto CreateRef() -> Ref<VertexArray>;
		virtual ~VertexArray() = default;
	public:
		virtual auto Bind() const -> void = 0;
		virtual auto Unbind() const -> void = 0;

		virtual auto SetVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) -> void = 0;
		virtual auto SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) -> void = 0;

		virtual auto GetVertexBuffer() const -> const Ref<VertexBuffer>& = 0;
		virtual auto GetIndexBuffer() const -> const Ref<IndexBuffer>& = 0;
	};
}
