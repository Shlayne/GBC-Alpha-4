#pragma once

#include "GBC/Core/Core.h"

namespace gbc
{
	struct ContextInfo
	{
		void* nativeWindow{};
	};

	class Context
	{
	public:
		static auto CreateScope(const ContextInfo& info) -> Scope<Context>;
		virtual ~Context() = default;
	public:
		virtual auto SwapBuffers() -> void = 0;
	};
}
