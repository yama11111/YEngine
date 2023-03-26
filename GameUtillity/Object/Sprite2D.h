#pragma once
#include "Sprite2DCommon.h"
#include "Transform.h"

namespace YGame
{
	// スプライト2D用オブジェクトクラス
	class Sprite2DObject :
		public Transform,
		private Sprite2DObjectCommon
	{
	private:
		// 定数バッファ (行列)
		YDX::ConstBuffer<Sprite2DObjectCommon::CBData> cBuff_;
		// 色ポインタ
		Color* pColor_ = nullptr;
	public:
		/// <summary>
		/// 生成 + 初期化 (デフォルト初期化)
		/// </summary>
		/// <param name="status"> : 設定用ステータス</param>
		/// <param name="(Vector3) status.pos_"> : 位置</param>
		/// <param name="(Vector3) status.rota_"> : 回転</param>
		/// <param name="(Vector3) status.scale_"> : 大きさ</param>
		/// <returns>動的インスタンス (newされたもの)</returns>
		static Sprite2DObject* Create(const Status& status);
		/// <summary>
		/// 生成 + 初期化 (Transform以外は nullの時 デフォルトで初期化)
		/// </summary>
		/// <param name="status"> : 設定用ステータス</param>
		/// <param name="(Vector3) status.pos_"> : 位置</param>
		/// <param name="(Vector3) status.rota_"> : 回転</param>
		/// <param name="(Vector3) status.scale_"> : 大きさ</param>
		/// <param name="-------------------------------------"></param>
		/// <param name="pColor"> : 色ポインタ</param>
		/// <returns>動的インスタンス (newされたもの)</returns>
		static Sprite2DObject* Create(const Status& status, Color* pColor);
	public:
		// 色設定 (null = Default)
		void SetColor(Color* pColor);
	public:
		// 描画前コマンド
		void SetDrawCommand();
	private:
		Sprite2DObject() = default;
	public:
		~Sprite2DObject() override = default;
	};

	// スプライト2Dクラス
	class Sprite2D : private Sprite2DCommon
	{
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
		/// <param name="status"> : スプライト設定</param>
		/// <param name="(Vector2) status.size_"> : 大きさ</param>
		/// <param name="(Vector2) status.anchor_"> : アンカーポイント (初期値は中心)</param>
		/// <param name="(bool) status.isFlipX_"> : X反転するか</param>
		/// <param name="(bool) status.isFlipY_"> : Y反転するか</param>
		/// <param name="--------------------------------"></param>
		/// <param name="texStatus"> : テクスチャ設定</param>
		/// <param name="(UINT) texStatus.index_"> : テクスチャインデックス</param>
		/// <param name="(Vector2) texStatus.leftTop_"> : テクスチャ左上</param>
		/// <param name="(Vector2) texStatus.size_"> : テクスチャサイズ</param>
		/// <param name="--------------------------------"></param>
		/// <param name="isDiv"> : 画像サイズに合わせるか</param>
		/// <returns>動的インスタンス (newされたもの)</returns>
		static Sprite2D* Create(const Status& status, const TexStatus& texStatus, const bool isDiv = false);
	public:
		/// <summary>
		/// 描画
		/// </summary>
		/// <param name="pObj"> : オブジェクトポインタ</param>
		void Draw(Sprite2DObject* pObj);
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
		/// <param name="status"> : スプライト設定</param>
		/// <param name="(Vector2) status.size_"> : 大きさ</param>
		/// <param name="(Vector2) status.anchor_"> : アンカーポイント(中心)</param>
		/// <param name="(bool) status.isFlipX_"> : X反転するか</param>
		/// <param name="(bool) status.isFlipY_"> : Y反転するか</param>
		/// <param name="--------------------------------"></param>
		/// <param name="texStatus"> : テクスチャ設定</param>
		/// <param name="(UINT) texStatus.index_"> : テクスチャインデックス</param>
		/// <param name="(Vector2) texStatus.leftTop_"> : テクスチャ左上</param>
		/// <param name="(Vector2) texStatus.size_"> : テクスチャサイズ</param>
		/// <param name="--------------------------------"></param>
		/// <param name="isDiv"> : 画像サイズに合わせるか</param>
		void SetAllStatus(const Status& status, const TexStatus& texStatus, const bool isDiv = false);
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
