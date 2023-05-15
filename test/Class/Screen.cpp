#include "Screen.h"

#include <Dxlib.h>

Screen::Screen(int width, int height,bool useAlpha)
	:width_(width),height_(height),isClear_(false)
{
	handle_ = MakeScreen(width_, height_, useAlpha);
}

Screen::Screen(Kirara::Math::Vector2Int size, bool useAlpha)
	:Screen(size.x,size.y,useAlpha)
{
}

Screen::~Screen()
{
	DeleteGraph(handle_);
}

void Screen::Draw(const int& x, const int& y, const bool& isTrans) const
{
	DrawGraph(x, y, handle_, isTrans);
}

void Screen::Draw(const int& x, const int& y, const float& extend, const bool& isTrans) const
{
	DrawExtendGraph(x, y, static_cast<int>(x + width_ * extend), static_cast<int>(y + height_ * extend), handle_, isTrans);
}

void Screen::NoClearBegin()
{
	SetDrawScreen(handle_);
}

void Screen::NoClearBegin(const int& screenHandle)
{
	justBeforeScr_ = screenHandle;
	NoClearBegin();
}

void Screen::NoClearBegin(const std::unique_ptr<Screen>& screenHandle)
{
	NoClearBegin(screenHandle->GetHandle());
}

void Screen::NoClearBegin(const std::shared_ptr<Screen>& screenHandle)
{
	NoClearBegin(screenHandle->GetHandle());
}

void Screen::NoClearBegin(const std::weak_ptr<Screen>& screenHandle)
{
	if(!screenHandle.expired())
	{
		NoClearBegin(screenHandle.lock()->GetHandle());
	}
}

void Screen::Begin()
{
	SetDrawScreen(handle_);
	if(!isClear_)
	{
		ClearDrawScreen();
		isClear_ = true;
	}
	
}

void Screen::Begin(const int& screenHandle)
{
	justBeforeScr_ = screenHandle;
	Begin();
}

void Screen::Begin(const Screen& screenHandle)
{
	Begin(screenHandle.GetHandle());
}

void Screen::Begin(const std::unique_ptr<Screen>& screenHandle)
{
	Begin(screenHandle->GetHandle());
}

void Screen::Begin(const std::shared_ptr<Screen>& screenHandle)
{
	Begin(screenHandle->GetHandle());
}

void Screen::Begin(const std::weak_ptr<Screen>& screenHandle)
{
	if (!screenHandle.expired())
	{
		Begin(screenHandle.lock()->GetHandle());
	}
}

void Screen::End()
{
	SetDrawScreen(justBeforeScr_.value_or(DX_SCREEN_BACK));
	isClear_ = false;
}

void Screen::Clear()
{
	Begin();
	End();
}

const int& Screen::GetHandle()const
{
	return handle_;
}

const int& Screen::GetWidth()const
{
	return width_;
}

const int& Screen::GetHeight()const
{
	return height_;
}

Screen::Screen():isClear_(false)
{
}
