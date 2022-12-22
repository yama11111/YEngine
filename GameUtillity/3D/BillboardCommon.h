#pragma once
#include "PipelineSet.h"
#include "TextureManager.h"
#include "Vec3.h"

namespace YGame
{
	class BillboardCommon
	{
	public:
		// 頂点データ
		struct VData
		{
			YMath::Vec3 pos_; // xyz座標
		};
	protected:
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

