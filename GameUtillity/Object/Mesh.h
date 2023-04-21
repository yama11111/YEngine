#pragma once
#include "Vertices.h"
#include "Texture.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include <unordered_map>
#include <string>
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

		// テクスチャ
		Texture* pTex_;

	public:

		/// <summary>
		/// 生成(立方体)
		/// </summary>
		/// <returns>動的インスタンス (new されたもの)</returns>
		static Mesh* CreateCube();

		/// <summary>
		/// 生成(立方体)
		/// </summary>
		/// <param name="texFileName"> : 画像のファイル名</param>
		/// <returns>動的インスタンス (new されたもの)</returns>
		static Mesh* CreateCube(const std::string& texFileName);

		/// <summary>
		/// メッシュ読み込み
		/// </summary>
		/// <param name="directoryPath"> : ディレクトリパス </param>
		/// <param name="objFileName"> : objファイル名 </param>
		/// <param name="isSmoothing"> : スムーシングするか</param>
		/// <returns>動的インスタンス (new されたもの)</returns>
		static Mesh* Load(const std::string& directoryPath, const std::string& objFileName, const bool isSmoothing);

	public:

		/// <summary>
		/// 描画
		/// </summary>
		/// <param name="texRPIndex"> : テクスチャ用ルートパラメータ番号</param>
		void Draw(const UINT texRPIndex);

	private:

		/// <summary>
		/// 法線計算
		/// </summary>
		/// <param name="v"></param>
		/// <param name="indices"></param>
		static void CalculateNormals(std::vector<VData>& v, const std::vector<uint16_t>& indices);

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

	private:

		Mesh() = default;

	public:

		~Mesh() = default;
	};
}

