#pragma once

#include "GBC/Core/Core.h"

namespace gbc
{
	class Context
	{
	public:
		static auto CreateScope(void* nativeWindow) -> Scope<Context>;
		virtual ~Context() = default;
	public:
		virtual auto SwapBuffers() -> void = 0;
	};
}
