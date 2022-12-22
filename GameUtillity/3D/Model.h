#pragma once
#include "Vertices.h"
#include "Material.h"
#include "PipelineSet.h"
#include "Object.h"
#include "ViewProjection.h"
#include "Vec2.h"

struct aiMesh;
struct aiMaterial;

namespace YGame
{
	class Model
	{
	public:
		// 頂点データ構造体
		struct VData
		{
			YMath::Vec3 pos_;	  // xyz座標
			YMath::Vec3 normal_;  // 法線ベクトル
			YMath::Vec2 uv_;	  // uv座標
			YMath::Vec3 tangent_; // 接空間
			YMath::Vec4 color_;	  // 頂点色
		};
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
	private:
		// パイプライン設定
		static YDX::PipelineSet pplnSet_;
	public:
		// 静的初期化
		static void StaticInitialize(std::vector<D3D12_ROOT_PARAMETER>* rootParams);
		// 静的描画コマンド
		static void StaticSetDrawCommand();
	};
}
