#pragma once

#include "GBC/Core/Core.h"
#include <string_view>
#include <vector>

namespace gbc
{
	using BufferUsage = uint8_t;
	enum : BufferUsage
	{
		BufferUsage_None,

		BufferUsage_StaticDraw,
		BufferUsage_StaticRead,
		BufferUsage_StaticCopy,

		BufferUsage_DynamicDraw,
		BufferUsage_DynamicRead,
		BufferUsage_DynamicCopy,

		BufferUsage_StreamDraw,
		BufferUsage_StreamRead,
		BufferUsage_StreamCopy,

		BufferUsageCount
	};

	using VertexBufferElementType = uint8_t;
	enum : VertexBufferElementType
	{
		VertexBufferElementType_None,

		VertexBufferElementType_Float,
		VertexBufferElementType_Float2,
		VertexBufferElementType_Float3,
		VertexBufferElementType_Float4,

		VertexBufferElementType_Int,
		VertexBufferElementType_Int2,
		VertexBufferElementType_Int3,
		VertexBufferElementType_Int4,

		VertexBufferElementType_UInt,
		VertexBufferElementType_UInt2,
		VertexBufferElementType_UInt3,
		VertexBufferElementType_UInt4,

		VertexBufferElementTypeCount
	};

	struct VertexBufferElement
	{
		VertexBufferElement(VertexBufferElementType type, std::string_view name, bool normalized = false) noexcept;

		std::string_view name;
		uint32_t count{0};
		uint32_t size{0};
		uint64_t offset{0};
		VertexBufferElementType type{VertexBufferElementType_None};
		bool normalized{false};
	};

	class VertexBufferLayout
	{
	public:
		VertexBufferLayout() noexcept = default;
		VertexBufferLayout(std::initializer_list<VertexBufferElement> elements) noexcept;
	public:
		inline auto GetElements() const noexcept -> const std::vector<VertexBufferElement>& { return m_Elements; }
		inline auto GetStride() const noexcept -> uint32_t { return m_Stride; }
	public:
		std::vector<VertexBufferElement> m_Elements;
		uint32_t m_Stride{0};
	};

	struct VertexBufferInfo
	{
		VertexBufferLayout layout;
		const void* data{nullptr};
		uint32_t size{0}; // Size in bytes.
		BufferUsage usage{BufferUsage_StaticDraw};
	};

	class VertexBuffer
	{
	public:
		static auto CreateRef(const VertexBufferInfo& info) -> Ref<VertexBuffer>;
		virtual ~VertexBuffer() = default;
	public:
		virtual auto Bind() const -> void = 0;
		virtual auto SetData(const void* data, uint32_t size) -> void = 0;
		virtual auto GetSize() const -> uint32_t = 0;
		virtual auto GetLayout() const -> const VertexBufferLayout& = 0;
	};

	using IndexBufferElementType = uint8_t;
	enum : IndexBufferElementType
	{
		IndexBufferElementType_None,

		IndexBufferElementType_UInt32,
		IndexBufferElementType_UInt16,
		IndexBufferElementType_UInt8,

		IndexBufferElementTypeCount
	};

	auto GetIndexBufferElementSize(IndexBufferElementType type) -> uint8_t;

	struct IndexBufferInfo
	{
		const void* data{nullptr};
		uint32_t count{0}; // Count in elements.
		BufferUsage usage{BufferUsage_StaticDraw};
		IndexBufferElementType type{IndexBufferElementType_UInt32};
	};

	class IndexBuffer
	{
	public:
		static auto CreateRef(const IndexBufferInfo& info) -> Ref<IndexBuffer>;
		virtual ~IndexBuffer() = default;
	public:
		virtual auto Bind() const -> void = 0;
		virtual auto SetData(const void* data, uint32_t count) -> void = 0;
		virtual auto GetCount() const -> uint32_t = 0;
		virtual auto GetType() const -> IndexBufferElementType = 0;
	};

	struct UniformBufferInfo
	{
		const void* data{nullptr};
		uint32_t size{0}; // Size in bytes.
		uint32_t binding{0};
		BufferUsage usage{BufferUsage_DynamicDraw};
	};

	class UniformBuffer
	{
	public:
		static auto CreateRef(const UniformBufferInfo& info) -> Ref<UniformBuffer>;
		virtual ~UniformBuffer() = default;
	public:
		virtual auto SetData(const void* data, uint32_t size, uint32_t offset = 0) -> void = 0;
		virtual auto GetSize() const -> uint32_t = 0;
	};
}
