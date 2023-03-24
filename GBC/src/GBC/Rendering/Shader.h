#pragma once

#include "GBC/Core/Core.h"
#include <string>
#include <vector>

namespace gbc
{
	using ShaderType = uint8_t;
	enum : ShaderType
	{
		ShaderType_None,
		ShaderType_Vertex,
		ShaderType_TessellationControl,
		ShaderType_TessellationEvaluation,
		ShaderType_Geometry,
		ShaderType_Fragment,
		ShaderType_Compute
	};

	struct ShaderSource
	{
		ShaderType type{ShaderType_None};
		std::string code;
	};

	struct ShaderInfo
	{
		std::vector<ShaderSource> sources;
	};

	class Shader
	{
	public:
		static auto CreateRef(const ShaderInfo& info) -> Ref<Shader>;
		virtual ~Shader() = default;
	public:
		virtual auto Bind() const -> void = 0;
	};
}
