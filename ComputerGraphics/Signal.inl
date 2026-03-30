#pragma once
#include <ranges>

template <typename... Args>
Signal<Args...>::Signal() = default;

template<typename ...Args>
inline void Signal<Args...>::Connect(void* source, _SIGNAL_FUNC func)
{
	m_connections[source] = func;
}

template <typename ... Args>
void Signal<Args...>::ConnectOneshot(std::function<void(Args...)> func)
{
	void* tempAddr = malloc(8);
	Connect(tempAddr, func);
	m_oneshots.emplace_back(tempAddr);
	free(tempAddr);
}

template <typename ... Args>
void Signal<Args...>::Disconnect(void* source)
{
	m_connections.erase(source);
}

template <typename ... Args>
void Signal<Args...>::Emit(Args ...args)
{
	for (_SIGNAL_FUNC& func : m_connections | std::views::values)
	{
		func(args...);
	}

	if (m_oneshots.empty()) return;

	for (void* tempAddr : m_oneshots)
	{
		Disconnect(tempAddr);
	}
	m_oneshots.clear();
}