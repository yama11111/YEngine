#pragma once
#include "Vertices.h"
#include "ShaderCommon.h"
#include "PipelineSet.h"
#include "TextureManager.h"
#include "Color.h"
#include "Vec2.h"
#include "Vec3.h"
#include "Mat4.h"
#include <unordered_map>

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
			YMath::Vec3 pos_;	  // xyz座標
			YMath::Vec3 normal_;  // 法線ベクトル
			YMath::Vec2 uv_;	  // uv座標
			YMath::Vec3 tangent_; // 接空間
			YMath::Vec4 color_;	  // 頂点色
		};
		// 定数バッファデータ構造体
		struct CBData
		{
			YMath::Mat4 matWorld_;	  // ワールド行列
			YMath::Mat4 matViewProj_; // ビュープロジェクション行列
			YMath::Vec3 cameraPos_;	  // カメラ座標
		};
		// 定数バッファデータ構造体 (マテリアル)
		struct MaterialCBData
		{
			YMath::Vec3 ambient_;  // アンビエント係数
			float pad1_; // パディング1
			YMath::Vec3 diffuse_;  // ディフューズ係数
			float pad2_; // パディング2
			YMath::Vec3 specular_; // スペキュラー係数
			float alpha_;		   // アルファ
		};
		// マテリアル構造体
		struct Material
		{
		public:
			std::string name_;			 // マテリアル名
			YMath::Vec3 ambient_;		 // アンビエント影響度
			YMath::Vec3 diffuse_;		 // ディフューズ影響度
			YMath::Vec3 specular_;		 // スペキュラー影響度
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
			ModelCB,
			LightCB,
			ColorCB,
			MaterialCB,
			TexDT,
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
			void Initialize(ID3DBlob* errorBlob_) override;
		};
	protected:
		// パイプライン設定
		static YDX::PipelineSet pipelineSet_;
		// 静的テクスチャマネージャーポインタ
		static TextureManager* pTexManager_;
	public:
		// 静的初期化ステータス
		struct StaticInitStatus
		{
			// テクスチャマネージャーポインタ
			TextureManager* pTexManager_;
		};
	public:
		// 静的初期化
		static void StaticInitialize(const StaticInitStatus& state);
		// 静的描画コマンド
		static void StaticSetDrawCommand();
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
	};
}

