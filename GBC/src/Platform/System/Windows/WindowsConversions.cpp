#include "gbcpch.h"
#include "WindowsConversions.h"

namespace gbc
{
	auto ConvertMouseButtonToGLFW(MouseButton button) noexcept -> int32_t
	{
		GBC_CORE_ASSERT_BOUNDED_ENUM_IS_VALID(MouseButton, button);
		return static_cast<int32_t>(button) - 1;
	}

	auto ConvertKeycodeToGLFW(Keycode keycode) noexcept -> int32_t
	{
		GBC_CORE_ASSERT_BOUNDED_ENUM_IS_VALID(Keycode, keycode);
		return static_cast<int32_t>(keycode);
	}



	auto UnconvertMouseButtonFromGLFW(int32_t button) noexcept -> MouseButton
	{
		auto mouseButton{static_cast<MouseButton>(button + 1)};
		GBC_CORE_ASSERT_BOUNDED_ENUM_IS_VALID(MouseButton, mouseButton);
		return mouseButton;
	}

	auto UnconvertKeycodeFromGLFW(int32_t key) noexcept -> Keycode
	{
		auto keycode{static_cast<Keycode>(key)};
		GBC_CORE_ASSERT_BOUNDED_ENUM_IS_VALID(Keycode, keycode);
		return keycode;
	}

	auto UnconvertModifiersFromGLFW(int32_t mods) noexcept -> Modifiers
	{
		auto modifiers{static_cast<Modifiers>(mods)};
		GBC_CORE_ASSERT_MASKED_CLASS_ENUM_IS_VALID(Modifiers, modifiers);
		return modifiers;
	}
}
