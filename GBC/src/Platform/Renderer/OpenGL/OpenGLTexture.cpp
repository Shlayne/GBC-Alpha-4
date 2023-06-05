#include "gbcpch.h"
#include "OpenGLTexture.h"
#include <glad/glad.h>

namespace gbc
{
	auto ConvertTextureFormatToOpenGL(TextureFormat internalFormat, TextureFormat format) -> std::tuple<GLint, GLenum, GLenum>;
	auto ConvertTextureFilterModeToOpenGL(TextureFilterMode minFilter, TextureFilterMode magFilter) -> std::pair<GLint, GLint>;
	auto ConvertTextureWrapModeToOpenGL(TextureWrapMode wrapU, TextureWrapMode wrapV) -> std::pair<GLint, GLint>;

	OpenGLTexture2D::OpenGLTexture2D(const Texture2DInfo& info)
		: m_MinFilter{info.minFilter}
		, m_MagFilter{info.magFilter}
		, m_WrapU{info.wrapU}
		, m_WrapV{info.wrapV}
	{
		TextureFormat inFormat{};
		const void* pixels{};
		if (info.rawTexture)
		{
			m_Width = info.rawTexture->GetWidth();
			m_Height = info.rawTexture->GetHeight();
			inFormat = info.rawTexture->GetFormat();
			m_Format = !info.format ? inFormat : info.format;
			pixels = info.rawTexture->GetPixels();
		}
		else
		{
			m_Width = info.width;
			m_Height = info.height;
			m_Format = inFormat = info.format;
		}

		auto [internalFormat, format, type] = ConvertTextureFormatToOpenGL(m_Format, inFormat);
		auto [minFilter, magFilter] = ConvertTextureFilterModeToOpenGL(m_MinFilter, m_MagFilter);
		auto [wrapU, wrapV] = ConvertTextureWrapModeToOpenGL(m_WrapU, m_WrapV);

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, internalFormat, m_Width, m_Height);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, minFilter);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, magFilter);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, wrapU);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, wrapV);
		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, format, type, pixels);
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &m_RendererID);
	}

	auto OpenGLTexture2D::Bind(uint32_t location) const -> void
	{
		glBindTextureUnit(location, m_RendererID);
	}

	auto ConvertTextureFormatToOpenGL(TextureFormat internalFormat, TextureFormat format) -> std::tuple<GLint, GLenum, GLenum>
	{
		GBC_CORE_ASSERT_BOUNDED_ENUM_IS_VALID(TextureFormat, format);
		GBC_CORE_ASSERT_BOUNDED_ENUM_IS_VALID(TextureFormat, internalFormat);
		constexpr GLint internalFormats[]
		{
			GL_R8UI,    // TextureFormat::R_8U
			GL_R32UI,   // TextureFormat::R_32U
			GL_RGB8,    // TextureFormat::RGB_8U
			GL_RGBA8,   // TextureFormat::RGBA_8U
			GL_RGBA32F, // TextureFormat::RGBA_32F
		};
		constexpr std::pair<GLenum, GLenum> formats[]
		{
			{GL_RED_INTEGER, GL_UNSIGNED_BYTE}, // TextureFormat::R_8U
			{GL_RED_INTEGER, GL_UNSIGNED_INT }, // TextureFormat::R_32U
			{GL_RGB,         GL_UNSIGNED_BYTE}, // TextureFormat::RGB_8U
			{GL_RGBA,        GL_UNSIGNED_BYTE}, // TextureFormat::RGBA_8U
			{GL_RGBA,        GL_FLOAT        }, // TextureFormat::RGBA_32F
		};
		auto& fs{formats[format - TextureFormat::Begin]};
		return {internalFormats[internalFormat - TextureFormat::Begin], fs.first, fs.second};
	}

	auto ConvertTextureFilterModeToOpenGL(TextureFilterMode minFilter, TextureFilterMode magFilter) -> std::pair<GLint, GLint>
	{
		GBC_CORE_ASSERT_BOUNDED_ENUM_IS_VALID(TextureFilterMode, minFilter);
		GBC_CORE_ASSERT_BOUNDED_ENUM_IS_VALID(TextureFilterMode, magFilter);
		constexpr GLint filters[]
		{
			GL_LINEAR,  // TextureFilterMode::Linear
			GL_NEAREST, // TextureFilterMode::Nearest
		};
		return {filters[minFilter - TextureFilterMode::Begin], filters[magFilter - TextureFilterMode::Begin]};
	}

	auto ConvertTextureWrapModeToOpenGL(TextureWrapMode wrapU, TextureWrapMode wrapV) -> std::pair<GLint, GLint>
	{
		GBC_CORE_ASSERT_BOUNDED_ENUM_IS_VALID(TextureWrapMode, wrapU);
		GBC_CORE_ASSERT_BOUNDED_ENUM_IS_VALID(TextureWrapMode, wrapV);
		constexpr GLint wrapModes[]
		{
			GL_CLAMP_TO_EDGE, // TextureWrapMode::ClampToEdge
			GL_REPEAT,        // TextureWrapMode::Repeat
		};
		return {wrapModes[wrapU - TextureWrapMode::Begin], wrapModes[wrapV - TextureWrapMode::Begin]};
	}
}
