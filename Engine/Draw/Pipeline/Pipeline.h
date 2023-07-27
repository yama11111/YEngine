#pragma once
#include "ConstBufferPtrSet.h"
#include "BaseGraphic.h"
#include "ShaderSet.h"
#include "PipelineSetting.h"
#include <queue>

namespace YGame
{
	class Pipeline final
	{

	public:

		// ブレンド情報
		enum class BlendState
		{
			// ブレンドしない
			None,

			// アルファブレンド
			Alpha,

			// 加算合成
			Add, 
			
			// 減算合成
			Sub,
			
			// 色反転
			Inverse,
		};
	
	public:

		// 描画用構造体
		struct DrawSet
		{
			// 優先度
			uint16_t priority = 0;

			// 定数バッファポインタセットポインタ
			ConstBufferPtrSet* pCBPtrSet = nullptr;
				
			// グラフィックポインタ
			BaseGraphic* pGraphic = nullptr;
		};

	public:
		
		/// <summary>
		/// 生成
		/// </summary>
		/// <param name="shaderSet"> : シェーダー</param>
		/// <param name="constBufferKeys"> : 定数バッファキー配列</param>
		/// <param name="graphicRPKeys"> : グラフィック用ルートパラメータキー配列</param>
		/// <param name="textureNum"> : テクスチャ枚数</param>
		/// <param name="pipelineSetting"> : パイプライン設定</param>
		/// <param name="blendState"> : ブレンド設定</param>
		/// <param name="renderTargetNum"> : レンダーターゲット枚数</param>
		/// <returns></returns>
		static Pipeline* Create(
			ShaderSet& shaderSet,
			const std::vector<std::string>& constBufferKeys, 
			const std::vector<std::string>& graphicRPKeys,
			const uint32_t textureNum,
			const PipelineSetting& pipelineSetting,
			const BlendState& blendState, 
			const UINT renderTargetNum);

		/// <summary>
		/// 描画情報をキューに積む
		/// </summary>
		/// <param name="drawSet"> : 描画セット</param>
		/// <param name="-----------------------------------------"></param>
		/// <param name="(uint16_t) priority"> : 優先度</param>
		/// <param name="(ConstBufferPtrSet*) pCBPtrSet"> : 定数バッファポインタセットポインタ</param>
		/// <param name="(BaseGraphic*) pGraphic"> : グラフィックポインタ</param>
		void EnqueueDrawSet(const DrawSet& drawSet);

		/// <summary>
		/// 描画
		/// </summary>
		void Draw();

		/// <summary>
		/// 静的初期化
		/// </summary>
		/// <param name="pDevice"> : デバイスポインタ</param>
		/// <param name="pCommandList"> : コマンドリストポインタ</param>
		static void StaticInitialize(ID3D12Device* pDevice, ID3D12GraphicsCommandList* pCommandList);

	private:

		// ルートシグネチャ
		Microsoft::WRL::ComPtr<ID3D12RootSignature> rootSignature_ = nullptr;

		// パイプランステート
		Microsoft::WRL::ComPtr<ID3D12PipelineState> pipelineState_ = nullptr;

		// プリミティブ形状
		D3D_PRIMITIVE_TOPOLOGY primitive_ = D3D_PRIMITIVE_TOPOLOGY_UNDEFINED;

		// 定数バッファルートパラメータ番号格納配列
		std::unordered_map<std::string, uint32_t> cbRPIndices_;
		
		// グラフィック用ルートパラメータ番号格納配列
		std::unordered_map<std::string, uint32_t> graphicRPIndices_;

		// 描画用構造体キュー
		std::priority_queue<DrawSet> drawSets_;

		// 静的デバイスポインタ
		static ID3D12Device* spDevice_;

		// 静的コマンドリストポインタ
		static ID3D12GraphicsCommandList* spCmdList_;

	private:

		/// <summary>
		/// ルートシグネチャ生成
		/// </summary>
		/// <param name="rootParams"> : ルートパラメータ</param>
		/// <param name="samplerDescs"> : テクスチャサンプラー</param>
		void CreateRootSignature(
			const std::vector<D3D12_ROOT_PARAMETER>& rootParams,
			const std::vector<D3D12_STATIC_SAMPLER_DESC>& samplerDescs);

		/// <summary>
		/// パイプラインステート生成
		/// </summary>
		/// <param name="pipelineDesc"> : パイプライン設定</param>
		void CreatePipelineState(D3D12_GRAPHICS_PIPELINE_STATE_DESC& pipelineDesc);

		/// <summary>
		/// プリミティブ形状の設定
		/// </summary>
		/// <param name="primitive"> : プリミティブ形状</param>
		void SetPrimitiveTopology(const D3D_PRIMITIVE_TOPOLOGY& primitive);

	};

	// 優先順位付け用オーバーロード
	bool operator<(const Pipeline::DrawSet& drawSet1, const Pipeline::DrawSet& drawSet2);
	bool operator>(const Pipeline::DrawSet& drawSet1, const Pipeline::DrawSet& drawSet2);
}
