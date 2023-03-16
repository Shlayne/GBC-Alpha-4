#pragma once

#include "GBC/Core/Application.h"
#include "GBC/Core/Keycodes.h"
#include "GBC/Core/MouseButtons.h"
#include "GBC/Event/Modifiers.h"

namespace gbc
{
	class Input
	{
	public:
		static auto IsKeyPressed(Keycode keycode, Window& window = Application::Get().GetWindow()) noexcept -> bool;
		static auto IsKeyReleased(Keycode keycode, Window& window = Application::Get().GetWindow()) noexcept -> bool;

		static auto IsMouseButtonPressed(MouseButton button, Window& window = Application::Get().GetWindow()) noexcept -> bool;
		static auto IsMouseButtonReleased(MouseButton button, Window& window = Application::Get().GetWindow()) noexcept -> bool;

		static auto GetRelativeMouseX(Window& window = Application::Get().GetWindow()) noexcept -> int32_t;
		static auto GetRelativeMouseY(Window& window = Application::Get().GetWindow()) noexcept -> int32_t;

		static auto GetAbsoluteMouseX() noexcept -> int32_t;
		static auto GetAbsoluteMouseY() noexcept -> int32_t;
	};
}
