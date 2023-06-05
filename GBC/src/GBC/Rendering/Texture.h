#pragma once

#include "GBC/Core/Core.h"
#include "GBC/Rendering/RawTexture2D.h"

namespace gbc
{
	GBC_DEFINE_BOUNDED_ENUM(
		TextureFilterMode, uint8_t,

		Linear,
		Nearest
	);

	GBC_DEFINE_BOUNDED_ENUM(
		TextureWrapMode, uint8_t,

		ClampToEdge,
		Repeat
	);

	class Texture
	{
	public:
		virtual ~Texture() = default;
	public:
		virtual auto Bind(uint32_t location = 0) const -> void = 0;
	};

	struct Texture2DInfo
	{
		Ref<RawTexture2D> rawTexture;
		uint32_t width{1};
		uint32_t height{1};
		TextureFormat format : TextureFormat::BitCount {};
		TextureFilterMode minFilter : TextureFilterMode::BitCount {TextureFilterMode::Linear};
		TextureFilterMode magFilter : TextureFilterMode::BitCount {TextureFilterMode::Linear};
		TextureWrapMode wrapU : TextureWrapMode::BitCount {TextureWrapMode::ClampToEdge};
		TextureWrapMode wrapV : TextureWrapMode::BitCount {TextureWrapMode::ClampToEdge};
	};

	class Texture2D : public Texture
	{
	public:
		static auto CreateRef(const Texture2DInfo& info) -> Ref<Texture2D>;
	public:
		virtual auto GetWidth() const -> uint32_t = 0;
		virtual auto GetHeight() const -> uint32_t = 0;
		virtual auto GetFormat() const -> TextureFormat = 0;
		virtual auto GetMinFilter() const -> TextureFilterMode = 0;
		virtual auto GetMagFilter() const -> TextureFilterMode = 0;
		virtual auto GetWrapU() const -> TextureWrapMode = 0;
		virtual auto GetWrapV() const -> TextureWrapMode = 0;
	};
}
