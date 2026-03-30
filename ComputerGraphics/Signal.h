#pragma once

#include <functional>
#include <map>

#define _SIGNAL_FUNC std::function<void(Args...)>

template <typename... Args>
class Signal final
{
public:
	Signal();

public:
	void Connect(void* source, _SIGNAL_FUNC func);
	void ConnectOneshot(_SIGNAL_FUNC func);
	void Disconnect(void* source);

	void Emit(Args... args);

protected:
	std::map<void*, _SIGNAL_FUNC> m_connections;
	std::vector<void*> m_oneshots;
};

#include "Signal.inl"