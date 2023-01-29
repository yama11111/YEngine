#pragma once
#include "Sprite2DCommon.h"
#include "Vertices.h"
#include "Object.h"
#include "Color.h"

namespace YGame
{
	// スプライト用オブジェクト
	typedef Object<Sprite2DCommon::CBData> ObjectSprite2D;

	// スプライトクラス
	class Sprite2D : private Sprite2DCommon
	{
	private:
		// 頂点データ
		YDX::Vertices<VData> vt_;
		// 色
		Color defColor_{};

		// サイズ
		YMath::Vec2 size_;
		// アンカーポイント
		YMath::Vec2 anchor_;
		// 左右反転
		bool isFlipX_ = false;
		// 上下反転
		bool isFlipY_ = false;

		// テクスチャ
		UINT tex_ = UINT32_MAX;
		// テクスチャ左上
		YMath::Vec2 texLeftTop_;
		// テクスチャサイズ
		YMath::Vec2 texSize_;

		// 非表示
		bool isInvisible_ = false;
	public:
		// 設定用ステータス
		struct Status
		{
			YMath::Vec2 size_; // サイズ
			YMath::Vec2 anchor_ = { 0.0f, 0.0f }; // アンカーポイント
			bool isFlipX_ = false; // 左右反転
			bool isFlipY_ = false; // 上下反転
		};
		// テクスチャ設定用ステータス
		struct TexStatus
		{
			UINT index_ = UINT32_MAX; // テクスチャインデックス
			YMath::Vec2 leftTop_ = { 0.0f,0.0f }; // テクスチャ左上
			YMath::Vec2 size_ = { 0.0f,0.0f }; // テクスチャサイズ
		};
	public:
		// 生成
		static Sprite2D* Create(const Status& state, const TexStatus& texState, const bool div = false);
	public:
		// 描画 (テクスチャ + 色 有)
		void Draw(ObjectSprite2D& obj, Color& color, const UINT tex);
		// 描画 (テクスチャ 有)
		void Draw(ObjectSprite2D& obj, const UINT tex);
		// 描画 (色 有)
		void Draw(ObjectSprite2D& obj, Color& color);
		// 描画 (デフォルト)
		void Draw(ObjectSprite2D& obj);
	public:
		// サイズ設定
		void SetSize(const YMath::Vec2& size);
		// アンカーポイント設定
		void SetAnchorPoint(const YMath::Vec2& anchor);
		// フリップ設定
		void SetFrip(const bool isFlipX, const bool isFlipY);
		// テクスチャ左上設定
		void SetTextureLeftTop(const YMath::Vec2& leftTop, const bool adjust = true);
		// テクスチャサイズ設定
		void SetTextureSize(const YMath::Vec2& texSize);
		// テクスチャ矩形設定
		void SetTextureRectangle(const YMath::Vec2& leftTop, const YMath::Vec2& texSize);
		// 全設定
		void SetAllStatus(const Status& state, const TexStatus& texState, const bool div = false);
		// 非表示設定
		void SetInvisible(const bool isInvisible) { isInvisible_ = isInvisible; }
	public:
		// サイズ取得
		YMath::Vec2 Size() const { return size_; }
		// アンカーポイント取得
		YMath::Vec2 AnchorPoint() const { return anchor_; }
	private:
		// コンストラクタ
		Sprite2D() = default;
	};
}
