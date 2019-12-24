#pragma once

#include "common/commonheaders.h"

namespace TemplateUtils
{
	template<class T>
	struct TypeOf
	{
		typedef T type;
	};

	template<class T>
	struct PtrTypeOf
	{
		typedef T* type;
	};

	template<class T*>
	struct TypePointed
	{
		typedef T type;
	};

	template<class T>
	TypeOf<T> GetTypeOfUniquePtr(const std::unique_ptr<T>& value)
	{
		return TypeOf<T>();
	}

	template<class T>
	TypeOf<T> GetTypeOfPtr(const T*& value)
	{
		return TypeOf<T>();
	}

	template<class T>
	TypeOf<T> GetTypeOf(const T&)
	{
		return TypeOf<T>();
	}

	template<class T*>
	TypeOf<T> GetTypePointedOf(const T*& value)
	{
		return TypeOf<T>();
	}	

	template<class T, class U>
	struct SameType
	{
		static constexpr bool value = false;
	};

	template<class T>
	struct SameType<T, T>
	{
		static constexpr bool value = true;
	};
	

}//TemplateUtils
