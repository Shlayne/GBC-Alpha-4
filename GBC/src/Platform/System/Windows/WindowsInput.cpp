#include "gbcpch.h"
#include "GBC/Core/Input.h"
#define GLFW_INCLUDE_NONE
#include <glfw/glfw3.h>

namespace gbc
{
	static auto GetKeyState(Keycode keycode, Window& window) noexcept -> int
	{
		return glfwGetKey(static_cast<GLFWwindow*>(window.GetNativeWindow()), static_cast<int>(keycode));
	}

	static auto GetMouseButtonState(MouseButton button, Window& window) noexcept -> int
	{
		return glfwGetMouseButton(static_cast<GLFWwindow*>(window.GetNativeWindow()), static_cast<int>(button));
	}

	static auto GetMousePosition(Window& window, double* x, double* y) noexcept -> void
	{
		glfwGetCursorPos(static_cast<GLFWwindow*>(window.GetNativeWindow()), x, y);
	}

	static auto GetWindowPosition(Window& window, int32_t* x, int32_t* y) noexcept -> void
	{
		glfwGetWindowPos(static_cast<GLFWwindow*>(window.GetNativeWindow()), x, y);
	}

	auto Input::IsKeyPressed(Keycode keycode, Window& window) noexcept -> bool
	{
		return GetKeyState(keycode, window) != GLFW_RELEASE;
	}

	auto Input::IsKeyReleased(Keycode keycode, Window& window) noexcept -> bool
	{
		return GetKeyState(keycode, window) == GLFW_RELEASE;
	}

	auto Input::IsMouseButtonPressed(MouseButton button, Window& window) noexcept -> bool
	{
		return GetMouseButtonState(button, window) != GLFW_RELEASE;
	}

	auto Input::IsMouseButtonReleased(MouseButton button, Window& window) noexcept -> bool
	{
		return GetMouseButtonState(button, window) == GLFW_RELEASE;
	}

	auto Input::GetRelativeMouseX(Window& window) noexcept -> int32_t
	{
		double x{0.0};
		GetMousePosition(window, &x, nullptr);
		return static_cast<int32_t>(x);
	}

	auto Input::GetRelativeMouseY(Window& window) noexcept -> int32_t
	{
		double y{0.0};
		GetMousePosition(window, nullptr, &y);
		return static_cast<int32_t>(y);
	}

	auto Input::GetRelativeMousePos(Window& window) noexcept -> glm::ivec2
	{
		glm::dvec2 mousePos{0.0};
		GetMousePosition(window, &mousePos.x, &mousePos.y);
		return mousePos;
	}

	auto Input::GetAbsoluteMouseX() noexcept -> int32_t
	{
		int32_t windowX{0};
		GetWindowPosition(Application::Get().GetWindow(), &windowX, nullptr);
		return static_cast<int32_t>(windowX + GetRelativeMouseX());
	}

	auto Input::GetAbsoluteMouseY() noexcept -> int32_t
	{
		int32_t windowY{0};
		GetWindowPosition(Application::Get().GetWindow(), nullptr, &windowY);
		return static_cast<int32_t>(windowY + GetRelativeMouseY());
	}

	auto Input::GetAbsoluteMousePos() noexcept -> glm::ivec2
	{
		glm::dvec2 mousePos{0.0};
		glm::ivec2 windowPos{0};
		Window& window{Application::Get().GetWindow()};
		GetMousePosition(window, &mousePos.x, &mousePos.y);
		GetWindowPosition(window, &windowPos.x, &windowPos.y);
		return windowPos += mousePos;
	}
}
