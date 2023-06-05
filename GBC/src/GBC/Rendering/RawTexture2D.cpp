#include "gbcpch.h"
#include "RawTexture2D.h"
#include <stb_image.h>

namespace gbc
{
	auto GetBytesPerPixel(TextureFormat format) -> uint32_t;
	auto GetChannels(TextureFormat format) -> int32_t;
	auto IsHDR(TextureFormat format) -> bool;

	RawTexture2D::RawTexture2D(uint32_t width, uint32_t height, TextureFormat format)
		: m_Width{width}
		, m_Height{height}
		, m_Format{format}
		, m_SelfAllocated{true}
	{
		m_Pixels = new uint8_t[GetBytesPerPixel(m_Format) * m_Width * m_Height]{};
	}

	// TODO: remove when asset system exists
	RawTexture2D::RawTexture2D(const std::filesystem::path& filepath, TextureFormat format)
	{
		auto filepathString{filepath.string()};
		int32_t width, height;
		void* pixels{};

		if (IsHDR(format))
			pixels = stbi_loadf(filepathString.c_str(), &width, &height, nullptr, GetChannels(format));
		else
			pixels = stbi_load(filepathString.c_str(), &width, &height, nullptr, GetChannels(format));
		GBC_CORE_ASSERT(pixels, "Failed to load texture from filepath=\"{}\"", filepathString);

		m_Width = static_cast<uint32_t>(width);
		m_Height = static_cast<uint32_t>(height);
		m_Pixels = pixels;
		m_Format = format;
		m_SelfAllocated = false;
	}

	RawTexture2D::RawTexture2D(const RawTexture2D& texture)
		: m_Width{texture.m_Width}
		, m_Height{texture.m_Height}
		, m_Format{texture.m_Format}
		, m_SelfAllocated{true}
	{
		size_t size{static_cast<size_t>(GetBytesPerPixel(m_Format)) * m_Width * m_Height};
		m_Pixels = new uint8_t[size];
		memcpy_s(m_Pixels, size, texture.m_Pixels, size);
	}

	RawTexture2D::RawTexture2D(RawTexture2D&& texture) noexcept
		: m_Width{texture.m_Width}
		, m_Height{texture.m_Height}
		, m_Pixels{texture.m_Pixels}
		, m_Format{texture.m_Format}
		, m_SelfAllocated{texture.m_SelfAllocated}
	{
		texture.m_Width = {};
		texture.m_Height = {};
		texture.m_Pixels = {};
		texture.m_Format = {};
		texture.m_SelfAllocated = {};
	}

	auto RawTexture2D::operator=(const RawTexture2D& texture) -> RawTexture2D&
	{
		if (this != &texture)
		{
			Deallocate();

			m_Width = texture.m_Width;
			m_Height = texture.m_Height;
			m_Format = texture.m_Format;
			size_t size{static_cast<size_t>(GetBytesPerPixel(m_Format)) * m_Width * m_Height};
			m_Pixels = new uint8_t[size];
			m_SelfAllocated = true;

			memcpy_s(m_Pixels, size, texture.m_Pixels, size);
		}
		return *this;
	}

	auto RawTexture2D::operator=(RawTexture2D&& texture) noexcept -> RawTexture2D&
	{
		if (this != &texture)
		{
			Deallocate();

			m_Width = texture.m_Width;
			m_Height = texture.m_Height;
			m_Pixels = texture.m_Pixels;
			m_Format = texture.m_Format;
			m_SelfAllocated = texture.m_SelfAllocated;

			texture.m_Width = {};
			texture.m_Height = {};
			texture.m_Pixels = {};
			texture.m_Format = {};
			texture.m_SelfAllocated = {};
		}
		return *this;
	}

	RawTexture2D::~RawTexture2D()
	{
		Deallocate();
	}

	auto RawTexture2D::Deallocate() const -> void
	{
		if (m_SelfAllocated)
			delete[] m_Pixels; // No destructors need to be called since they're all always trivial types.
		else
			stbi_image_free(m_Pixels);
	}

	auto GetBytesPerPixel(TextureFormat format) -> uint32_t
	{
		GBC_CORE_ASSERT_BOUNDED_ENUM_IS_VALID(TextureFormat, format);
		constexpr uint32_t bytesPerPixel[]
		{
			1, // TextureFormat::R_8U
			4, // TextureFormat::R_32U
			3, // TextureFormat::RGB_8U
			4, // TextureFormat::RGBA_8U
			4, // TextureFormat::RGBA_32F
		};
		return bytesPerPixel[format - TextureFormat::Begin];
	}

	auto GetChannels(TextureFormat format) -> int32_t
	{
		GBC_CORE_ASSERT_BOUNDED_ENUM_IS_VALID(TextureFormat, format);
		constexpr int32_t channels[]
		{
			1,  // TextureFormat::R_8U
			4,  // TextureFormat::R_32U
			3,  // TextureFormat::RGB_8U
			4,  // TextureFormat::RGBA_8U
			16, // TextureFormat::RGBA_32F
		};
		return channels[format - TextureFormat::Begin];
	}

	auto IsHDR(TextureFormat format) -> bool
	{
		GBC_CORE_ASSERT_BOUNDED_ENUM_IS_VALID(TextureFormat, format);
		constexpr uint8_t channels =
			false * (1 << 0) | // TextureFormat::R_8U
			false * (1 << 1) | // TextureFormat::R_32U
			false * (1 << 2) | // TextureFormat::RGB_8U
			false * (1 << 3) | // TextureFormat::RGBA_8U
			true  * (1 << 4);  // TextureFormat::RGBA_32F
		return channels & (1 << (format - TextureFormat::Begin));
	}
}
