#pragma once

#include "GBC/Core/Core.h"

#if GBC_ENABLE_ASSERTS || GBC_ENABLE_VERIFYS
	#include "GBC/Core/DebugBreak.h"
	#include "GBC/Core/Logger.h"

	#define _GBC_ASSERT_OR_VERIFY(which, type, condition, message, ...) \
		do \
		{ \
			if (!(condition)) \
			{ \
				GBC##type##ERROR(#which " ({0}) failed at {1}:{2}", (condition), __FILE__, __LINE__); \
				GBC##type##ERROR(message __VA_OPT__(,) __VA_ARGS__); \
				GBC_DEBUG_BREAK(); \
			} \
		} \
		while (false)
#endif

#if GBC_ENABLE_ASSERTS
	#define GBC_CORE_ASSERT(condition, message, ...) GBC_EXPAND(_GBC_ASSERT_OR_VERIFY(Assertion, _CORE_, condition, message __VA_OPT__(,) __VA_ARGS__))
	#define GBC_ASSERT(condition, message, ...) GBC_EXPAND(_GBC_ASSERT_OR_VERIFY(Assertion, _, condition, message __VA_OPT__(,) __VA_ARGS__))
#else
	#define GBC_CORE_ASSERT(condition, message, ...)
	#define GBC_ASSERT(condition, message, ...)
#endif

#if GBC_ENABLE_VERIFYS
	#define GBC_CORE_VERIFY(condition, message, ...) GBC_EXPAND(_GBC_ASSERT_OR_VERIFY(Verification, _CORE_, condition, message __VA_OPT__(,) __VA_ARGS__))
	#define GBC_VERIFY(condition, message, ...) GBC_EXPAND(_GBC_ASSERT_OR_VERIFY(Verification, _, condition, message __VA_OPT__(,) __VA_ARGS__))
#else
	#define GBC_CORE_VERIFY(condition, message, ...) condition
	#define GBC_VERIFY(condition, message, ...) condition
#endif
