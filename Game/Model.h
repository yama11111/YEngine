#pragma once
#include "Transform.h"
#include "ViewProjection.h"
#include "Vertices.h"
#include "PipelineSet.h"
#include "TextureManager.h"
#include "Material.h"

namespace Game
{
	class Model
	{
	private:
		// 頂点インデックス
		DX::VertexIndex3D vtIdx_;
		// マテリアル
		Material mtrl_;
		// 定数バッファ(マテリアル2)
		DX::ConstBuffer<DX::MaterialData2> cbMtrl_;
	public:
		// 動的ポインタ(立方体)
		static Model* Create();
		// モデル読み込み
		static Model* Load(const char* fileName);
	public:
		// 描画
		void Draw(Transform& trfm, ViewProjection& vp, const UINT tex);
	private:
		// コンストラクタ
		Model() = default;
	private:
		// パイプライン設定
		static DX::PipelineSet pplnSet_;
		// 静的定数バッファマネージャーポインタ
		static DX::ConstBufferManager* pCBManager_;
		// 静的テクスチャマネージャーポインタ
		static TextureManager* pTexManager_;
	public:
		// 静的初期化構造体
		struct StaticInitState
		{
			DX::ConstBufferManager* pCBManage;
			TextureManager* pTexManager;
			std::vector<D3D12_ROOT_PARAMETER>* rootParams;
		};
	public:
		// 静的初期化
		static void StaticInitialize(const StaticInitState& state);
		// 静的描画コマンド
		static void StaticSetDrawCommand();
	};
}
