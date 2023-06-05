#include "gbcpch.h"
#include "GBC/Core/Input.h"
#define GLFW_INCLUDE_NONE
#include <glfw/glfw3.h>

namespace gbc
{
	auto ConvertMouseButtonToGLFW(MouseButton button) noexcept -> int32_t;
	auto GetKeyState(Window& window, Keycode keycode) noexcept -> int32_t;
	auto GetMouseButtonState(Window& window, MouseButton button) noexcept -> int32_t;
	auto GetMousePosition(Window& window, double* x, double* y) noexcept -> void;
	auto GetWindowPosition(Window& window, int32_t* x, int32_t* y) noexcept -> void;

	auto Input::IsKeyPressed(Keycode keycode, Window& window) noexcept -> bool
	{
		return GetKeyState(window, keycode) != GLFW_RELEASE;
	}

	auto Input::IsKeyReleased(Keycode keycode, Window& window) noexcept -> bool
	{
		return GetKeyState(window, keycode) == GLFW_RELEASE;
	}

	auto Input::IsMouseButtonPressed(MouseButton button, Window& window) noexcept -> bool
	{
		return GetMouseButtonState(window, button) != GLFW_RELEASE;
	}

	auto Input::IsMouseButtonReleased(MouseButton button, Window& window) noexcept -> bool
	{
		return GetMouseButtonState(window, button) == GLFW_RELEASE;
	}

	auto Input::GetRelativeMouseX(Window& window) noexcept -> int32_t
	{
		double x{};
		GetMousePosition(window, &x, nullptr);
		return static_cast<int32_t>(x);
	}

	auto Input::GetRelativeMouseY(Window& window) noexcept -> int32_t
	{
		double y{};
		GetMousePosition(window, nullptr, &y);
		return static_cast<int32_t>(y);
	}

	auto Input::GetRelativeMousePos(Window& window) noexcept -> glm::ivec2
	{
		glm::dvec2 mousePos{};
		GetMousePosition(window, &mousePos.x, &mousePos.y);
		return mousePos;
	}

	auto Input::GetAbsoluteMouseX() noexcept -> int32_t
	{
		int32_t windowX{};
		GetWindowPosition(Application::Get().GetWindow(), &windowX, nullptr);
		return windowX + GetRelativeMouseX();
	}

	auto Input::GetAbsoluteMouseY() noexcept -> int32_t
	{
		int32_t windowY{};
		GetWindowPosition(Application::Get().GetWindow(), nullptr, &windowY);
		return windowY + GetRelativeMouseY();
	}

	auto Input::GetAbsoluteMousePos() noexcept -> glm::ivec2
	{
		glm::dvec2 mousePos{};
		glm::ivec2 windowPos{};
		Window& window{Application::Get().GetWindow()};
		GetMousePosition(window, &mousePos.x, &mousePos.y);
		GetWindowPosition(window, &windowPos.x, &windowPos.y);
		return windowPos += mousePos;
	}

	auto ConvertMouseButtonToGLFW(MouseButton button) noexcept -> int32_t
	{
		GBC_CORE_ASSERT_BOUNDED_ENUM_IS_VALID(MouseButton, button);
		return +button - 1;
	}

	auto GetKeyState(Window& window, Keycode keycode) noexcept -> int32_t
	{
		return glfwGetKey(static_cast<GLFWwindow*>(window.GetNativeWindow()), static_cast<int32_t>(keycode));
	}

	auto GetMouseButtonState(Window& window, MouseButton button) noexcept -> int32_t
	{
		return glfwGetMouseButton(static_cast<GLFWwindow*>(window.GetNativeWindow()), ConvertMouseButtonToGLFW(button));
	}

	auto GetMousePosition(Window& window, double* x, double* y) noexcept -> void
	{
		glfwGetCursorPos(static_cast<GLFWwindow*>(window.GetNativeWindow()), x, y);
	}

	auto GetWindowPosition(Window& window, int32_t* x, int32_t* y) noexcept -> void
	{
		glfwGetWindowPos(static_cast<GLFWwindow*>(window.GetNativeWindow()), x, y);
	}
}
