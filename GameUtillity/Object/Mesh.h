#pragma once
#include "Vertices.h"
#include "Material.h"
#include "Vector2.h"
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
			YMath::Vector3 tangent_; // 接空間
			YMath::Vector4 color_;	 // 頂点色
		};

	private:
		
		// 頂点インデックス配列
		YDX::VertexIndex<VData> vtIdx_;

		// 頂点法線スムーシング用データ
		std::unordered_map<unsigned short, std::vector<unsigned short>> smoothData_;
		
		// マテリアル
		Material mtrl_;

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
		/// <param name="mateRPIndex"> : ルートパラメータ番号</param>
		/// <param name="texRPIndex"> : ルートパラメータ番号</param>
		void Draw(UINT mateRPIndex, UINT texRPIndex);

	private:

		// 法線計算
		static void CalculateNormals(std::vector<VData>& v, const std::vector<uint16_t>& indices);
		
		// 法線計算 (スムーシング)
		static void CalculateSmoothedVertexNormals(std::vector<VData>& vertices,
			std::unordered_map<unsigned short, std::vector<unsigned short>>& smoothData);

	private:

		Mesh() = default;

	public:

		~Mesh() = default;
	};
}

