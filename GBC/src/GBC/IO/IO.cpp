#include "gbcpch.h"
#include "IO.h"

// TODO: remove this file when asset system exists.

namespace gbc::io
{
	auto ReadFile(const std::filesystem::path& filepath) -> std::string
	{
		std::ifstream file{filepath};
		if (file.is_open())
		{
			std::stringstream stream;
			stream << file.rdbuf();
			file.close();
			return stream.str();
		}
		return {};
	}
}
