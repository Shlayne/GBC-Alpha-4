#pragma once

#if GBC_CONFIG_PROFILE
	#define GBC_ENABLE_LOGGING 1
	#define GBC_ENABLE_VERIFYS 1
	#define GBC_ENABLE_ASSERTS 1
#elif GBC_CONFIG_DEBUG
	#define GBC_ENABLE_LOGGING 1
	#define GBC_ENABLE_VERIFYS 1
	#define GBC_ENABLE_ASSERTS 1
#elif GBC_CONFIG_RELEASE
	#define GBC_ENABLE_LOGGING 1
	#define GBC_ENABLE_VERIFYS 1
	#define GBC_ENABLE_ASSERTS 0
#elif GBC_CONFIG_DIST
	#define GBC_ENABLE_LOGGING 0
	#define GBC_ENABLE_VERIFYS 0
	#define GBC_ENABLE_ASSERTS 0
#endif

#define GBC_EXPAND(x) x
#define _GBC_STRINGIFY(x) #x
#define GBC_STRINGIFY(x) GBC_EXPAND(_GBC_STRINGIFY(x))
#define GBC_BIND_FUNC(func) [this](auto&&... args) -> decltype(auto) { return this->func(std::forward<decltype(args)>(args)...); }

#include "GBC/Core/Memory.h"
#include "GBC/Core/Logger.h"
#include "GBC/Core/AssertOrVerify.h"
#include "GBC/Core/DebugBreak.h"
#include "GBC/Core/Enums.h"
