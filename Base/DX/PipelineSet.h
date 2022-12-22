#pragma once
#include <d3d12.h>
#include <wrl.h>
#include <vector>

#pragma comment(lib, "d3d12.lib")

namespace YDX
{
	class PipelineSet
	{
	public:
		// 設定構造体インターフェース
		struct IStatus
		{
		public:
			// 頂点レイアウト
			std::vector<D3D12_INPUT_ELEMENT_DESC> inputLayout_;
			// テクスチャサンプラー
			std::vector<D3D12_STATIC_SAMPLER_DESC> sampleDesc_;
			// パイプライン設定
			D3D12_GRAPHICS_PIPELINE_STATE_DESC pplnDesc_{};
			// プリミティブ形状
			D3D_PRIMITIVE_TOPOLOGY primitive_ = D3D_PRIMITIVE_TOPOLOGY_UNDEFINED;
		public:
			virtual void Initialize(ID3DBlob* errorBlob_) = 0;
		};
	private:
		// ルートシグネチャ
		Microsoft::WRL::ComPtr<ID3D12RootSignature> rootSignature_ = nullptr;
		// パイプランステート
		Microsoft::WRL::ComPtr<ID3D12PipelineState> pplnState_ = nullptr;
		// プリミティブ形状
		D3D_PRIMITIVE_TOPOLOGY primitive_ = D3D_PRIMITIVE_TOPOLOGY_UNDEFINED;
	public:
		// 初期化
		void Initialize(IStatus* state, std::vector<D3D12_ROOT_PARAMETER>* rootParams);
		// 描画前コマンド
		void SetDrawCommand();
	private:
		// 静的デバイスポインタ
		static ID3D12Device* pDevice_;
		// 静的コマンドリストポインタ
		static ID3D12GraphicsCommandList* pCmdList_;
	public:
		// 静的初期化
		static void StaticInitialize(ID3D12Device* pDevice, ID3D12GraphicsCommandList* pCommandList);
	};
}
