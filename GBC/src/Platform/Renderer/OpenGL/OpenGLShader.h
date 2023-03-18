#pragma once

#include "GBC/Rendering/Shader.h"

namespace gbc
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const ShaderInfo& info);
		virtual ~OpenGLShader();
	public:
		virtual auto Bind() -> void override;
	private:
		uint32_t m_RendererID{0};
	};
}
