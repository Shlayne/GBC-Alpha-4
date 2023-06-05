#pragma once

#include "GBC/Core/AssertOrVerify.h"
#include <bit>

#define _GBC_DEFINE_BOUNDED_ENUM_IMPL(enumClass, underlyingType, ...) \
	enum enumClass : underlyingType { \
		None = 0, \
		__VA_ARGS__, \
		End, \
		Begin = None + 1, \
		Count = End - Begin, \
		BitCount = std::bit_width(Count) \
	}

#define _GBC_DEFINE_MASKED_ENUM_IMPL(enumClass, underlyingType, ...) \
	enum enumClass : underlyingType { \
		None = 0, \
		__VA_ARGS__, \
		End, \
		Begin = 1 << 0, \
		Mask = (End << 1) - 3, \
		Count = std::countr_one(Mask), \
		BitCount = std::bit_width(Count) \
	}

#define GBC_DEFINE_BOUNDED_ENUM(enumName, underlyingType, ...) \
	_GBC_DEFINE_BOUNDED_ENUM_IMPL(class enumName, underlyingType, __VA_ARGS__); \
	inline constexpr underlyingType operator-(enumName e1, enumName e2) noexcept { \
		return static_cast<underlyingType>(e1) - static_cast<underlyingType>(e2); \
	} \
	static_assert(static_cast<underlyingType>(enumName::End) > 1, #enumName " must have at least one enum value.")

// TODO: make this if needed.
//#define GBC_DEFINE_MASKED_ENUM(enumName, underlyingType, ...)

// NOTE: Not an enum class. This is an unscoped enum designed to be nested in a class.
#define GBC_DEFINE_BOUNDED_CLASS_ENUM(className, underlyingType, ...) \
	_GBC_DEFINE_BOUNDED_ENUM_IMPL(, underlyingType, __VA_ARGS__); \
	static_assert(static_cast<underlyingType>(End) > 1, #className " must have at least one enum value.")

// NOTE: Not an enum class. This is an unscoped enum designed to be nested in a class.
#define GBC_DEFINE_MASKED_CLASS_ENUM(className, underlyingType, ...) \
	_GBC_DEFINE_MASKED_ENUM_IMPL(, underlyingType, __VA_ARGS__); \
	static_assert(static_cast<underlyingType>(End) > 1, #className " must have at least one enum value.")

#define GBC_BOUNDED_ENUM_IS_VALID(enumName, value) ((enumName::Begin) <= (value) && (value) < (enumName::End))
#define GBC_MASKED_ENUM_IS_VALID(enumName, value) (((enumName::Mask) & (value)) == (value))

// Common assert use case.
#if GBC_ENABLE_ASSERTS
	#define GBC_CORE_ASSERT_BOUNDED_ENUM_IS_VALID(enumName, value) \
		GBC_CORE_ASSERT(GBC_BOUNDED_ENUM_IS_VALID(enumName, value), "Unknown " #enumName ".");
	#define GBC_CORE_ASSERT_MASKED_ENUM_IS_VALID(enumName, value) \
		GBC_CORE_ASSERT(GBC_MASKED_ENUM_IS_VALID(enumName, value), "Unknown " #enumName ".");
#else
	#define GBC_CORE_ASSERT_BOUNDED_ENUM_IS_VALID(enumName, value)
	#define GBC_CORE_ASSERT_MASKED_ENUM_IS_VALID(enumName, value)
#endif
