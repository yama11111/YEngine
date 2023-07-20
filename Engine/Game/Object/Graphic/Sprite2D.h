#pragma once
#include "BaseGraphic.h"
#include "Vertices.h"
#include "Texture.h"
#include "PipelineSetting.h"
#include "Vector3.h"
#include "Vector2.h"
#include <list>
#include <array>

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

		// 設定用ステータス
		struct Status
		{
			bool isDiv_ = true; // 画像サイズに合わせるか
			YMath::Vector2 size_; // サイズ
			YMath::Vector2 anchor_ = { 0.5f, 0.5f }; // アンカーポイント
			bool isFlipX_ = false; // 左右反転
			bool isFlipY_ = false; // 上下反転
		};

		// テクスチャ設定用ステータス
		struct TexStatus
		{
			Texture* pTex_; // テクスチャポインタ
			bool isDiv_ = true; // 画像サイズに合わせるか
			YMath::Vector2 leftTop_ = { 0.0f,0.0f }; // テクスチャ左上
			YMath::Vector2 size_ = { 0.0f,0.0f }; // テクスチャサイズ
		};

	public:

		/// <summary>
		/// 生成
		/// </summary>
		/// <param name="status"> : スプライト設定</param>
		/// <param name="(bool) isDiv_"> : 画像サイズに合わせるか</param>
		/// <param name="(Vector2) status.size_"> : 大きさ</param>
		/// <param name="(Vector2) status.anchor_"> : アンカーポイント (初期値は中心)</param>
		/// <param name="(bool) status.isFlipX_"> : X反転するか</param>
		/// <param name="(bool) status.isFlipY_"> : Y反転するか</param>
		/// <param name="--------------------------------"></param>
		/// <param name="texStatus"> : テクスチャ設定</param>
		/// <param name="(Texture*) texStatus.pTex_"> : テクスチャポインタ</param>
		/// <param name="(bool) isDiv_"> : 画像サイズに合わせるか</param>
		/// <param name="(Vector2) texStatus.leftTop_"> : テクスチャ左上</param>
		/// <param name="(Vector2) texStatus.size_"> : テクスチャサイズ</param>
		/// <param name="--------------------------------"></param>
		/// <returns>スプライトポインタ</returns>
		static Sprite2D* Create(const Status& status, const TexStatus& texStatus);

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
		Texture* pTex_ = nullptr;

		// テクスチャ左上
		YMath::Vector2 texLeftTop_;

		// テクスチャサイズ
		YMath::Vector2 texSize_;

		// 表示するか
		bool isVisible_ = true;

	private:

		// 静的スプライト2D格納用vector配列
		static std::vector<std::unique_ptr<Sprite2D>> sSprites_;
	};
}
