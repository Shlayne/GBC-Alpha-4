#pragma once

#include "GBC/Core/Core.h"
#include "GBC/Rendering/VertexArray.h"
#include "GBC/Rendering/Shader.h"
#include <glm/glm.hpp>

namespace gbc
{
	class Renderer
	{
	public:
		static auto Init() -> void;
		static auto Shutdown() -> void;

		static auto BeginScene(const glm::mat4& viewProjection) -> void;
		static auto EndScene() -> void;

		static auto Submit(const Ref<VertexArray>& vertexArray, const Ref<Shader>& shader) -> void;
	};
}
