#include "gbcpch.h"
#include "EventThread.h"
#include "GBC/Event/Events.h"

namespace gbc
{
	auto ConvertEventTypeToMetadata(EventType type) -> std::tuple<size_t, auto(*)(void*, Event&&) -> void, auto(*)(const void*) noexcept -> void>;

	EventThread::EventThread()
		: m_Thread{[this]()
		{
			while (!m_Exit)
			{
				// Wait for an event or destructor.
				std::unique_lock conditionLock{m_ConditionMutex};
				m_Condition.wait(conditionLock);
				if (m_Exit) break; // Only set on destruction.
				if (Empty()) continue;

				// Move current queue and use that to process, while
				// at the same time still accepting incoming events.
				// This allows events to be queued on the event thread.
				m_QueueMutex.lock();
				std::vector<uint8_t> queue{std::move(m_Queue)};
				std::vector<EventMetadata> queueMetadata{std::move(m_QueueMetadata)};
				m_QueueMutex.unlock();

				// Keep track of the current event.
				auto event{queue.data()};
				for (auto& metadata : queueMetadata)
				{
					// Call the function on the current event.
					m_EventCallback(*reinterpret_cast<Event*>(event), metadata.window);
					// Destruct the current event, since it's no longer needed.
					metadata.destructor(event);
					// Get the offset of the next event.
					event += metadata.size;
				}
			}
		}}
	{

	}

	EventThread::~EventThread()
	{
		std::lock_guard queueLock{m_QueueMutex};

		// Keep track of the current event.
		auto event{m_Queue.data()};
		for (auto& metadata : m_QueueMetadata)
		{
			// Destruct the current event.
			metadata.destructor(event);
			// Get the offset of the current event.
			event += metadata.size;
		}

		m_Queue.clear();
		m_QueueMetadata.clear();

		m_Exit = true;
		Notify();
	}

	auto EventThread::EnqueueEvent(Event& event, Window* window) -> void
	{
		m_QueueMutex.lock();

		// Create the new event's metadata.
		auto [size, constructor, destructor] = ConvertEventTypeToMetadata(event.GetType());
		EventMetadata& metadata{m_QueueMetadata.emplace_back(size, destructor, window)};
		// Allocate at least enough bytes to store the new event.
		m_Queue.resize(m_Queue.size() + metadata.size);
		// Get the address of the new event.
		auto eventAddress{m_Queue.data() + m_Queue.size() - metadata.size};
		// In-place move construct the new event.
		// The only reason for a move is the path drop event,
		// which has a std::vector<std::string>.
		constructor(eventAddress, std::move(event));

		m_QueueMutex.unlock();

		Notify();
	}

	auto EventThread::Empty() -> bool
	{
		std::lock_guard queueLock{m_QueueMutex};
		return m_Queue.empty();
	}

	auto EventThread::Notify() -> void
	{
		std::unique_lock conditionLock{m_ConditionMutex};
		m_Condition.notify_one();
	}

	auto ConvertEventTypeToMetadata(EventType type) -> std::tuple<size_t, auto(*)(void*, Event&&) -> void, auto(*)(const void*) noexcept -> void>
	{
		GBC_CORE_ASSERT_BOUNDED_ENUM_IS_VALID(EventType, type);

		// I got this (lambda containing destructor) idea from Herb Sutter.
#define EVENT_METADATA(e) {sizeof(e##Event), [](void* address, Event&& event) -> void { new (address) e##Event{static_cast<e##Event&&>(event)}; }, [](const void* event) noexcept -> void { static_cast<const e##Event*>(event)->~e##Event(); }}
		constexpr std::tuple<size_t, auto(*)(void*, Event&&) -> void, auto(*)(const void*) noexcept -> void> metadata[]
		{
			EVENT_METADATA(WindowClose),
			EVENT_METADATA(WindowResize),
			EVENT_METADATA(WindowMove),
			EVENT_METADATA(WindowFocus),
			EVENT_METADATA(WindowMinimize),
			EVENT_METADATA(WindowMaximize),
			EVENT_METADATA(WindowPathDrop),
			EVENT_METADATA(WindowFramebufferResize),
			EVENT_METADATA(WindowContentScale),
			EVENT_METADATA(WindowRefresh),
			EVENT_METADATA(KeyPress),
			EVENT_METADATA(KeyRepeat),
			EVENT_METADATA(KeyRelease),
			EVENT_METADATA(KeyCharType),
			EVENT_METADATA(MouseButtonPress),
			EVENT_METADATA(MouseButtonRelease),
			EVENT_METADATA(MouseMove),
			EVENT_METADATA(MouseScroll),
			EVENT_METADATA(MouseEnter)
		};
		return metadata[type - EventType::Begin];
	}
}
