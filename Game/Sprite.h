#pragma once
#include "Vertices.h"
#include "PipelineSet.h"
#include "Object.h"
#include "TextureManager.h"

namespace Game
{
	class Sprite
	{
	private:
		// 頂点データ
		DX::Vertices<DX::SpriteVData> vt_;
		// テクスチャ
		UINT tex_ = -1;
		// サイズ
		Math::Vec2 size_;
		// アンカーポイント
		Math::Vec2 anchor_;
		// 左右反転
		bool isFlipX_ = false;
		// 上下反転
		bool isFlipY_ = false;
		// 非表示
		bool isInvisible_ = false;
	public:
		// 設定用ステータス
		struct Status
		{
			Math::Vec2 size; // サイズ
			Math::Vec2 anchor = { 0.0f, 0.0f }; // アンカーポイント
			bool isFlipX = false; // 左右反転
			bool isFlipY = false; // 上下反転
		};
	public:
		// 生成
		static Sprite* Create(const Status& state, const UINT tex);
	public:
		// 描画
		void Draw(Object& obj, const UINT tex);
		void Draw(Object& obj);
	public:
		// サイズ設定
		void SetSize(const Math::Vec2& size);
		// アンカーポイント設定
		void SetAnchorPoint(const Math::Vec2& anchor);
		// フリップ設定
		void SetFrip(const bool isFlipX, const bool isFlipY);
		// 全設定
		void SetStatus(const Status& state);
		// 非表示設定
		void SetInvisible(const bool isInvisible) { isInvisible_ = isInvisible; }
	public:
		// サイズ取得
		Math::Vec2 Size() const { return size_; }
		// アンカーポイント取得
		Math::Vec2 AnchorPoint() const { return anchor_; }
	private:
		// コンストラクタ
		Sprite() = default;
	private:
		// 静的射影変換行列(平行投影)
		static Math::Mat4 projection_;
		// パイプライン設定
		static DX::PipelineSet pplnSet_;
		// 静的テクスチャマネージャーポインタ
		static TextureManager* pTexManager_;
	public:
		// 静的初期化
		static void StaticInitialize(TextureManager* pTexManager, std::vector<D3D12_ROOT_PARAMETER>* rootParams);
		// 静的描画コマンド
		static void StaticSetDrawCommand();
	};
}
