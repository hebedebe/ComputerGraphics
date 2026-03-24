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
}