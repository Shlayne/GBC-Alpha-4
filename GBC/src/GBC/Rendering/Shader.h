#pragma once

#include "GBC/Core/Core.h"
#include <string>
#include <vector>

namespace gbc
{
	GBC_DEFINE_BOUNDED_ENUM(
		ShaderType, uint8_t,

		Vertex,
		TessellationControl,
		TessellationEvaluation,
		Geometry,
		Fragment,
		Compute
	);

	struct ShaderSource
	{
		ShaderType type : ShaderType::BitCount {};
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
