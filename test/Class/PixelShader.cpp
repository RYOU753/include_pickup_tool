#include "PixelShader.h"
#include <DxLib.h>
#include <cassert>
#include <ranges>

#include "ConstantBuffer.h"
#include "Screen.h"

PixelShader::PixelShader(std::string_view path)
{
	handle_ = LoadPixelShader(path.data());
	assert(handle_ != -1);
}

PixelShader::~PixelShader()
{
	DeleteShader(handle_);
}

void PixelShader::Begin()
{
	SetUsePixelShader(handle_);
	ActiveBuffer();
}

void PixelShader::End()
{
	DeactivateBuffer();
	SetUsePixelShader(-1);
}

void PixelShader::SetConstantBuffer(const int& slot,const ConstBufBaseSPtr& constantBuffer)
{
	constantBufferList_.emplace(slot, constantBuffer);
}

void PixelShader::SetTextureBuffer(const int& slot, const int& graphHandle)
{
	textureBufferList_.emplace(slot, graphHandle);
}

void PixelShader::SetRenderTarget(const int& slot, const std::shared_ptr<Screen>& target)
{
	renderTargetList_.emplace(slot, target);
}

void PixelShader::ActiveBuffer()
{
	//コンスタントバッファセット
	for (const auto& [slot, buffer] : constantBufferList_)
	{
		SetShaderConstantBuffer(buffer->GetHandle(), DX_SHADERTYPE_PIXEL, slot);
	}
	//テクスチャバッファセット
	for(const auto& [slot,buffer]:textureBufferList_)
	{
		SetUseTextureToShader(slot, buffer);
	}
	//レンダーターゲットの設定
	for(const auto& [slot,target]:renderTargetList_)
	{
		SetRenderTargetToShader(slot, target->GetHandle());
	}
}

void PixelShader::DeactivateBuffer()
{
	for (const auto& slot : constantBufferList_ | std::views::keys)
	{
		SetShaderConstantBuffer(-1, DX_SHADERTYPE_PIXEL, slot);
	}

	for (const auto& slot : textureBufferList_ | std::views::keys)
	{
		SetUseTextureToShader(slot, -1);
	}

	for (const auto& slot : renderTargetList_ | std::views::keys)
	{
		SetRenderTargetToShader(slot, -1);
	}
}
