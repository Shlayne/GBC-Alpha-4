#pragma once

#include "GBC/Core/Core.h"

#if GBC_CONFIG_DEBUG
	#if GBC_SYSTEM_WINDOWS
		#define GBC_DEBUG_BREAK() __debugbreak()
	#endif
#else
	#define GBC_DEBUG_BREAK()
#endif
