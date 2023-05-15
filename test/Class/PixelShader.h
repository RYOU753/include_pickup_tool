#pragma once
#include <memory>
#include <string_view>
#include <unordered_map>
#include "../Using/ShaderUsing.h"

class Screen;

class PixelShader
{
public:
	PixelShader(std::string_view path);
	~PixelShader();

	/// @brief シェーダ適用始め
	void Begin();

	/// @brief シェーダ適用終了
	void End();

	/// @brief ピクセルシェーダ内で使うコンスタントバッファをセットする
	/// @param slot セットするスロット
	/// @param constantBuffer セットするコンスタントバッファ
	void SetConstantBuffer(const int& slot,const ConstBufBaseSPtr& constantBuffer);

	/// @brief ピクセルシェーダ内で使うテクスチャバッファをセットする
	/// @param slot セットするスロット
	/// @param graphHandle セットするテクスチャ
	void SetTextureBuffer(const int& slot, const int& graphHandle);

	void SetRenderTarget(const int& slot, const std::shared_ptr<Screen>& target);
private:
	/// @brief バッファをセットする
	void ActiveBuffer();

	/// @brief セットしたコンスタントバッファを解除する
	void DeactivateBuffer();
	
	int handle_;
	std::unordered_map<int, ConstBufBaseSPtr> constantBufferList_;
	std::unordered_map<int, int> textureBufferList_;
	std::unordered_map<int, std::shared_ptr<Screen>> renderTargetList_;
};
