#pragma once
#include <vector>
#include <unordered_map>
#include "EventListener.h"


namespace Sonic {

	class EventDispatcher
	{
	private:
		template<typename Event>
		struct ListenerContainer
		{
			std::unordered_map<intptr_t, size_t> keys;
			std::vector<EventListener<Event>> listeners;

			ListenerContainer()
			{
				s_ClearFunctions.push_back([this]() {
					keys.clear();
					listeners.clear();
				});
			}
		};

		EventDispatcher() = delete;
		EventDispatcher(const EventDispatcher& other) = delete;
		EventDispatcher& operator=(const EventDispatcher& other) = delete;

		static void clear();

	public:
		template<typename Event>
		static void addListener(EventListener<Event> listener)
		{
			getListeners<Event>().listeners.push_back(listener);
		}

		template<typename F, typename Event>
		static void addListener(F* object, void(F::* method)(const Event&))
		{
			addListener(EventListener<Event>([object, method](const Event& e) { (object->*method)(e); }));
		}

		template<typename F, typename Event>
		static void addRemovableListener(F* object, void(F::* method)(const Event&))
		{
			addListener(object, method);

			auto& keys = getListeners<Event>().keys;
			keys.emplace(reinterpret_cast<intptr_t>(object), getListeners<Event>().listeners.size() - 1);
		}

		template<typename Event, typename F>
		static void removeListener(F* object)
		{
			auto& listeners = getListeners<Event>().listeners;
			auto& keys = getListeners<Event>().keys;
			auto it = keys.find(reinterpret_cast<intptr_t>(object));

			for (auto& [_, index] : keys)
				if (index > it->second)
					index--;

			listeners.erase(listeners.begin() + it->second);
			keys.erase(it);
		}

		template<typename Event>
		static void dispatch(const Event& e)
		{
			for (auto& listener : getListeners<Event>().listeners)
				listener(e);
		}

	private:
		template<typename Event>
		static ListenerContainer<Event>& getListeners()
		{
			static ListenerContainer<Event> listeners;
			return listeners;
		}

		static std::vector<std::function<void()>> s_ClearFunctions;

		friend class SceneManager;
	};

}
