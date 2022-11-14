#pragma once
#include "Transform.h"
#include "ViewProjection.h"
#include "Vertices.h"
#include "PipelineSet.h"
#include "TextureManager.h"
#include <string>

namespace Game
{
	struct Material
	{
		std::string name_; // マテリアル名
		Math::Vec3 ambient_; // アンビエント影響度
		Math::Vec3 diffuse_; // ディフューズ影響度
		Math::Vec3 specular_; // スペキュラー影響度
		float alpha_; // アルファ値
		std::string textureFileName_; // テクスチャファイル名
		Material() 
		{
			ambient_ = { 0.3f,0.3f,0.3f };
			diffuse_ = { 0.0f,0.0f,0.0f };
			specular_ = { 0.0f,0.0f,0.0f };
			alpha_ = 1.0f;
		}
	};

	class Model
	{
	private:
		// 頂点インデックス
		DX::VertexIndex3D vtIdx_;
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
		// 静的テクスチャマネージャーポインタ
		static TextureManager* pTexManager_;
	public:
		// 静的初期化
		static void StaticInitialize(TextureManager* pTexManager, std::vector<D3D12_ROOT_PARAMETER>* rootParams);
		// 静的描画コマンド
		static void StaticSetDrawCommand();
	};
}
