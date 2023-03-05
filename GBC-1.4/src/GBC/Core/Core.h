#pragma once

#if GBC_CONFIG_PROFILE
	#define GBC_ENABLE_LOGGING 1
#elif GBC_CONFIG_DEBUG
	#define GBC_ENABLE_LOGGING 1
#elif GBC_CONFIG_RELEASE
	#define GBC_ENABLE_LOGGING 1
#elif GBC_CONFIG_DIST
	#define GBC_ENABLE_LOGGING 0
#endif

#include "GBC/Core/Memory.h"
#include "GBC/Core/Logger.h"
