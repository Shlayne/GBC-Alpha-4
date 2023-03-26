#pragma once

#include "GBC/Core/Core.h"
#include <filesystem>

namespace gbc::io
{
	auto ReadFile(const std::filesystem::path& filepath) -> std::string;
}
