#pragma once

#include "GBC/Core/Core.h"
#include <spdlog/spdlog.h>

namespace gbc
{
	class Logger
	{
	public:
		static auto GetCoreLogger() -> Ref<spdlog::logger>&;
		static auto GetClientLogger() -> Ref<spdlog::logger>&;
	private:
		friend auto Main(int argc, char** argv) -> int;
		static auto Init() -> void;
	};
}

#if GBC_ENABLE_LOGGING
	#define GBC_CORE_TRACE(...) ::gbc::Logger::GetCoreLogger()->trace(__VA_ARGS__)
	#define GBC_CORE_DEBUG(...) ::gbc::Logger::GetCoreLogger()->debug(__VA_ARGS__)
	#define GBC_CORE_INFO(...)  ::gbc::Logger::GetCoreLogger()->info(__VA_ARGS__)
	#define GBC_CORE_WARN(...)  ::gbc::Logger::GetCoreLogger()->warn(__VA_ARGS__)
	#define GBC_CORE_ERROR(...) ::gbc::Logger::GetCoreLogger()->error(__VA_ARGS__)
	#define GBC_CORE_FATAL(...) ::gbc::Logger::GetCoreLogger()->critical(__VA_ARGS__)

	#define GBC_TRACE(...) ::gbc::Logger::GetClientLogger()->trace(__VA_ARGS__)
	#define GBC_DEBUG(...) ::gbc::Logger::GetClientLogger()->debug(__VA_ARGS__)
	#define GBC_INFO(...)  ::gbc::Logger::GetClientLogger()->info(__VA_ARGS__)
	#define GBC_WARN(...)  ::gbc::Logger::GetClientLogger()->warn(__VA_ARGS__)
	#define GBC_ERROR(...) ::gbc::Logger::GetClientLogger()->error(__VA_ARGS__)
	#define GBC_FATAL(...) ::gbc::Logger::GetClientLogger()->critical(__VA_ARGS__)
#else
	#define GBC_CORE_TRACE(...)
	#define GBC_CORE_DEBUG(...)
	#define GBC_CORE_INFO(...)
	#define GBC_CORE_WARN(...)
	#define GBC_CORE_ERROR(...)
	#define GBC_CORE_FATAL(...)

	#define GBC_TRACE(...)
	#define GBC_DEBUG(...)
	#define GBC_INFO(...)
	#define GBC_WARN(...)
	#define GBC_ERROR(...)
	#define GBC_FATAL(...)
#endif
