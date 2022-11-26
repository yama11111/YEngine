#pragma once
#include "Vertices.h"
#include "Material.h"
#include "PipelineSet.h"
#include "Object.h"
#include "ViewProjection.h"

namespace Game
{
	class Model
	{
	private:
		// 頂点インデックス
		DX::VertexIndex3D vtIdx_;
		// マテリアル
		Material mtrl_;
	public:
		// 生成(立方体)
		static Model* Create();
		// モデル読み込み
		static Model* Load(const std::string& modelName);
	public:
		// 描画
		void Draw(Object& obj, const ViewProjection& vp, const UINT tex);
		void Draw(Object& obj, const ViewProjection& vp);
	private:
		// コンストラクタ
		Model() = default;
	private:
		// パイプライン設定
		static DX::PipelineSet pplnSet_;
	public:
		// 静的初期化
		static void StaticInitialize(std::vector<D3D12_ROOT_PARAMETER>* rootParams);
		// 静的描画コマンド
		static void StaticSetDrawCommand();
	};
}
