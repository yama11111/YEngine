#pragma once
#include "Transform.h"
#include "ViewProjection.h"
#include "Vertices.h"
#include "PipelineSet.h"
#include "TextureManager.h"

namespace Object
{
	class Model
	{
	private:
		// 頂点インデックス
		DX::VertexIndex3D vtIdx;
	public:
		// コンストラクタ
		Model();
		// 描画
		void Draw(Transform& trfm, ViewProjection& vp, const UINT tex);
	private:
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
