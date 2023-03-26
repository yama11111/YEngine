#pragma once
#include "Vertices.h"
#include "ShaderCommon.h"
#include "PipelineSet.h"
#include "Material.h"
#include "ViewProjection.h"
#include "LightGroup.h"
#include "Color.h"
#include <unordered_map>
#include <memory>

// include回避用
struct aiMesh;

namespace YGame
{
	// モデル用オブジェクトコモンクラス
	class ModelObjectCommon
	{
	protected:
		// 定数バッファデータ構造体
		struct CBData
		{
			YMath::Matrix4 matWorld_;	 // ワールド行列
			YMath::Matrix4 matViewProj_; // ビュープロジェクション行列
			YMath::Vector3 cameraPos_;	 // カメラ座標
		};
	protected:
		// ビュープロジェクションポインタ (デフォルト)
		static std::unique_ptr<ViewProjection> sDefVP_;
		// 光源ポインタ (デフォルト)
		static std::unique_ptr<LightGroup> sDefLightGroup_;
		// 色 (デフォルト)
		static std::unique_ptr<Color> sDefColor_;
	public:
		// 静的初期化 (デフォルト値設定)
		static void StaticInitialize();
	};

	// モデルコモンクラス
	class ModelCommon
	{
	public:
		// 頂点データ構造体
		struct VData
		{
			YMath::Vector3 pos_;	 // xyz座標
			YMath::Vector3 normal_;	 // 法線ベクトル
			YMath::Vector2 uv_;		 // uv座標
			YMath::Vector3 tangent_; // 接空間
			YMath::Vector4 color_;	 // 頂点色
		};
		// メッシュ構造体
		struct Mesh
		{
			// 頂点インデックス配列
			YDX::VertexIndex<VData> vtIdx_;
			// 頂点法線スムーシング用データ
			std::unordered_map<unsigned short, std::vector<unsigned short>> smoothData_;
			// マテリアル
			Material mtrl_;
		};
	public:
		// ルートパラメータ番号
		enum class RootParameterIndex 
		{
			TransformCB	 = 0, // 行列
			ColorCB		 = 1, // 色
			LightCB		 = 2, // 光
			MaterialCB	 = 3, // マテリアル
			TexDT		 = 4, // テクスチャ
		};
	private:
		// シェーダーセット
		class ShaderSet : public YDX::ShaderCommon
		{
		public:
			// 頂点シェーダオブジェクト
			Microsoft::WRL::ComPtr<ID3DBlob> vsBlob_ = nullptr;
			// ピクセルシェーダオブジェクト
			Microsoft::WRL::ComPtr<ID3DBlob> psBlob_ = nullptr;
		public:
			// シェーダーファイル読み込み
			void Load(ID3DBlob* errorBlob);
		};
		// パイプライン設定構造体
		struct PipelineSetStatus : public YDX::PipelineSet::IStatus
		{
			// 初期化
			void Initialize(ID3DBlob* errorBlob_) override;
		};
	protected:
		// 法線計算
		static void CalculateNormals(std::vector<VData>& v, const std::vector<uint16_t> indices);
		// 法線計算 (スムーシング)
		static void CalculateSmoothedVertexNormals(std::vector<VData>& vertices,
			std::unordered_map<unsigned short, std::vector<unsigned short>>& smoothData);
		// 頂点情報読み込み(assimp)
		static YDX::VertexIndex<VData> LoadVertices(const aiMesh* src, bool invU, bool invV, bool isNormalized);
	protected:
		// パイプライン設定
		static YDX::PipelineSet sPipelineSet_;
	public:
		// 静的初期化
		static void StaticInitialize();
		// 静的描画コマンド
		static void StaticSetDrawCommand();
	};
}

