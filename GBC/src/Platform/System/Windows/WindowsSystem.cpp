#include "gbcpch.h"
#include "GBC/Core/System.h"
#define GLFW_INCLUDE_NONE
#include <glfw/glfw3.h>

namespace gbc
{
	// Miscellaneous Callbacks
#if GBC_ENABLE_LOGGING
	static auto ErrorCallback(int errorCode, const char* description) -> void;
#endif

	auto System::Init() -> void
	{
		// TODO: profile function

		GBC_CORE_VERIFY(glfwInit(), "Failed to initialize GLFW.");

		// Miscellaneous Callbacks
#if GBC_ENABLE_LOGGING
		glfwSetErrorCallback(&ErrorCallback);
#endif
		// TODO: monitor and joystick callbacks would go here.
	}

	auto System::Shutdown() -> void
	{
		// TODO: profile function
		glfwTerminate();
	}

	auto System::PollEvents() -> void
	{
		// TODO: profile function
		glfwPollEvents();
	}

	auto System::GetTimestep() -> Timestep
	{
		static double lastTime{0.0};
		double currentTime{glfwGetTime()};
		Timestep timestep{static_cast<float>(currentTime - lastTime)};
		lastTime = currentTime;
		return timestep;
	}

	// Miscellaneous Callbacks

#if GBC_ENABLE_LOGGING
	static auto ErrorCallback(int errorCode, const char* description) -> void
	{
		GBC_CORE_ERROR("GLFW Error ({}): {}", errorCode, description);
	}
#endif
}
