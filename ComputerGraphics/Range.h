#pragma once
#include <cstdlib>

template<typename T>
struct Range
{
	T max;
	T min;

public:
	T Rand() const { return T(static_cast<float>(rand())) / T(RAND_MAX) / (max - min); }

public:
	Range(T single) : max(single), min(single) {}
	Range(T min, T max): max(max), min(min){}
};
