/**
 * @file ScreenDesc.h
 * @brief スクリーン設定クラス
 * @author Yamanaka Rui
 * @date 2024/01/18
 */

#pragma once
#include <d3d12.h>
#include "Vector2.h"
#include <vector>

namespace YDX
{
	class ScreenDesc
	{
	private:
		
		// ビューポート設定コマンド
		std::vector<D3D12_VIEWPORT> viewport_;
		
		// シザー矩形
		std::vector<D3D12_RECT> scissorRect_;
	
	public:
		
		// 初期化 (引数 : 左上, 右下)
		void Initialize(const YMath::Vector2& topLeft, const YMath::Vector2& bottomRight, const size_t descNum = 1);
		
		// 描画前コマンド
		void SetDrawCommand();
	
	private:
		
		// 静的コマンドリストポインタ
		static ID3D12GraphicsCommandList* spCmdList_;
	
	public:
		
		// 静的メンバ初期化
		static void StaticInitialize(ID3D12GraphicsCommandList* pCommandList);
	};
}
