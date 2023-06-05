#pragma once

#include "GBC/Core/Core.h"
#include <filesystem>

// TODO: remove this file when asset system exists.

namespace gbc::io
{
	auto ReadFile(const std::filesystem::path& filepath) -> std::string;
}
