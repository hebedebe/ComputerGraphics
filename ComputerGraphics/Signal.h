#pragma once

#include <functional>
#include <map>
#include <ranges>

#define _SIGNAL_FUNC std::function<void(Args...)>

template <typename... Args>
class Signal final
{
public:
	Signal() = default;
	~Signal() = default;

public:
	void Connect(void* source, _SIGNAL_FUNC func);
	void Disconnect(void* source);

	void Emit(Args... args);

protected:
	std::map<void*, _SIGNAL_FUNC> m_connections;
};

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
	for (_SIGNAL_FUNC &func : m_connections | std::views::values)
	{
		func(args...);
	}
}
