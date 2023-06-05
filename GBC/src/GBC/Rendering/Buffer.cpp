#include "gbcpch.h"
#include "Buffer.h"
#include "GBC/Rendering/RendererAPI.h"
#include "Platform/Renderer/OpenGL/OpenGLBuffer.h"

namespace gbc
{
	auto VertexBuffer::CreateRef(const VertexBufferInfo& info) -> Ref<VertexBuffer>
	{
		GBC_CORE_ASSERT_BOUNDED_CLASS_ENUM_IS_VALID(RendererAPI, RendererAPI::GetType());
		constexpr Ref<VertexBuffer>(*createRefFuncs[])(const VertexBufferInfo&)
		{
			[](const VertexBufferInfo& info) -> Ref<VertexBuffer> { return gbc::CreateRef<OpenGLVertexBuffer>(info); }
		};
		return createRefFuncs[RendererAPI::GetType() - RendererAPI::Begin](info);
	}

	auto IndexBuffer::CreateRef(const IndexBufferInfo& info) -> Ref<IndexBuffer>
	{
		GBC_CORE_ASSERT_BOUNDED_CLASS_ENUM_IS_VALID(RendererAPI, RendererAPI::GetType());
		constexpr Ref<IndexBuffer>(*createRefFuncs[])(const IndexBufferInfo&)
		{
			[](const IndexBufferInfo& info) -> Ref<IndexBuffer> { return gbc::CreateRef<OpenGLIndexBuffer>(info); }
		};
		return createRefFuncs[RendererAPI::GetType() - RendererAPI::Begin](info);
	}

	auto UniformBuffer::CreateRef(const UniformBufferInfo& info) -> Ref<UniformBuffer>
	{
		GBC_CORE_ASSERT_BOUNDED_CLASS_ENUM_IS_VALID(RendererAPI, RendererAPI::GetType());
		constexpr Ref<UniformBuffer>(*createRefFuncs[])(const UniformBufferInfo&)
		{
			[](const UniformBufferInfo& info) -> Ref<UniformBuffer> { return gbc::CreateRef<OpenGLUniformBuffer>(info); }
		};
		return createRefFuncs[RendererAPI::GetType() - RendererAPI::Begin](info);
	}

	auto GetVertexBufferElementCount(VertexBufferElementType type) -> uint32_t;
	auto GetVertexBufferElementSize(VertexBufferElementType type) -> uint32_t;

	VertexBufferElement::VertexBufferElement(VertexBufferElementType type, std::string_view name, bool normalized) noexcept
		: name{name}
		, count{GetVertexBufferElementCount(type)}
		, size{GetVertexBufferElementSize(type)}
		, type{type}
		, normalized{normalized}
	{

	}

	VertexBufferLayout::VertexBufferLayout(std::initializer_list<VertexBufferElement> elements) noexcept
		: m_Elements{elements}
	{
		uint64_t offset{};

		for (auto& element : m_Elements)
		{
			element.offset = offset;
			offset += element.size;
			m_Stride += element.size;
		}
	}

	auto GetVertexBufferElementCount(VertexBufferElementType type) -> uint32_t
	{
		GBC_CORE_ASSERT_BOUNDED_ENUM_IS_VALID(VertexBufferElementType, type);
		constexpr uint32_t elementCounts[]
		{
			1, // VertexBufferElementType::Float
			2, // VertexBufferElementType::Float2
			3, // VertexBufferElementType::Float3
			4, // VertexBufferElementType::Float4
			1, // VertexBufferElementType::Int
			2, // VertexBufferElementType::Int2
			3, // VertexBufferElementType::Int3
			4, // VertexBufferElementType::Int4
			1, // VertexBufferElementType::UInt
			2, // VertexBufferElementType::UInt2
			3, // VertexBufferElementType::UInt3
			4, // VertexBufferElementType::UInt4
		};
		return elementCounts[type - VertexBufferElementType::Begin];
	}

	auto GetVertexBufferElementSize(VertexBufferElementType type) -> uint32_t
	{
		GBC_CORE_ASSERT_BOUNDED_ENUM_IS_VALID(VertexBufferElementType, type);
		constexpr uint32_t elementSizes[]
		{
			1 * sizeof(float),    // VertexBufferElementType::Float
			2 * sizeof(float),    // VertexBufferElementType::Float2
			3 * sizeof(float),    // VertexBufferElementType::Float3
			4 * sizeof(float),    // VertexBufferElementType::Float4
			1 * sizeof(int32_t),  // VertexBufferElementType::Int
			2 * sizeof(int32_t),  // VertexBufferElementType::Int2
			3 * sizeof(int32_t),  // VertexBufferElementType::Int3
			4 * sizeof(int32_t),  // VertexBufferElementType::Int4
			1 * sizeof(uint32_t), // VertexBufferElementType::UInt
			2 * sizeof(uint32_t), // VertexBufferElementType::UInt2
			3 * sizeof(uint32_t), // VertexBufferElementType::UInt3
			4 * sizeof(uint32_t), // VertexBufferElementType::UInt4
		};
		return elementSizes[type - VertexBufferElementType::Begin];
	}

	auto GetIndexBufferElementSize(IndexBufferElementType type) -> uint8_t
	{
		GBC_CORE_ASSERT_BOUNDED_ENUM_IS_VALID(IndexBufferElementType, type);
		constexpr uint8_t elementSizes[]
		{
			sizeof(uint32_t), // IndexBufferElementType::UInt32
			sizeof(uint16_t), // IndexBufferElementType::UInt16
			sizeof(uint8_t),  // IndexBufferElementType::UInt8
		};
		return elementSizes[type - IndexBufferElementType::Begin];
	}
}
