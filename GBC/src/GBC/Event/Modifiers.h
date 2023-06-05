#pragma once

#include "GBC/Core/Core.h"

// Taken from glfw3.h and modified

namespace gbc
{
	class Modifiers
	{
	public:
		GBC_DEFINE_MASKED_CLASS_ENUM(
			Modifiers, uint8_t,

			Shift    = 1 << 0,
			Control  = 1 << 1,
			Alt      = 1 << 2,
			Super    = 1 << 3,
			CapsLock = 1 << 4,
			NumLock  = 1 << 5
		);
	public:
		constexpr Modifiers() noexcept = default;
		constexpr Modifiers(uint8_t modifiers) noexcept : m_Modifiers(modifiers & Mask) {}

		constexpr auto Has(uint8_t modifiers) const noexcept -> bool { return m_Modifiers & modifiers; }
		constexpr auto Are(uint8_t modifiers) const noexcept -> bool { return (m_Modifiers & modifiers) == m_Modifiers; }

		constexpr operator uint8_t() const noexcept { return m_Modifiers; }

		constexpr auto operator!() const noexcept -> bool { return m_Modifiers == None; }
		constexpr explicit operator bool() const noexcept { return !*this; }
	private:
		uint8_t m_Modifiers{};
	};
}
