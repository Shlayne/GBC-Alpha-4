#pragma once

#include "GBC/Rendering/Texture.h"

namespace gbc
{
	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(const Texture2DInfo& info);
		virtual ~OpenGLTexture2D();
	public:
		virtual auto Bind(uint32_t location) const -> void override;
		inline virtual auto GetWidth() const -> uint32_t override { return m_Width; }
		inline virtual auto GetHeight() const -> uint32_t override { return m_Height; }
		inline virtual auto GetFormat() const -> TextureFormat override { return m_Format; }
		inline virtual auto GetMinFilter() const -> TextureFilterMode override { return m_MinFilter; }
		inline virtual auto GetMagFilter() const -> TextureFilterMode override { return m_MagFilter; }
		inline virtual auto GetWrapU() const -> TextureWrapMode override { return m_WrapU; }
		inline virtual auto GetWrapV() const -> TextureWrapMode override { return m_WrapV; }
	private:
		uint32_t m_RendererID{};
		uint32_t m_Width{};
		uint32_t m_Height{};
		TextureFormat m_Format : TextureFormat::BitCount {};
		TextureFilterMode m_MinFilter : TextureFilterMode::BitCount {};
		TextureFilterMode m_MagFilter : TextureFilterMode::BitCount {};
		TextureWrapMode m_WrapU : TextureWrapMode::BitCount {};
		TextureWrapMode m_WrapV : TextureWrapMode::BitCount {};
	};
}
