#pragma once

template<typename T>
void Clamp(T& Num, const T Min, const T Max);

template<typename T>
inline void Clamp(T& Num, const T Min, const T Max) {
	Num = min(max(Num, Min), Max);
}
