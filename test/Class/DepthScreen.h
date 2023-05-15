#pragma once
#include "Screen.h"

class DepthScreen
	:public Screen
{
public:
	DepthScreen(int width, int height);
	~DepthScreen() override =default;
	void Begin()override;
};
