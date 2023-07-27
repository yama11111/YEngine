#pragma once
#include "BaseGraphic.h"
#include "Vertices.h"
#include "Texture.h"
#include "PipelineSetting.h"
#include "Vector3.h"
#include "Vector2.h"

namespace YGame
{
	// スプライト2D
	class Sprite2D :
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
		/// <param name="pTexs"> : テクスチャポインタ配列</param>
		/// <param name="anchor"> : アンカーポイント (初期値は中心)</param>
		/// <param name="isFlipX"> : X反転するか</param>
		/// <param name="isFlipY"> : Y反転するか</param>
		/// <returns>スプライトポインタ</returns>
		static Sprite2D* Create(
			const std::unordered_map<std::string, Texture*>& pTexs,
			YMath::Vector2 anchor = { 0.5f, 0.5f }, 
			const bool isFlipX = false,
			const bool isFlipY = false);

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

	public:

		Sprite2D() = default;

		~Sprite2D() = default;

	private:

		// 頂点データ
		YDX::Vertices<VData> vt_;


		// サイズ
		YMath::Vector2 size_;

		// アンカーポイント
		YMath::Vector2 anchor_;

		// 左右反転
		bool isFlipX_ = false;

		// 上下反転
		bool isFlipY_ = false;


		// テクスチャ
		std::unordered_map<std::string, Texture*> pTexs_{};

		// 表示するか
		bool isVisible_ = true;

	private:

		// 静的スプライト2D格納用vector配列
		static std::vector<std::unique_ptr<Sprite2D>> sSprites_;
	};
}
