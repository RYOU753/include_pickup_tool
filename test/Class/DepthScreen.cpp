#include "DepthScreen.h"

#include <Dxlib.h>

DepthScreen::DepthScreen(int width, int height)
{
	// 深度を描画するテクスチャの作成( １チャンネル浮動小数点１６ビットテクスチャ )
	SetDrawValidFloatTypeGraphCreateFlag(TRUE);
	SetCreateDrawValidGraphChannelNum(1);
	SetCreateGraphChannelBitDepth(16);
	handle_ = MakeScreen(width, height, FALSE);
	width_ = width;
	height_ = height;
	SetDrawValidFloatTypeGraphCreateFlag(FALSE);
	SetCreateDrawValidGraphChannelNum(4);
	SetCreateGraphChannelBitDepth(32);
}

void DepthScreen::Begin()
{
	SetDrawScreen(handle_);
	//SetBackgroundColor(255, 255, 255,255);
	if (!isClear_)
	{
		ClearDrawScreen();
		isClear_ = true;
	}
	//SetBackgroundColor(0,0,0);
}