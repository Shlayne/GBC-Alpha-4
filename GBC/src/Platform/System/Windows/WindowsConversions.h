#pragma once

#include "GBC/Core/Keycodes.h"
#include "GBC/Core/Modifiers.h"
#include "GBC/Core/MouseButtons.h"

namespace gbc
{
	auto ConvertMouseButtonToGLFW(MouseButton button) noexcept -> int32_t;
	auto ConvertKeycodeToGLFW(Keycode keycode) noexcept -> int32_t;

	auto UnconvertMouseButtonFromGLFW(int32_t button) noexcept -> MouseButton;
	auto UnconvertKeycodeFromGLFW(int32_t key) noexcept -> Keycode;
	auto UnconvertModifiersFromGLFW(int32_t mods) noexcept -> Modifiers;
}
