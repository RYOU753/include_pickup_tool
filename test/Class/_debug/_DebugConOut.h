#pragma once
#ifdef _DEBUG
#include <windows.h>
#include <memory>
#include <assert.h>
#include <iostream>
#include <string_view>
// ÃÞÊÞ¯¸ÞÒ¯¾°¼Þ—p’è‹`

#define lpDebugConOut _DebugConOut::GetInstance()
#define TRACE(fmt, ...) lpDebugConOut.PrintF(fmt, __VA_ARGS__)
#define TRACELN(fmt, ...) lpDebugConOut.PrintF(fmt"\n", __VA_ARGS__)
#define TRACE_ST(...) lpDebugConOut.StreamPrintln(__VA_ARGS__)

class _DebugConOut
{
public:
	static _DebugConOut& GetInstance()
	{
		static _DebugConOut sInstance;
		return sInstance;
		//return *sInstance_;
	}

	template<class... Args>
	void PrintF(const char* format, Args... args);

	template<typename ... Args>
	void StreamPrintln(const Args&... args);
private:
	struct _DebugConOutDeleter
	{
		void operator()(_DebugConOut * _debugConOut) const
		{
			delete _debugConOut;
		}
	};
	_DebugConOut();
	~_DebugConOut();
	
	FILE* debugFp_ = nullptr;
	//inline static std::unique_ptr<_DebugConOut, _DebugConOutDeleter> sInstance_{};
	// = std::unique_ptr<_DebugConOut, _DebugConOutDeleter>(new _DebugConOut());
};

template <class ... Args>
void _DebugConOut::PrintF(const char* format, Args... args)
{
	printf(format, args...);
}

template <typename  ... Args>
void _DebugConOut::StreamPrintln(const Args&... args)
{
	using swallow = std::initializer_list<int>;
	(void)swallow
	{
		(void(std::cout << args), 0)...
	};
	std::cout << std::endl;
}

#else	//_DEBUG
#define TRACE(fmt, ...)
#define TRACE_ST(...)
#endif	//_DEBUG
