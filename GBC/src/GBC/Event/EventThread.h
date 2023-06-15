#pragma once

#include "GBC/Event/Event.h"
#include <thread>
#include <mutex>

namespace gbc
{
	class Window;

	class EventThread
	{
	public:
		EventThread();
		~EventThread();
	public:
		// Actually, moves the event, but shh.
		auto EnqueueEvent(Event& event, Window* window) -> void;
	public:
		inline auto SetEventCallback(const EventCallback& callback) -> void { m_EventCallback = callback; }
	private:
		auto Empty() -> bool;
		auto Notify() -> void;
	private:
		EventCallback m_EventCallback;
		std::jthread m_Thread;
		std::mutex m_ConditionMutex;
		std::condition_variable m_Condition;
		std::atomic_bool m_Exit;
	private:
		struct EventMetadata
		{
			size_t size{};
			auto(*destructor)(const void*) noexcept -> void {};
			Window* window{};
		};

		std::recursive_mutex m_QueueMutex;
		std::vector<uint8_t> m_Queue;
		std::vector<EventMetadata> m_QueueMetadata;
	};
}
