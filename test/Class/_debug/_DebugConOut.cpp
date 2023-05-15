#ifdef _DEBUG

#include <Windows.h>
#include "_DebugConOut.h"

//std::unique_ptr<_DebugConOut, _DebugConOut::_DebugConOutDeleter> _DebugConOut::sInstance(new _DebugConOut);
//volatile static inline std::unique_ptr<_DebugConOut> sInstance(new _DebugConOut);

_DebugConOut::_DebugConOut()
{
	AllocConsole();
	freopen_s(&debugFp_, "CONOUT$", "w", stdout);
	freopen_s(&debugFp_, "CONIN$",  "r", stdin);
}


_DebugConOut::~_DebugConOut()
{
	FreeConsole();
}
#endif	//_DEBUG