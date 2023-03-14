#pragma once

namespace gbc
{
	struct Timestep
	{
	public:
		constexpr Timestep(float seconds = 0.0f) noexcept : m_Seconds{seconds} {}
		constexpr auto operator=(float seconds) noexcept -> Timestep& { m_Seconds = seconds; return *this; }
		constexpr auto operator=(Timestep timestep) noexcept -> Timestep& { m_Seconds = timestep.m_Seconds; return *this; }
		constexpr operator float() const noexcept { return m_Seconds; }
	public:
		constexpr auto Seconds() const noexcept -> float { return m_Seconds; }
		constexpr auto Millis() const noexcept -> float { return m_Seconds * 1'000.0f; }
		constexpr auto Micros() const noexcept -> float { return m_Seconds * 1'000'000.0f; }
		constexpr auto Nanos() const noexcept -> float { return m_Seconds * 1'000'000'000.0f; }
	public:
		constexpr auto operator+ (Timestep timestep) const noexcept -> Timestep { return m_Seconds + timestep.m_Seconds; }
		constexpr auto operator+=(Timestep timestep) noexcept -> Timestep& { m_Seconds += timestep.m_Seconds; return *this; }
		constexpr auto operator- (Timestep timestep) const noexcept -> Timestep { return m_Seconds - timestep.m_Seconds; }
		constexpr auto operator-=(Timestep timestep) noexcept -> Timestep& { m_Seconds -= timestep.m_Seconds; return *this; }
		constexpr auto operator* (Timestep timestep) const noexcept -> Timestep { return m_Seconds * timestep.m_Seconds; }
		constexpr auto operator*=(Timestep timestep) noexcept -> Timestep& { m_Seconds *= timestep.m_Seconds; return *this; }
		constexpr auto operator/ (Timestep timestep) const noexcept -> Timestep { return m_Seconds / timestep.m_Seconds; }
		constexpr auto operator/=(Timestep timestep) noexcept -> Timestep& { m_Seconds /= timestep.m_Seconds; return *this; }
	private:
		float m_Seconds;
	};
}
