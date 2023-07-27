#pragma once
#include "Vertices.h"
#include "Texture.h"
#include "Node.h"
#include "Vector2.h"
#include "Vector4.h"
#include <fbxsdk.h>
#include <unordered_map>
#include <memory>

namespace YGame
{
	class Mesh
	{

	public:

		// 頂点データ構造体
		struct VData
		{
			YMath::Vector3 pos_;	 // xyz座標
			YMath::Vector3 normal_;	 // 法線ベクトル
			YMath::Vector2 uv_;		 // uv座標
			//YMath::Vector3 tangent_; // 接空間
			//YMath::Vector4 color_;	 // 頂点色
		};

	private:
		
		// 頂点インデックス配列
		YDX::VertexIndex<VData> vtIdx_;

		// 頂点法線スムーシング用データ
		std::unordered_map<unsigned short, std::vector<unsigned short>> smoothData_;

		// ノード
		Node node_;

		// テクスチャ
		std::unordered_map<std::string, Texture*> pTexs_{};

	public:
		
		/// <summary>
		/// 生成(立方体)
		/// </summary>
		/// <param name="pTexs"> : テクスチャポインタ配列</param>
		/// <returns>動的インスタンス (new されたもの)</returns>
		static Mesh* CreateCube(const std::unordered_map<std::string, Texture*> pTexs);

		/// <summary>
		/// メッシュ(.obj)読み込み
		/// </summary>
		/// <param name="directoryPath"> : ディレクトリパス </param>
		/// <param name="objFileName"> : objファイル名 </param>
		/// <param name="isSmoothing"> : スムーシングするか</param>
		/// <returns>動的インスタンス (new されたもの)</returns>
		static Mesh* LoadObj(const std::string& directoryPath, const std::string& objFileName, const bool isSmoothing);

		/// <summary>
		/// メッシュ(.fbx)読み込み
		/// </summary>
		/// <param name="folderPath"> : モデルフォルダのパス</param>
		/// <param name="fbxNode"> :  FBXノード</param>
		/// <param name="isSmoothing"> : スムーシングするか</param>
		/// <returns>動的インスタンス (new されたもの)</returns>
		static Mesh* LoadFbx(const std::string& folderPath, FbxNode* fbxNode, const bool isSmoothing);

	public:

		/// <summary>
		/// 描画
		/// </summary>
		/// <param name="rpIndices"> : ルートパラメータ情報 + 番号</param>
		void SetDrawCommand(const std::unordered_map<std::string, uint32_t>& rpIndices);

	private:

		/// <summary>
		/// 法線計算
		/// </summary>
		/// <param name="vertices"> : 頂点配列</param>
		/// <param name="indices"> : インデックス配列</param>
		static void CalculateNormals(std::vector<VData>& vertices, const std::vector<uint16_t>& indices);

		/// <summary>
		/// 法線計算 (スムーシング)
		/// </summary>
		/// <param name="vertices"> : 頂点配列</param>
		/// <param name="smoothData"> : 保存用スムースデータ</param>
		static void CalculateSmoothedVertexNormals(std::vector<VData>& vertices,
			std::unordered_map<unsigned short, std::vector<unsigned short>>& smoothData);
		
		/// <summary>
		/// マテリアル(テクスチャ)読み込み
		/// </summary>
		/// <param name="directoryPath"> : ディレクトリパス</param>
		/// <param name="fileName"> : ファイル名</param>
		/// <returns>テクスチャポインタ</returns>
		static Texture* LoadMaterial(const std::string& directoryPath, const std::string& fileName);


#pragma region FbxLoader

	public:

		// FBX読み込み用
		class FbxLoader
		{

		public:

			/// <summary>
			/// 頂点読み取り
			/// </summary>
			/// <param name="vertices"> : 頂点配列</param>
			/// <param name="fbxNode"> : 解析するノード</param>
			static void ParseMeshVertices(std::vector<VData>& vertices, FbxMesh* fbxMesh);

			/// <summary>
			/// 面読み取り
			/// </summary>
			/// <param name="vertices"> : 頂点配列</param>
			/// <param name="indices"> : インデックス配列</param>
			/// <param name="fbxMesh"> : 解析するメッシュ</param>
			static void ParseMeshFaces(std::vector<VData>& vertices, std::vector<uint16_t>& indices, FbxMesh* fbxMesh);

			/// <summary>
			/// マテリアル読み取り
			/// </summary>
			/// <param name="folderPath"> : モデルフォルダのパス</param>
			/// <param name="refPtrTex"> : 参照テクスチャポインタ</param>
			/// <param name="fbxNode"> : 解析するノード</param>
			static void ParseMaterial(const std::string& folderPath, Texture*& refPtrTex, FbxNode* fbxNode);

		public:

			/// <summary>
			/// Fbx用の行列から行列に変換
			/// </summary>
			/// <param name="fbxMat"> : Fbx用行列</param>
			/// <returns>行列</returns>
			static YMath::Matrix4 ConvertFromFbxAMatrixToMatrix4(const FbxAMatrix& fbxMat);

		};

#pragma endregion


	private:

		Mesh() = default;

	public:

		~Mesh() = default;
	};
}

