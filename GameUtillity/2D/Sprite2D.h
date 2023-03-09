#pragma once
#include "Sprite2DCommon.h"
#include "Vertices.h"
#include "BaseObject.h"
#include "Color.h"

namespace YGame
{
	// スプライト2D用オブジェクト
	class ObjectSprite2D : public BaseObject
	{
	public:
		// 定数バッファ
		YDX::ConstBuffer<Sprite2DCommon::CBData> cBuff_;
	public:
		// 生成
		static ObjectSprite2D* Create(const Status& state);
	private:
		ObjectSprite2D() = default;
	public:
		~ObjectSprite2D() override = default;
	};

	// スプライト2Dクラス
	class Sprite2D : private Sprite2DCommon
	{
	private:
		// 頂点データ
		YDX::Vertices<VData> vt_;
		// 色
		std::unique_ptr<Color> defColor_;

		// サイズ
		YMath::Vector2 size_;
		// アンカーポイント
		YMath::Vector2 anchor_;
		// 左右反転
		bool isFlipX_ = false;
		// 上下反転
		bool isFlipY_ = false;

		// テクスチャ
		UINT tex_ = UINT32_MAX;
		// テクスチャ左上
		YMath::Vector2 texLeftTop_;
		// テクスチャサイズ
		YMath::Vector2 texSize_;

		// 非表示
		bool isInvisible_ = false;
	public:
		// 設定用ステータス
		struct Status
		{
			YMath::Vector2 size_; // サイズ
			YMath::Vector2 anchor_ = { 0.0f, 0.0f }; // アンカーポイント
			bool isFlipX_ = false; // 左右反転
			bool isFlipY_ = false; // 上下反転
		};
		// テクスチャ設定用ステータス
		struct TexStatus
		{
			UINT index_ = UINT32_MAX; // テクスチャインデックス
			YMath::Vector2 leftTop_ = { 0.0f,0.0f }; // テクスチャ左上
			YMath::Vector2 size_ = { 0.0f,0.0f }; // テクスチャサイズ
		};
	public:
		// 生成
		static Sprite2D* Create(const Status& state, const TexStatus& texState, const bool div = false);
	public:
		// 描画 (テクスチャ + 色 有)
		void Draw(ObjectSprite2D* obj, Color* color, const UINT tex);
		// 描画 (テクスチャ 有)
		void Draw(ObjectSprite2D* obj, const UINT tex);
		// 描画 (色 有)
		void Draw(ObjectSprite2D* obj, Color* color);
		// 描画 (デフォルト)
		void Draw(ObjectSprite2D* obj);
	public:
		// サイズ設定
		void SetSize(const YMath::Vector2& size);
		// アンカーポイント設定
		void SetAnchorPoint(const YMath::Vector2& anchor);
		// フリップ設定
		void SetFrip(const bool isFlipX, const bool isFlipY);
		// テクスチャ左上設定
		void SetTextureLeftTop(const YMath::Vector2& leftTop, const bool adjust = true);
		// テクスチャサイズ設定
		void SetTextureSize(const YMath::Vector2& texSize);
		// テクスチャ矩形設定
		void SetTextureRectangle(const YMath::Vector2& leftTop, const YMath::Vector2& texSize);
		// 全設定
		void SetAllStatus(const Status& state, const TexStatus& texState, const bool div = false);
		// 非表示設定
		void SetInvisible(const bool isInvisible) { isInvisible_ = isInvisible; }
	public:
		// サイズ取得
		YMath::Vector2 Size() const { return size_; }
		// アンカーポイント取得
		YMath::Vector2 AnchorPoint() const { return anchor_; }
	private:
		Sprite2D() = default;
	public:
		~Sprite2D() = default;
	};
}
