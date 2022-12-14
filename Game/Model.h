#pragma once
#include "Vertices.h"
#include "Material.h"
#include "PipelineSet.h"
#include "Object.h"
#include "ViewProjection.h"

struct aiMesh;
struct aiMaterial;

namespace Game
{
	class Model
	{
	private:
		struct Mesh
		{
			// 頂点インデックス配列
			DX::VertexIndex3D vtIdx_;
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
		// 頂点情報読み込み(assimp)
		static DX::VertexIndex3D LoadVertices(const aiMesh* src, bool invU, bool invV, bool isNormalized);
		// マテリアル読み込み(assimp)
		static Material LoadMaterial(const std::string directoryPath, const aiMaterial* src, 
			const std::string extension);
		// 拡張子変換
		static std::string ReplaceExtension(const std::string fileName, const std::string extention);
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
