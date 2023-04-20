#pragma once
#include <d3d12.h>
#include <wrl.h>
#include <vector>

#pragma comment(lib, "d3d12.lib")

namespace YDX
{
	class PipelineSet
	{

	private:

		// ルートシグネチャ
		Microsoft::WRL::ComPtr<ID3D12RootSignature> rootSignature_ = nullptr;

		// パイプランステート
		Microsoft::WRL::ComPtr<ID3D12PipelineState> pipelineState_ = nullptr;

		// プリミティブ形状
		D3D_PRIMITIVE_TOPOLOGY primitive_ = D3D_PRIMITIVE_TOPOLOGY_UNDEFINED;

	public:

		// 初期化用構造体
		struct InitStatus
		{

			// 頂点レイアウト
			std::vector<D3D12_INPUT_ELEMENT_DESC> inputLayout_;

			// テクスチャサンプラー
			std::vector<D3D12_STATIC_SAMPLER_DESC> samplerDescs_;

			// ルートパラメータ
			std::vector<D3D12_ROOT_PARAMETER> rootParams_;

			// デスクリプタレンジ
			D3D12_DESCRIPTOR_RANGE descriptorRange_{};

			// パイプライン設定
			D3D12_GRAPHICS_PIPELINE_STATE_DESC pipelineDesc_{};

			// プリミティブ形状
			D3D_PRIMITIVE_TOPOLOGY primitive_;

		};

	public:

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="status"> : 初期化用ステータス</param>
		/// <param name="-----------------------------------"></param>
		/// <param name="inputLayout"> : 頂点レイアウト</param>
		/// <param name="samplerDescs"> : テクスチャサンプラー</param>
		/// <param name="rootParams"> : ルートパラメータ</param>
		/// <param name="descriptorRange"> : デスクリプタレンジ</param>
		/// <param name="pipelineDesc"> : パイプライン設定</param>
		/// <param name="primitive"> : プリミティブ形状</param>
		void Initialize(InitStatus& status);

		/// <summary>
		/// 描画前コマンド
		/// </summary>
		void SetDrawCommand();

	private:

		/// <summary>
		/// ルートシグネチャ生成
		/// </summary>
		/// <param name="rootParams"> : ルートパラメータ</param>
		/// <param name="samplerDescs"> : テクスチャサンプラー</param>
		/// <param name="errorBlob"> : エラー用</param>
		void CreateRootSignature(
			const std::vector<D3D12_ROOT_PARAMETER>& rootParams,
			const std::vector<D3D12_STATIC_SAMPLER_DESC>& samplerDescs);

		/// <summary>
		/// パイプラインステート生成
		/// </summary>
		/// <param name="pipelineDesc"> : パイプライン設定</param>
		/// <param name="inputLayout"> : 頂点レイアウト</param>
		/// <param name="descriptorRange"> : デスクリプタレンジ</param>
		void CreatePipelineState(
			D3D12_GRAPHICS_PIPELINE_STATE_DESC& pipelineDesc,
			const std::vector<D3D12_INPUT_ELEMENT_DESC>& inputLayout);

		/// <summary>
		/// プリミティブ形状の設定
		/// </summary>
		/// <param name="primitive"> : プリミティブ形状</param>
		void SetPrimitiveTopology(const D3D_PRIMITIVE_TOPOLOGY& primitive);

	private:

		// 静的デバイスポインタ
		static ID3D12Device* pDevice_;

		// 静的コマンドリストポインタ
		static ID3D12GraphicsCommandList* pCmdList_;

	public:
		
		/// <summary>
		/// 静的初期化
		/// </summary>
		/// <param name="pDevice"> : デバイスポインタ</param>
		/// <param name="pCommandList"> : コマンドリストポインタ</param>
		static void StaticInitialize(ID3D12Device* pDevice, ID3D12GraphicsCommandList* pCommandList);

	};
}
