#pragma once
#include "ModelCommon.h"
#include "Vertices.h"
#include "Material.h"
#include "Object.h"
#include "ViewProjection.h"
#include "Vec2.h"

namespace YGame
{
	class Model : private ModelCommon
	{
	public:
		// メッシュ構造体
		struct Mesh
		{
			// 頂点インデックス配列
			YDX::VertexIndex<VData> vtIdx_;
			// マテリアル
			Material mtrl_;
		};
	private:
		// メッシュ配列
		std::vector<Mesh> meshes_;
	public:
		// 読み込み設定構造体
		struct LoadStatus 
		{
			std::string directoryPath_;
			std::string modelFileName_;
			bool isInverseU_;
			bool isInverseV_;
			bool isNormalized_ = false;
			std::string extension_ = "";
		};
	public:
		// 生成(立方体)
		static Model* Create();
		// モデル読み込み
		static Model* Load(const std::string& modelFileName);
		// モデル読み込み(assimp)
		static Model* Load(const LoadStatus& state);
	private:
		// 法線計算
		static void Normalized(std::vector<VData>& v, const std::vector<uint16_t> indices);
		// 頂点情報読み込み(assimp)
		static YDX::VertexIndex<VData> LoadVertices(const aiMesh* src, bool invU, bool invV, bool isNormalized);
		// マテリアル読み込み(assimp)
		static Material LoadMaterial(const std::string directoryPath, const aiMaterial* src, 
			const std::string extension);
		// 拡張子変換
		static std::string ReplaceExtension(const std::string fileName, const std::string extention);
	public:
		// 描画 (テクスチャ有)
		void Draw(Object& obj, const ViewProjection& vp, const UINT tex);
		// 描画
		void Draw(Object& obj, const ViewProjection& vp);
	private:
		// コンストラクタ
		Model() = default;
	};
}
