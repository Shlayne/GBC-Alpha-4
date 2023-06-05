#pragma once

#include "GBC/Core/Core.h"
#include <string_view>
#include <vector>

namespace gbc
{
	GBC_DEFINE_BOUNDED_ENUM(
		BufferUsage, uint8_t,

		StaticDraw,
		StaticRead,
		StaticCopy,

		DynamicDraw,
		DynamicRead,
		DynamicCopy,

		StreamDraw,
		StreamRead,
		StreamCopy
	);
	
	GBC_DEFINE_BOUNDED_ENUM(
		VertexBufferElementType, uint8_t,

		Float,
		Float2,
		Float3,
		Float4,

		Int,
		Int2,
		Int3,
		Int4,

		UInt,
		UInt2,
		UInt3,
		UInt4
	);

	struct VertexBufferElement
	{
		VertexBufferElement(VertexBufferElementType type, std::string_view name, bool normalized = false) noexcept;

		std::string_view name;
		uint32_t count{};
		uint32_t size{};
		uint64_t offset{};
		VertexBufferElementType type : VertexBufferElementType::BitCount {};
		bool normalized{};
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
		uint32_t m_Stride{};
	};

	struct VertexBufferInfo
	{
		VertexBufferLayout layout;
		const void* data{};
		uint32_t size{}; // Size in bytes.
		BufferUsage usage : BufferUsage::BitCount {BufferUsage::StaticDraw};
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

	GBC_DEFINE_BOUNDED_ENUM(
		IndexBufferElementType, uint8_t,

		UInt32,
		UInt16,
		UInt8
	);

	auto GetIndexBufferElementSize(IndexBufferElementType type) -> uint8_t;

	struct IndexBufferInfo
	{
		const void* data{};
		uint32_t count{}; // Count in elements.
		BufferUsage usage : BufferUsage::BitCount {BufferUsage::StaticDraw};
		IndexBufferElementType type : IndexBufferElementType::BitCount {IndexBufferElementType::UInt32};
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
		const void* data{};
		uint32_t size{}; // Size in bytes.
		uint32_t binding{};
		BufferUsage usage : BufferUsage::BitCount {BufferUsage::DynamicDraw};
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
