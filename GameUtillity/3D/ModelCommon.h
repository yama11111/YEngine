#pragma once
#include "Vertices.h"
#include "ShaderCommon.h"
#include "PipelineSet.h"
#include "TextureManager.h"
#include "Color.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Matrix4.h"
#include <unordered_map>
#include <memory>

struct aiMesh;
struct aiMaterial;

namespace YGame
{
	class ModelCommon
	{
	public:
		// 頂点データ構造体
		struct VData
		{
			YMath::Vector3 pos_;	  // xyz座標
			YMath::Vector3 normal_;  // 法線ベクトル
			YMath::Vector2 uv_;	  // uv座標
			YMath::Vector3 tangent_; // 接空間
			YMath::Vector4 color_;	  // 頂点色
		};
		// 定数バッファデータ構造体
		struct CBData
		{
			YMath::Matrix4 matWorld_;	  // ワールド行列
			YMath::Matrix4 matViewProj_; // ビュープロジェクション行列
			YMath::Vector3 cameraPos_;	  // カメラ座標
		};
		// 定数バッファデータ構造体 (マテリアル)
		struct MaterialCBData
		{
			YMath::Vector3 ambient_;  // アンビエント係数
			float pad1_; // パディング1
			YMath::Vector3 diffuse_;  // ディフューズ係数
			float pad2_; // パディング2
			YMath::Vector3 specular_; // スペキュラー係数
			float alpha_;		   // アルファ
		};
		// マテリアル構造体
		struct Material
		{
		public:
			std::string name_;			 // マテリアル名
			YMath::Vector3 ambient_;		 // アンビエント影響度
			YMath::Vector3 diffuse_;		 // ディフューズ影響度
			YMath::Vector3 specular_;		 // スペキュラー影響度
			float alpha_;				 // アルファ値
		public:
			std::string texFileName_;	 // テクスチャファイル名
			UINT texIndex_;				 // テクスチャインデックス
		public:
			YDX::ConstBuffer<MaterialCBData> cBuff_; // 定数バッファ(マテリアル2)
		public:
			Material(); // コンストラクタ
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
			ObjCB		 = 0, // 行列
			LightCB		 = 1, // 光
			ColorCB		 = 2, // 色
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
		// マテリアル読み込み(assimp)
		static Material LoadMaterial(const std::string directoryPath, const aiMaterial* src, const std::string extension);
		// マテリアル読み込み
		static Material LoadMaterial(const std::string& directoryPath, const std::string& fileName);
	protected:
		// パイプライン設定
		static YDX::PipelineSet pipelineSet_;
		// 静的テクスチャマネージャーポインタ
		static TextureManager* pTexManager_;
	public:
		// 静的初期化
		static void StaticInitialize();
		// 静的描画コマンド
		static void StaticSetDrawCommand();
	};
}

