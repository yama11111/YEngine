#pragma once
#include "Vec2.h"
#include "Vec3.h"
#include "Mat4.h"
#include "PipelineSet.h"
#include "TextureManager.h"

namespace YGame
{
	class SpriteCommon
	{
	public:
		// 頂点データ構造体
		struct VData
		{
			YMath::Vec3 pos_; // xyz座標
			YMath::Vec2 uv_;  // uv座標
		};
	protected:
		// 静的射影変換行列(平行投影)
		static YMath::Mat4 projection_;
		// パイプライン設定
		static YDX::PipelineSet pplnSet_;
		// 静的テクスチャマネージャーポインタ
		static TextureManager* pTexManager_;
	public:
		// 静的初期化ステータス
		struct StaticInitStatus
		{
			// テクスチャマネージャーポインタ
			TextureManager* pTexManager_;
			// ルートパラメータポインタ
			std::vector<D3D12_ROOT_PARAMETER>* rootParams_;
		};
	public:
		// 静的初期化
		static void StaticInitialize(const StaticInitStatus& state);
		// 静的描画コマンド
		static void StaticSetDrawCommand();
	};
}
