#pragma once

#include "noncopyable.h"

template<class T>
class NonMovable : public NonCopyable<T>
{
	public:
		NonMovable<T>() = default;
		NonMovable<T>(const NonMovable<T>&& other) = delete;
		NonMovable<T> operator=(const NonMovable<T>&& other) = delete;
		virtual ~NonMovable<T>() {}
};
