#pragma once
#include <d3d12.h>
#include "Vector2.h"

#pragma comment(lib, "d3d12.lib")

namespace YDX
{
	class ScreenDesc
	{
	private:
		// ビューポート設定コマンド
		D3D12_VIEWPORT viewport_{};
		// シザー矩形
		D3D12_RECT scissorRect_{};
	public:
		// 初期化 (引数 : 左上, 右下)
		void Initialize(const YMath::Vector2& topLeft, const YMath::Vector2& bottomRight);
		// 描画前コマンド
		void SetDrawCommand();
	private:
		// 静的コマンドリストポインタ
		static ID3D12GraphicsCommandList* pCommandList_;
	public:
		// 静的メンバ初期化
		static void StaticInitialize(ID3D12GraphicsCommandList* pCommandList);
	};
}
