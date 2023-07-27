#pragma once
#include "BaseGraphic.h"
#include "Vertices.h"
#include "Texture.h"
#include "ScreenDesc.h"
#include "PipelineSetting.h"
#include "Vector3.h"
#include "Vector2.h"
#include <list>
#include <vector>

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
		/// 静的初期化
		/// </summary>
		/// <param name="pDevice"> : デバイスポインタ</param>
		/// <param name="pCmdList"> : コマンドリストポインタ</param>
		static void StaticInitialize(
			ID3D12Device* pDevice,
			ID3D12GraphicsCommandList* pCmdList);

		/// <summary>
		/// 生成
		/// </summary>
		/// <param name="rtvTags"> : レンダーターゲットタグ配列</param>
		/// <returns>ポストエフェクトポインタ</returns>
		static PostEffect* Create(const std::vector<std::string>& rtvTags);

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
		void SetDrawCommand(std::unordered_map<std::string, uint32_t>& rpIndices) override;

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

		// 描画段階
		enum class Phase
		{
			None, // 何もしていない

			Rendering, // 書き込み中
			
			End, // 終了
		};
	
	private:

		// 頂点データ
		YDX::Vertices<VData> vt_;

		// テクスチャ
		std::unordered_map<std::string, Texture*> pTexs_{};

		// 段階
		Phase phase_ = Phase::None;

		// スクリーン設定
		YDX::ScreenDesc screenDesc_;


		// RTV用ヒープ
		Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> rtvHeap_ = nullptr;

		// DSV用ヒープ
		Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> dsvHeap_ = nullptr;

		// 深度バッファ
		YDX::GPUResource depthBuff_;

	private:

		// 静的ポストエフェクト格納用vector配列
		static std::vector<std::unique_ptr<PostEffect>> sPostEffects_;

		// 静的デバイスポインタ
		static ID3D12Device* spDevice_;

		// 静的コマンドリストポインタ
		static ID3D12GraphicsCommandList* spCmdList_;

	private:

		void CreateRTV();

		void CreateDepthBuff(const YMath::Vector2 & size);

		void CreateDSV();

	};
}
