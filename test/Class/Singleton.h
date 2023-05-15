#pragma once
template<class T>
class StaticSingleton
{
public:
	static T& GetInstance(void)
	{
		static T instance;
		return instance;
	}

	StaticSingleton(const StaticSingleton& obj) = delete;//コピーコンストラクタ禁止
	StaticSingleton& operator=(const StaticSingleton& obj) = delete;//代入演算子禁止
	StaticSingleton(const StaticSingleton&& obj) = delete;//ムーブコンストラクタ禁止
	StaticSingleton& operator=(const StaticSingleton&& obj) = delete;//ムーブ代入禁止
protected:
	StaticSingleton() = default;
	virtual ~StaticSingleton();
private:
};

template <class T>
StaticSingleton<T>::~StaticSingleton() = default;

template<class T>
class DynamicSingleton
{
public:
	static T& GetInstance()
	{
		if (instance_ == nullptr)
		{
			Create();
		}
		return *instance_;
	}

	static void Create()
	{
		if (instance_ == nullptr)
		{
			instance_ = new T;
		}
	}

	static void Destroy()
	{
		if (instance_ != nullptr)
		{
			delete instance_;
			instance_ = nullptr;
		}
	}

	DynamicSingleton(const DynamicSingleton& obj) = delete;//コピーコンストラクタ禁止
	DynamicSingleton& operator=(const DynamicSingleton& obj) = delete;//代入演算子禁止
	DynamicSingleton(const DynamicSingleton&& obj) = delete;//ムーブコンストラクタ禁止
	DynamicSingleton& operator=(const DynamicSingleton&& obj) = delete;//ムーブ代入禁止
protected:
	DynamicSingleton() = default;
	virtual ~DynamicSingleton();
private:
	static T* instance_;
};

template <class T>
DynamicSingleton<T>::~DynamicSingleton() = default;

template <typename T> T* DynamicSingleton<T>::instance_ = nullptr;
