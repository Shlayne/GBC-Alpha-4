#pragma once

#include "GBC/Core/Core.h"
#include "GBC/Core/Timestep.h"

namespace gbc
{
	class System
	{
	public:
		static auto Init() -> void;
		static auto Shutdown() -> void;
		static auto PollEvents() -> void;
		static auto GetTimestep() -> Timestep;
	};
}
