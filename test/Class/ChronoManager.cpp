#include "ChronoManager.h"

#include <DxLib.h>

#include "_debug/_DebugConOut.h"
#include "_debug/_DebugDispOut.h"

ChronoManager::ChronoManager() 
{
	nowTime = std::chrono::system_clock::now();
	delta_ = 0.0;
	sec_ = 0.0;
}

void ChronoManager::Update(void)
{
	oldTime = nowTime;
	nowTime = std::chrono::system_clock::now();
	const auto flameTime = nowTime - oldTime;
	const auto nanoSec = std::chrono::duration_cast<std::chrono::nanoseconds>(flameTime).count();
	delta_ = nanoSec / NANO;

	delta_ = delta_ < LIMIT ? delta_ : LIMIT;
}

void ChronoManager::DebugDrawFps(const int& x, const int& y, const int& color)
{
	_dbgDrawFormatString(x - GetDrawFormatStringWidth("FPS:%d", GetFPS()), y, color, "FPS:%d", GetFPS());
}

const double& ChronoManager::GetDelta() const
{
	return delta_;
}

void ChronoManager::StopWatchStart(void)
{
	startTime = std::chrono::system_clock::now();
}

void ChronoManager::StopWatchEnd(void)
{
	endTime = std::chrono::system_clock::now();
	const auto dur = endTime - startTime;
	const auto time = static_cast<double>(std::chrono::duration_cast<std::chrono::nanoseconds>(dur).count()) / MICRO;
	TRACE("経過時間::%lf秒\n", time);
}

int ChronoManager::GetFPS(void)
{
	sec_ += GetDelta();
	if (sec_ >= 1.0)
	{
		fpsView_ = fpsCount_;
		fpsCount_ = 0;
		sec_ = 0.0;
	}
	else
	{
		fpsCount_++;
	}
	return fpsView_;
}
