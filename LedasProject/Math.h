#pragma once
#include <cmath>

template<typename T>
bool IsEqualsZero(T expr)
{
	return abs(expr) <= 0.00000000001;
}