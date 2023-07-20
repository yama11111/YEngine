#pragma once
#include <d3d12.h>
#include <vector>

namespace YGame
{
	struct PipelineSetting
	{
		// 頂点レイアウト
		std::vector<D3D12_INPUT_ELEMENT_DESC> inputLayout;
		
		// テクスチャサンプラー
		std::vector<D3D12_STATIC_SAMPLER_DESC> samplerDescs;
		
		// ポリゴンの塗り方
		D3D12_FILL_MODE fillMode = D3D12_FILL_MODE_SOLID;
		
		// カリング設定
		D3D12_CULL_MODE cullMode;
		
		// 深度テストを行うか
		bool depthEnable;

		// 形状設定
		D3D12_PRIMITIVE_TOPOLOGY_TYPE primitiveType;

		// 形状
		D3D_PRIMITIVE_TOPOLOGY primitive;
	};
}

