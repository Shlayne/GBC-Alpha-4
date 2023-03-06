#pragma once

#include <cstdint>

namespace gbc
{
	enum Modifiers_ : uint8_t
	{
		Modifiers_None     = 0,
		Modifiers_Control  = 1 << 0,
		Modifiers_Shift    = 1 << 1,
		Modifiers_Alt      = 1 << 2,
		Modifiers_Super    = 1 << 3,
		Modifiers_CapsLock = 1 << 4,
		Modifiers_NumLock  = 1 << 5,

		// Automatically creates the modifiers mask.
		Modifiers_Last, Modifiers_All = (Modifiers_Last << 1) - 3
	};

	class Modifiers
	{
	public:
		constexpr Modifiers() noexcept = default;
		constexpr Modifiers(Modifiers_ modifiers) noexcept : m_Modifiers(Mask(modifiers)) {}
		constexpr Modifiers(uint8_t modifiers) noexcept : m_Modifiers(Mask(modifiers)) {}

		constexpr auto Has(Modifiers_ modifiers) const noexcept -> bool { return m_Modifiers & modifiers; }
		constexpr auto Has(uint8_t modifiers) const noexcept -> bool { return Has(static_cast<Modifiers_>(modifiers)); }
		constexpr auto Are(Modifiers_ modifiers) const noexcept -> bool { return (m_Modifiers & modifiers) == m_Modifiers; }
		constexpr auto Are(uint8_t modifiers) const noexcept -> bool { return Are(static_cast<Modifiers_>(modifiers)); }

		constexpr operator uint8_t() const noexcept { return m_Modifiers; }

		constexpr auto None() const noexcept -> bool { return m_Modifiers == Modifiers_None; }
		constexpr auto operator!() const noexcept -> bool { return None(); }
		constexpr explicit operator bool() const noexcept { return !None(); }
	private:
		static constexpr auto Mask(uint8_t modifiers) noexcept -> Modifiers_ { return static_cast<Modifiers_>(modifiers & Modifiers_All); }
	private:
		Modifiers_ m_Modifiers{Modifiers_None};
	};
}
