#pragma once

#include "GBC/Core/Core.h"
#include <filesystem> // TODO: remove when asset system exists

namespace gbc
{
	GBC_DEFINE_BOUNDED_ENUM(
		TextureFormat, uint8_t,

		R_8U,
		R_32U,
		RGB_8U,
		RGBA_8U,
		RGBA_32F
	);

	class RawTexture2D
	{
	public:
		static inline auto CreateRef() -> Ref<RawTexture2D> { return gbc::CreateRef<RawTexture2D>(); }
		static inline auto CreateRef(uint32_t width, uint32_t height, TextureFormat format) -> Ref<RawTexture2D> { return gbc::CreateRef<RawTexture2D>(width, height, format); }
		static inline auto CreateRef(const RawTexture2D& texture) -> Ref<RawTexture2D> { return gbc::CreateRef<RawTexture2D>(texture); }
		static inline auto CreateRef(RawTexture2D&& texture) -> Ref<RawTexture2D> { return gbc::CreateRef<RawTexture2D>(std::move(texture)); }

		// TODO: remove when asset system exists
		static inline auto CreateRef(const std::filesystem::path& filepath, TextureFormat format) -> Ref<RawTexture2D> { return gbc::CreateRef<RawTexture2D>(filepath, format); }
	public:
		RawTexture2D() = default;
		RawTexture2D(uint32_t width, uint32_t height, TextureFormat format);
		RawTexture2D(const RawTexture2D& texture);
		RawTexture2D(RawTexture2D&& texture) noexcept;

		// TODO: remove when asset system exists
		RawTexture2D(const std::filesystem::path& filepath, TextureFormat format);

		auto operator=(const RawTexture2D& texture) -> RawTexture2D&;
		auto operator=(RawTexture2D&& texture) noexcept -> RawTexture2D&;
		~RawTexture2D();
	public:
		inline auto GetWidth() const noexcept -> uint32_t { return m_Width; }
		inline auto GetHeight() const noexcept -> uint32_t { return m_Height; }
		inline auto GetFormat() const noexcept -> TextureFormat { return m_Format; }
		inline auto GetPixels() noexcept -> void* { return m_Pixels; }
		inline auto GetPixels() const noexcept -> const void* { return m_Pixels; }
	private:
		auto Deallocate() const -> void;
	private:
		uint32_t m_Width{};
		uint32_t m_Height{};
		void* m_Pixels{};
		TextureFormat m_Format : TextureFormat::BitCount {};
		bool m_SelfAllocated : 1 {}; // TODO: undermine this by using the same (de)allocators.
	};
}
