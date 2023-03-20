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
		/// <summary>
		/// 生成 + 初期化
		/// </summary>
		/// <param name="state"> : 設定用ステータス</param>
		/// <param name="(Vector3) state.pos_"> : 位置</param>
		/// <param name="(Vector3) state.rota_"> : 回転</param>
		/// <param name="(Vector3) state.scale_"> : 大きさ</param>
		/// <returns>動的インスタンス (newされたもの)</returns>
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
			YMath::Vector2 anchor_ = { 0.5f, 0.5f }; // アンカーポイント
			bool isFlipX_ = false; // 左右反転
			bool isFlipY_ = false; // 上下反転
		};
		// テクスチャ設定用ステータス
		struct TexStatus
		{
			UINT index_; // テクスチャインデックス
			YMath::Vector2 leftTop_ = { 0.0f,0.0f }; // テクスチャ左上
			YMath::Vector2 size_ = { 0.0f,0.0f }; // テクスチャサイズ
		};
	public:
		/// <summary>
		/// 生成
		/// </summary>
		/// <param name="state"> : スプライト設定</param>
		/// <param name="(Vector2) state.size_"> : 大きさ</param>
		/// <param name="(Vector2) state.anchor_"> : アンカーポイント (初期値は中心)</param>
		/// <param name="(bool) state.isFlipX_"> : X反転するか</param>
		/// <param name="(bool) state.isFlipY_"> : Y反転するか</param>
		/// <param name="--------------------------------"></param>
		/// <param name="texState"> : テクスチャ設定</param>
		/// <param name="(UINT) texState.index_"> : テクスチャインデックス</param>
		/// <param name="(Vector2) texState.leftTop_"> : テクスチャ左上</param>
		/// <param name="(Vector2) texState.size_"> : テクスチャサイズ</param>
		/// <param name="--------------------------------"></param>
		/// <param name="isDiv"> : 画像サイズに合わせるか</param>
		/// <returns>動的インスタンス (newされたもの)</returns>
		static Sprite2D* Create(const Status& state, const TexStatus& texState, const bool isDiv = false);
	public:
		/// <summary>
		/// 描画 (テクスチャ + 色 有)
		/// </summary>
		/// <param name="pObj"> : オブジェクトポインタ</param>
		/// <param name="pColor"> : 色ポインタ</param>
		/// <param name="tex"> : テクスチャインデックス</param>
		void Draw(ObjectSprite2D* pObj, Color* pColor, const UINT tex);
		/// <summary>
		/// 描画 (テクスチャ 有)
		/// </summary>
		/// <param name="pObj"> : オブジェクトポインタ</param>
		/// <param name="tex"> : テクスチャインデックス</param>
		void Draw(ObjectSprite2D* pObj, const UINT tex);
		/// <summary>
		/// 描画 (色 有)
		/// </summary>
		/// <param name="pObj"> : オブジェクトポインタ</param>
		/// <param name="pColor"> : 色ポインタ</param>
		void Draw(ObjectSprite2D* pObj, Color* pColor);
		/// <summary>
		/// 描画 (デフォルト)
		/// </summary>
		/// <param name="pObj"> : オブジェクトポインタ</param>
		void Draw(ObjectSprite2D* pObj);
	public:
		// スプライトサイズ設定
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
		/// <summary>
		/// 全設定
		/// </summary>
		/// <param name="state"> : スプライト設定</param>
		/// <param name="(Vector2) state.size_"> : 大きさ</param>
		/// <param name="(Vector2) state.anchor_"> : アンカーポイント(中心)</param>
		/// <param name="(bool) state.isFlipX_"> : X反転するか</param>
		/// <param name="(bool) state.isFlipY_"> : Y反転するか</param>
		/// <param name="--------------------------------"></param>
		/// <param name="texState"> : テクスチャ設定</param>
		/// <param name="(UINT) texState.index_"> : テクスチャインデックス</param>
		/// <param name="(Vector2) texState.leftTop_"> : テクスチャ左上</param>
		/// <param name="(Vector2) texState.size_"> : テクスチャサイズ</param>
		/// <param name="--------------------------------"></param>
		/// <param name="isDiv"> : 画像サイズに合わせるか</param>
		void SetAllStatus(const Status& state, const TexStatus& texState, const bool isDiv = false);
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
