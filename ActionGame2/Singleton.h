#pragma once

template <typename T>
class Singleton
{
protected:
	Singleton() {};
	Singleton(const Singleton&) = delete;
	Singleton operator=(const Singleton&) = delete;

public:
	static T& GetInstance()
	{
		static T instance;
		return instance;
	}

};
