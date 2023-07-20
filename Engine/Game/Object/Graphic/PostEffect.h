#pragma once
#include "BaseGraphic.h"
#include "Vertices.h"
#include "Texture.h"
#include "ScreenDesc.h"
#include "PipelineSetting.h"
#include "Vector3.h"
#include "Vector2.h"
#include <list>
#include <array>

namespace YGame
{
	// ポストエフェクト
	class PostEffect :
		public BaseGraphic
	{

	public:

		// 頂点データ構造体
		struct VData
		{
			YMath::Vector3 pos_; // xyz座標
			YMath::Vector2 uv_;  // uv座標
		};

	public:

		/// <summary>
		/// 生成
		/// </summary>
		/// <returns>ポストエフェクトポインタ</returns>
		static PostEffect* Create();

		/// <summary>
		/// 全削除
		/// </summary>
		static void AllClear();
		
		/// <summary>
		/// モデル用のパイプライン設定取得
		/// </summary>
		/// <returns>パイプライン設定</returns>
		static PipelineSetting GetPipelineSetting();

	public:

		/// <summary>
		/// 描画
		/// </summary>
		/// <param name="rpIndices"> : ルートパラメータ情報 + 番号</param>
		void SetDrawCommand(std::unordered_map<std::string, uint32_t>& rpIndices) const override;

		/// <summary>
		/// 書き込み開始
		/// </summary>
		void StartRender();

		/// <summary>
		/// 書き込み終了
		/// </summary>
		void EndRender();

	public:

		PostEffect() = default;

		~PostEffect() = default;

	private:

		void CreateRTV();

		void CreateDepthBuff(const YMath::Vector2 & size);

		void CreateDSV();

	private:

		// 頂点データ
		YDX::Vertices<VData> vt_;

		// テクスチャの数
		static const size_t kTextureNum_ = 2;

		// テクスチャ
		std::array<Texture*, kTextureNum_> pTexs_;


		// RTV用ヒープ
		Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> rtvHeap_ = nullptr;

		// DSV用ヒープ
		Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> dsvHeap_ = nullptr;

		// 深度バッファ
		YDX::GPUResource depthBuff_;

	private:

		// 静的ポストエフェクト格納用vector配列
		static std::vector<std::unique_ptr<PostEffect>> sPostEffects_;

	private:

		// 静的デバイスポインタ
		static ID3D12Device* spDevice_;

		// 静的コマンドリストポインタ
		static ID3D12GraphicsCommandList* spCmdList_;

		// 静的スクリーン設定ポインタ
		static YDX::ScreenDesc sScreenDesc_;

	public:

		/// <summary>
		/// 静的初期化
		/// </summary>
		/// <param name="pDevice"> : デバイスポインタ</param>
		/// <param name="pCmdList"> : コマンドリストポインタ</param>
		static void StaticInitialize(
			ID3D12Device * pDevice,
			ID3D12GraphicsCommandList * pCmdList);

	};
}
