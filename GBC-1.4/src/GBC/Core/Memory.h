#pragma once

#include <memory>

namespace gbc
{
	template<typename T>
	using Ref = std::shared_ptr<T>;

	template<typename T, typename... Args>
	auto CreateRef(Args&&... args) -> Ref<T>
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	auto DestroyRef(Ref<T>& ref)
	{
		ref.reset();
	}



	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T, typename... Args>
	auto CreateScope(Args&&... args) -> Scope<T>
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}
}
