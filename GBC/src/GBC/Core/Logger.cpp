#include "gbcpch.h"
#include "Logger.h"
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace gbc
{
	Ref<spdlog::logger> s_CoreLogger;
	Ref<spdlog::logger> s_ClientLogger;

	auto Logger::Init() -> void
	{
		std::vector<spdlog::sink_ptr> sinks;
		sinks.emplace_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>())->set_pattern("%^[%T] %n: %v%$");
		sinks.emplace_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>("GBC.log", true))->set_pattern("[%T] [%l] %n: %v");

		s_CoreLogger = CreateRef<spdlog::logger>("GBC", sinks.begin(), sinks.end());
		spdlog::register_logger(s_CoreLogger);
		s_CoreLogger->set_level(spdlog::level::trace);
		s_CoreLogger->flush_on(spdlog::level::trace);

		s_ClientLogger = CreateRef<spdlog::logger>("APP", sinks.begin(), sinks.end());
		spdlog::register_logger(s_ClientLogger);
		s_ClientLogger->set_level(spdlog::level::trace);
		s_ClientLogger->flush_on(spdlog::level::trace);
	}

	auto Logger::GetCoreLogger() -> Ref<spdlog::logger>&
	{
		return s_CoreLogger;
	}

	auto Logger::GetClientLogger() -> Ref<spdlog::logger>&
	{
		return s_ClientLogger;
	}
}
