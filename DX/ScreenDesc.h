#pragma once
#include <d3d12.h>
#include "Vec2.h"

#pragma comment(lib, "d3d12.lib")

namespace DX
{
	class ScreenDesc
	{
	private:
		// ビューポート設定コマンド
		D3D12_VIEWPORT viewport_{};
		// シザー矩形
		D3D12_RECT scissorRect_{};
	public:
		// 
		void Initialize(const Math::Vec2& topLeft, const Math::Vec2& bottomRight);
		// 描画前コマンド
		void SetCommand();
	private:
		// コマンドリストポインタ
		static ID3D12GraphicsCommandList* pCmdList_;
	public:
		// スタティックイニシャライズ
		static void StaticInitialize(ID3D12GraphicsCommandList* pCommandList);
	};
}
