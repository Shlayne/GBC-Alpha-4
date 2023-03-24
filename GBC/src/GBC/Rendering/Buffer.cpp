#include "gbcpch.h"
#include "Buffer.h"
#include "GBC/Rendering/RendererAPI.h"
#include "Platform/Renderer/OpenGL/OpenGLBuffer.h"

namespace gbc
{
	auto VertexBuffer::CreateRef(const VertexBufferInfo& info) -> Ref<VertexBuffer>
	{
		switch (RendererAPI::GetType())
		{
			case RendererAPI_OpenGL: return gbc::CreateScope<OpenGLVertexBuffer>(info);
		}

		GBC_CORE_ASSERT(false, "Unknown RendererAPI.");
		return nullptr;
	}

	auto IndexBuffer::CreateRef(const IndexBufferInfo& info) -> Ref<IndexBuffer>
	{
		switch (RendererAPI::GetType())
		{
			case RendererAPI_OpenGL: return gbc::CreateScope<OpenGLIndexBuffer>(info);
		}

		GBC_CORE_ASSERT(false, "Unknown RendererAPI.");
		return nullptr;
	}

	auto UniformBuffer::CreateRef(const UniformBufferInfo& info) -> Ref<UniformBuffer>
	{
		switch (RendererAPI::GetType())
		{
			case RendererAPI_OpenGL: return gbc::CreateScope<OpenGLUniformBuffer>(info);
		}

		GBC_CORE_ASSERT(false, "Unknown RendererAPI.");
		return nullptr;
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
		uint64_t offset = 0;

		for (auto& element : m_Elements)
		{
			element.offset = offset;
			offset += element.size;
			m_Stride += element.size;
		}
	}

	auto GetVertexBufferElementCount(VertexBufferElementType type) -> uint32_t
	{
		switch (type)
		{
			case VertexBufferElementType_Float: [[fallthrough]];
			case VertexBufferElementType_Int: [[fallthrough]];
			case VertexBufferElementType_UInt:
				return 1;
			case VertexBufferElementType_Float2: [[fallthrough]];
			case VertexBufferElementType_Int2: [[fallthrough]];
			case VertexBufferElementType_UInt2:
				return 2;
			case VertexBufferElementType_Float3: [[fallthrough]];
			case VertexBufferElementType_Int3: [[fallthrough]];
			case VertexBufferElementType_UInt3:
				return 3;
			case VertexBufferElementType_Float4: [[fallthrough]];
			case VertexBufferElementType_Int4: [[fallthrough]];
			case VertexBufferElementType_UInt4:
				return 4;
		}

		GBC_CORE_ASSERT(false, "Unknown VertexBufferElementType.");
		return 0;
	}

	auto GetVertexBufferElementSize(VertexBufferElementType type) -> uint32_t
	{
		switch (type)
		{
			case VertexBufferElementType_Float:  return 1 * sizeof(float);
			case VertexBufferElementType_Float2: return 2 * sizeof(float);
			case VertexBufferElementType_Float3: return 3 * sizeof(float);
			case VertexBufferElementType_Float4: return 4 * sizeof(float);
			case VertexBufferElementType_Int:    return 1 * sizeof(int32_t);
			case VertexBufferElementType_Int2:   return 2 * sizeof(int32_t);
			case VertexBufferElementType_Int3:   return 3 * sizeof(int32_t);
			case VertexBufferElementType_Int4:   return 4 * sizeof(int32_t);
			case VertexBufferElementType_UInt:   return 1 * sizeof(uint32_t);
			case VertexBufferElementType_UInt2:  return 2 * sizeof(uint32_t);
			case VertexBufferElementType_UInt3:  return 3 * sizeof(uint32_t);
			case VertexBufferElementType_UInt4:  return 4 * sizeof(uint32_t);
		}

		GBC_CORE_ASSERT(false, "Unknown VertexBufferElementType.");
		return 0;
	}

	auto GetIndexBufferElementSize(IndexBufferElementType type) -> uint8_t
	{
		switch (type)
		{
			case IndexBufferElementType_UInt32: return sizeof(uint32_t);
			case IndexBufferElementType_UInt16: return sizeof(uint16_t);
			case IndexBufferElementType_UInt8:  return sizeof(uint8_t);
		}

		GBC_CORE_ASSERT(false, "Unknown IndexBufferElementType.");
		return 0;
	}
}
