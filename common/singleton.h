#pragma once

template<class T>
class Singleton
{
public:
	static T* Get() 
	{
	   	if(ms_Instance == nullptr)
	   	{
			ms_Instance = new T;
	   	}	   
		return ms_Instance; 
	}

	static void Destroy()
	{
		ms_Instance = nullptr;
		delete ms_Instance;
	}
protected:
	Singleton<T>() {}
	static T* ms_Instance;

private:
	Singleton<T>(const Singleton<T>& other) = delete;
	Singleton<T> operator=(const Singleton<T>& other) = delete;
};

template<class T>
T* Singleton<T>::ms_Instance{ nullptr };
