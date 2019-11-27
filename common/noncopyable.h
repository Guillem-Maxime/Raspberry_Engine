#pragma once

template<class T>
class NonCopyable
{
	public:
		NonCopyable<T>() = default;
		NonCopyable<T>(const NonCopyable<T>& other) = delete;
		NonCopyable<T> operator=(const NonCopyable<T>& other) = delete;
		virtual ~NonCopyable<T>() {}
};
