#pragma once

#include "GBC/Core/Core.h"

#if GBC_ENABLE_ASSERTS || GBC_ENABLE_VERIFYS
	#include "GBC/Core/DebugBreak.h"
	#include "GBC/Core/Logger.h"
	#include <filesystem>

	#define _GBC_ASSERT_OR_VERIFY(which, type, condition, ...) \
		do \
		{ \
			if (!(condition)) \
			{ \
				GBC##type##ERROR(#which " (" #condition ") failed at {}:{}", std::filesystem::relative(__FILE__, std::filesystem::current_path().parent_path()).string(), __LINE__); \
				__VA_OPT__(GBC##type##ERROR(__VA_ARGS__);) \
				GBC_DEBUG_BREAK(); \
			} \
		} \
		while (false)
#endif

#if GBC_ENABLE_ASSERTS
	#define GBC_CORE_ASSERT(condition, ...) GBC_EXPAND(_GBC_ASSERT_OR_VERIFY(Assertion, _CORE_, condition __VA_OPT__(,) __VA_ARGS__))
	#define GBC_ASSERT(condition, ...) GBC_EXPAND(_GBC_ASSERT_OR_VERIFY(Assertion, _, condition __VA_OPT__(,) __VA_ARGS__))
#else
	#define GBC_CORE_ASSERT(condition, ...)
	#define GBC_ASSERT(condition, ...)
#endif

#if GBC_ENABLE_VERIFYS
	#define GBC_CORE_VERIFY(condition, ...) GBC_EXPAND(_GBC_ASSERT_OR_VERIFY(Verification, _CORE_, condition __VA_OPT__(,) __VA_ARGS__))
	#define GBC_VERIFY(condition, ...) GBC_EXPAND(_GBC_ASSERT_OR_VERIFY(Verification, _, condition __VA_OPT__(,) __VA_ARGS__))
#else
	#define GBC_CORE_VERIFY(condition, ...) condition
	#define GBC_VERIFY(condition, ...) condition
#endif
