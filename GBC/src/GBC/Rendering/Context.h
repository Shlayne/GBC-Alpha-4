#pragma once

#include "GBC/Core/Core.h"

namespace gbc
{
	class Context
	{
	public:
		static Scope<Context> CreateScope(void* nativeWindow);
		virtual ~Context() = default;
	public:
		virtual auto SwapBuffers() -> void = 0;
	};
}
