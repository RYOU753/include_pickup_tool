#include "Timer.h"
#include <algorithm>

Timer::Timer(const float& limit, const float& currentTime)
	: limitTime_(limit), currentTime_(currentTime), resetCounter_(0)
{
}

Timer::~Timer() = default;

void Timer::Update(const double& delta)
{
    if (!IsTimeOver())
    {
        currentTime_ += static_cast<float>(delta);
    }
    else
    {
        currentTime_ = limitTime_;
    }
}

bool Timer::IsTimeOver() const
{
    return currentTime_ > limitTime_;
}

float Timer::NormalizedTime() const
{
    return  std::clamp(currentTime_ / limitTime_,0.0f,1.0f);
}

float Timer::GetDurationTime() const
{
    return currentTime_;
}

float Timer::InverseNormalizedTime() const
{
    return std::max(0.0f,1.0f - NormalizedTime());
}

float Timer::InverseTime() const
{
    return std::max(0.0f,limitTime_ - currentTime_);
}

void Timer::ResetTime()
{
    currentTime_ = 0.0f;
    resetCounter_++;
}

void Timer::SetTime(float time)
{
    currentTime_ = time;
}

void Timer::SetLimitTime(float limit)
{
    limitTime_ = limit;
}
const float& Timer::GetLimitTime(void) const
{
    return limitTime_;
}
const int& Timer::GetResetCount(void) const
{
    return resetCounter_;
}

void Timer::InitResetCount()
{
    resetCounter_ = 0;
}
