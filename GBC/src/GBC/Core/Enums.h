#pragma once

#include "GBC/Core/AssertOrVerify.h"
#include <bit>
#include <concepts>

namespace gbc
{
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
		inline constexpr auto operator-(enumName e1, enumName e2) noexcept -> underlyingType { \
			return static_cast<underlyingType>(e1) - static_cast<underlyingType>(e2); \
		} \
		inline constexpr auto operator+(enumName e) noexcept -> underlyingType { \
			return static_cast<underlyingType>(e); \
		} \
		inline constexpr auto operator!(enumName e) noexcept -> bool { \
			return static_cast<underlyingType>(e) == static_cast<underlyingType>(enumName::None); \
		} \
		static_assert(static_cast<underlyingType>(enumName::End) > 1, #enumName " must have at least one enum value.")

	#define GBC_DEFINE_MASKED_ENUM(enumName, underlyingType, ...) \
		_GBC_DEFINE_MASKED_ENUM_IMPL(class enumName, underlyingType, __VA_ARGS__); \
		inline constexpr auto operator|(enumName e1, enumName e2) noexcept -> enumName { \
			return static_cast<enumName>(static_cast<underlyingType>(e1) | static_cast<underlyingType>(e2)); \
		} \
		inline constexpr auto operator&(enumName e1, enumName e2) noexcept -> enumName { \
			return static_cast<enumName>(static_cast<underlyingType>(e1) & static_cast<underlyingType>(e2)); \
		} \
		inline constexpr auto operator^(enumName e1, enumName e2) noexcept -> enumName { \
			return static_cast<enumName>(static_cast<underlyingType>(e1) ^ static_cast<underlyingType>(e2)); \
		} \
		inline constexpr auto operator~(enumName e) noexcept -> enumName { \
			return static_cast<enumName>(~static_cast<underlyingType>(e) & static_cast<underlyingType>(enumName::Mask)); \
		} \
		inline constexpr auto operator!(enumName e) noexcept -> bool { \
			return static_cast<underlyingType>(e) == static_cast<underlyingType>(enumName::None); \
		} \
		static_assert(static_cast<underlyingType>(enumName::End) > 1, #enumName " must have at least one enum value.")

	// NOTE: Not an enum class. This is an unscoped enum designed to be nested in a class.
	#define GBC_DEFINE_BOUNDED_CLASS_ENUM(className, underlyingType, ...) \
		_GBC_DEFINE_BOUNDED_ENUM_IMPL(, underlyingType, __VA_ARGS__); \
		static_assert(static_cast<underlyingType>(End) > 1, #className " must have at least one enum value.")

	// NOTE: Not an enum class. This is an unscoped enum designed to be nested in a class.
	#define GBC_DEFINE_MASKED_CLASS_ENUM(className, underlyingType, ...) \
		_GBC_DEFINE_MASKED_ENUM_IMPL(, underlyingType, __VA_ARGS__); \
		static_assert(static_cast<underlyingType>(End) > 1, #className " must have at least one enum value.")

	template<typename Enum>
	requires(std::is_enum_v<Enum>)
	inline constexpr auto IsBoundedEnumValid(Enum e) noexcept
	{
		return Enum::Begin <= e && e < Enum::End;
	}

	template<typename ClassEnum, typename Enum>
	requires(std::is_class_v<ClassEnum>)
	inline constexpr auto IsBoundedClassEnumValid(Enum e) noexcept
	{
		return ClassEnum::Begin <= e && e < ClassEnum::End;
	}

	template<typename Enum>
	requires(std::is_enum_v<Enum>)
	inline constexpr auto IsMaskedEnumValid(Enum e) noexcept
	{
		return (Enum::Mask & e) == e;
	}

	template<typename ClassEnum, typename Enum>
	requires(std::is_class_v<ClassEnum>)
	inline constexpr auto IsMaskedClassEnumValid(Enum e) noexcept
	{
		return (ClassEnum::Mask & e) == e;
	}

	// Common assert use case.
	#if GBC_ENABLE_ASSERTS
		#define GBC_CORE_ASSERT_BOUNDED_ENUM_IS_VALID(enumName, value) \
			GBC_CORE_ASSERT(::gbc::IsBoundedEnumValid(value), "Unknown " #enumName ".");
		#define GBC_CORE_ASSERT_BOUNDED_CLASS_ENUM_IS_VALID(classEnumName, value) \
			GBC_CORE_ASSERT(::gbc::IsBoundedClassEnumValid<classEnumName>(value), "Unknown " #classEnumName ".");
		#define GBC_CORE_ASSERT_MASKED_ENUM_IS_VALID(enumName, value) \
			GBC_CORE_ASSERT(::gbc::IsMaskedEnumValid(value), "Unknown " #enumName ".");
		#define GBC_CORE_ASSERT_MASKED_CLASS_ENUM_IS_VALID(classEnumName, value) \
			GBC_CORE_ASSERT(::gbc::IsMaskedClassEnumValid<classEnumName>(value), "Unknown " #classEnumName ".");
	#else
		#define GBC_CORE_ASSERT_BOUNDED_ENUM_IS_VALID(enumName, value)
		#define GBC_CORE_ASSERT_BOUNDED_CLASS_ENUM_IS_VALID(classEnumName, value)
		#define GBC_CORE_ASSERT_MASKED_ENUM_IS_VALID(enumName, value)
		#define GBC_CORE_ASSERT_MASKED_CLASS_ENUM_IS_VALID(classEnumName, value)
	#endif

	template<typename EnumIn, EnumIn BitIn, std::unsigned_integral UIntOut, UIntOut BitOut >
	requires(std::is_enum_v<EnumIn> && gbc::IsMaskedEnumValid(BitIn))
	inline constexpr UIntOut TranslateMaskedEnum(EnumIn value)
	{
		return (static_cast<UIntOut>(value & BitIn)
				>> std::countr_zero(static_cast<UIntOut>(BitIn)))
				<< std::countr_zero<UIntOut>(BitOut);
	}
}
