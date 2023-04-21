#include "Mesh.h"
#include "FileUtillity.h"
#include <cassert>
#include <fstream>
#include <sstream>

#pragma region 名前空間

using YGame::Mesh;
using YGame::Texture;
using YMath::Vector2;
using YMath::Vector3;
using YMath::Vector4;

#pragma endregion

Mesh* Mesh::CreateCube()
{
	// インスタンス生成 (動的)
	Mesh* instance = new Mesh();

	// 頂点
	std::vector<VData> v =
	{
		// 前
		{{ -1.0f, -1.0f, -1.0f }, {}, {0.0f, 1.0f}}, // 左下
		{{ -1.0f,  1.0f, -1.0f }, {}, {0.0f, 0.0f}}, // 左上
		{{  1.0f, -1.0f, -1.0f }, {}, {1.0f, 1.0f}}, // 右下
		{{  1.0f,  1.0f, -1.0f }, {}, {1.0f, 0.0f}}, // 右上

		// 後
		{{ -1.0f, -1.0f,  1.0f }, {}, {1.0f, 1.0f}}, // 左下
		{{ -1.0f,  1.0f,  1.0f }, {}, {1.0f, 0.0f}}, // 左上
		{{  1.0f, -1.0f,  1.0f }, {}, {0.0f, 1.0f}}, // 右下
		{{  1.0f,  1.0f,  1.0f }, {}, {0.0f, 0.0f}}, // 右上

		// 左
		{{ -1.0f, -1.0f, -1.0f }, {}, {1.0f, 1.0f}}, // 左下
		{{ -1.0f, -1.0f,  1.0f }, {}, {0.0f, 1.0f}}, // 左上
		{{ -1.0f,  1.0f, -1.0f }, {}, {1.0f, 0.0f}}, // 右下
		{{ -1.0f,  1.0f,  1.0f }, {}, {0.0f, 0.0f}}, // 右上

		// 右
		{{  1.0f, -1.0f, -1.0f }, {}, {0.0f, 1.0f}}, // 左下
		{{  1.0f, -1.0f,  1.0f }, {}, {1.0f, 1.0f}}, // 左上
		{{  1.0f,  1.0f, -1.0f }, {}, {0.0f, 0.0f}}, // 右下
		{{  1.0f,  1.0f,  1.0f }, {}, {1.0f, 0.0f}}, // 右上

		// 下
		{{ -1.0f, -1.0f,  1.0f }, {}, {0.0f, 0.0f}}, // 左下
		{{ -1.0f, -1.0f, -1.0f }, {}, {0.0f, 1.0f}}, // 左上
		{{  1.0f, -1.0f,  1.0f }, {}, {1.0f, 0.0f}}, // 右下
		{{  1.0f, -1.0f, -1.0f }, {}, {1.0f, 1.0f}}, // 右上

		// 上
		{{ -1.0f,  1.0f,  1.0f }, {}, {0.0f, 0.0f}}, // 左下
		{{ -1.0f,  1.0f, -1.0f }, {}, {0.0f, 1.0f}}, // 左上
		{{  1.0f,  1.0f,  1.0f }, {}, {1.0f, 0.0f}}, // 右下
		{{  1.0f,  1.0f, -1.0f }, {}, {1.0f, 1.0f}}, // 右上
	};
	// インデックス
	std::vector<uint16_t> i =
	{
		// 前
		0, 1, 2, // 三角形1つ目
		2, 1, 3, // 三角形2つ目

		// 後
		6, 7, 4, // 三角形1つ目
		4, 7, 5, // 三角形2つ目

		// 左
		8, 9, 10, // 三角形1つ目
		10, 9, 11, // 三角形2つ目

		// 右
		14, 15, 12, // 三角形1つ目
		12, 15, 13, // 三角形2つ目

		// 下
		16, 17, 18, // 三角形1つ目
		18, 17, 19, // 三角形2つ目

		//// 上
		22, 23, 20, // 三角形1つ目
		20, 23, 21, // 三角形2つ目
	};

	// 法線を計算
	CalculateNormals(v, i);

	// 頂点インデックス初期化(代入)
	instance->vtIdx_.Initialize(v, i);
	// マテリアル初期化
	instance->pTex_ = Texture::Load("white1x1.png", false);

	// インスタンスを返す
	return instance;
}

Mesh* Mesh::CreateCube(const std::string& texFileName)
{
	// 生成
	Mesh* instance = CreateCube();

	// マテリアル初期化
	instance->pTex_ = Texture::Load(texFileName, true);

	// インスタンスを返す
	return instance;
}

Mesh* Mesh::Load(const std::string& directoryPath, const std::string& objFileName, const bool isSmoothing)
{
	// インスタンス生成 (動的)
	Mesh* instance = new Mesh();

	// 頂点
	std::vector<VData> v;
	// インデックス
	std::vector<uint16_t> i;
	// 頂点法線スムーシング用データ
	std::unordered_map<unsigned short, std::vector<unsigned short>> sd;
	// テクスチャ
	Texture* pTex = nullptr;

	// ファイルストリーム
	std::ifstream file;

	// .objファイルを開く
	file.open(directoryPath + objFileName);
	// ファイルオープン失敗をチェック
	assert(file);

	// 頂点座標
	std::vector<Vector3> positions;
	// 法線
	std::vector<Vector3> normals;
	// UV座標
	std::vector<Vector2> uvs;

	// 1行ずつ読み込み
	std::string line;
	while (std::getline(file, line))
	{
		// 1行分の文字列をストリームに変換して解析しやすくする
		std::istringstream lineStream(line);

		// 半角スペース区切りで行の先頭文字列を取得
		std::string key;
		std::getline(lineStream, key, ' ');

#pragma region マテリアル

		// 先頭文字列が "mtllib" ならマテリアル
		if (key == "mtllib")
		{
			// マテリアルファイル名取得
			std::string mtlFileName;
			lineStream >> mtlFileName;
			// マテリアル読み込み
			pTex = LoadMaterial(directoryPath, mtlFileName);
		}

#pragma endregion

#pragma region 頂点データ

		// 先頭文字列が "v" なら頂点座標
		if (key == "v")
		{
			// 頂点座標
			Vector3 pos;
			// 読み込み
			lineStream >> pos.x_;
			lineStream >> pos.y_;
			lineStream >> pos.z_;
			// 追加
			positions.push_back(pos);
		}
		// 先頭文字列が "vt" ならテクスチャ
		if (key == "vt")
		{
			// UV座標
			Vector2 uv;
			// 読み込み
			lineStream >> uv.x_;
			lineStream >> uv.y_;
			// v反転
			uv.y_ = 1.0f - uv.y_;
			// 追加
			uvs.push_back(uv);
		}
		// 先頭文字列が "vn" なら法線ベクトル
		if (key == "vn")
		{
			// 法線
			Vector3 normal;
			// 読み込み
			lineStream >> normal.x_;
			lineStream >> normal.y_;
			lineStream >> normal.z_;
			// 追加
			normals.push_back(normal);
		}

#pragma endregion

#pragma region インデックスデータ

		// 先頭文字列が "f" ならポリゴン(三角形)
		if (key == "f")
		{
			// 半角スペース区切りで行の続き読み込み
			std::string indexString;
			while (std::getline(lineStream, indexString, ' '))
			{
				// 頂点インデックス1個分の文字列をストリームに変換して解析しやすくする
				std::istringstream indexStream(indexString);

				// インデックスデータ
				uint16_t idPositon, idNormal, idTexcoord;

				// 読み込み
				indexStream >> idPositon;
				// '/' 飛ばす
				indexStream.seekg(1, std::ios_base::cur);
				// 読み込み
				indexStream >> idTexcoord;
				// '/' 飛ばす
				indexStream.seekg(1, std::ios_base::cur);
				// 読み込み
				indexStream >> idNormal;

				// 頂点データ
				VData vData;
				vData.pos_ = positions[static_cast<size_t>(idPositon - 1)];
				vData.normal_ = normals[static_cast<size_t>(idNormal - 1)];
				vData.uv_ = uvs[static_cast<size_t>(idTexcoord - 1)];

				// 追加
				v.push_back(vData);
				// 追加
				i.push_back(static_cast<uint16_t>(i.size()));
				// 追加
				if (isSmoothing)
				{
					sd[idPositon].emplace_back(static_cast<unsigned short>(v.size() - 1));
				}
			}
		}

#pragma endregion

	}

	// ファイルを閉じる
	file.close();

	// スムーシングするか
	if (isSmoothing)
	{
		// スムーシング計算
		CalculateSmoothedVertexNormals(v, sd);
	}


	// 頂点インデックス初期化(代入)
	instance->vtIdx_.Initialize(v, i);
	// スムースデータ代入
	instance->smoothData_ = sd;
	// テクスチャ代入
	instance->pTex_ = pTex;

	// インスタンスを返す
	return instance;
}

void Mesh::CalculateNormals(std::vector<VData>& v, const std::vector<uint16_t>& indices)
{
	// 三角形1つごとに計算していく
	for (size_t i = 0; i < indices.size() / 3; i++)
	{
		// 三角形のインデックスを取り出す
		unsigned short index0 = indices[i * 3 + 0];
		unsigned short index1 = indices[i * 3 + 1];
		unsigned short index2 = indices[i * 3 + 2];

		// 三角形を構成する頂点座標ベクトルに代入
		Vector3 p0 = v[index0].pos_;
		Vector3 p1 = v[index1].pos_;
		Vector3 p2 = v[index2].pos_;

		// p0->p1ベクトル、p0->p2ベクトルを計算 (ベクトルの減算)
		Vector3 v1 = p1 - p0;
		Vector3 v2 = p2 - p0;

		// 外積は両方から垂直なベクトル
		Vector3 normal = v1.Cross(v2);

		// 正規化 (長さを1にする)
		normal = normal.Normalized();

		// 求めた法線を頂点データに代入
		v[index0].normal_ = normal;
		v[index1].normal_ = normal;
		v[index2].normal_ = normal;
	}
}

void Mesh::CalculateSmoothedVertexNormals(std::vector<VData>& vertices,
	std::unordered_map<unsigned short, std::vector<unsigned short>>& smoothData)
{
	// スムースデータの数だけ
	auto itr = smoothData.begin();
	for (; itr != smoothData.end(); ++itr)
	{
		// 次の要素を代入
		std::vector<unsigned short>& v = itr->second;

		// 法線
		Vector3 normal = {};

		// 計算
		for (unsigned short index : v)
		{
			normal += vertices[index].normal_;
		}
		normal = (normal / (float)v.size()).Normalized();

		// 代入
		for (unsigned short index : v)
		{
			vertices[index].normal_ = normal;
		}
	}
}

Texture* Mesh::LoadMaterial(const std::string& directoryPath, const std::string& fileName)
{
	// 戻り値用
	Texture* pTex = nullptr;

	// ファイルストリーム
	std::ifstream file;
	// .mtlファイルを開く
	file.open(directoryPath + fileName);
	// ファイルオープン失敗をチェック
	assert(file);

	// 1行ずつ読み込み
	std::string line;
	while (std::getline(file, line))
	{
		// 1行分の文字列をストリームに変換して解析しやすくする
		std::istringstream lineStream(line);

		// 半角スペース区切りで行の先頭文字列を取得
		std::string key;
		std::getline(lineStream, key, ' ');

		// 先頭のタブ文字は無視する
		if (key[0] == '\t') { key.erase(key.begin()); }

		//// 先頭文字列が "newmtl" ならマテリアル名
		//if (key == "newmtl")
		//{
		//	// 読み込み
		//	lineStream >> m.name_;
		//}
		//// 先頭文字列が "Ka" ならアンビエント色
		//if (key == "Ka")
		//{
		//	// 読み込み
		//	lineStream >> m.ambient_.x_;
		//	lineStream >> m.ambient_.y_;
		//	lineStream >> m.ambient_.z_;
		//}
		//// 先頭文字列が "Kd" ならディフューズ色
		//if (key == "Kd")
		//{
		//	// 読み込み
		//	lineStream >> m.diffuse_.x_;
		//	lineStream >> m.diffuse_.y_;
		//	lineStream >> m.diffuse_.z_;
		//}
		//// 先頭文字列が "vn" ならスペキュラー色
		//if (key == "Ks")
		//{
		//	// 読み込み
		//	lineStream >> m.specular_.x_;
		//	lineStream >> m.specular_.y_;
		//	lineStream >> m.specular_.z_;
		//}

		// 先頭文字列が "map_Kd" ならテクスチャファイル名
		if (key == "map_Kd")
		{
			//// 読み込み
			//lineStream >> m.texFileName_;

			// テクスチャファイル名取得
			std::string texFileName;
			lineStream >> texFileName;

			// 読み込み
			pTex = Texture::Load(directoryPath, texFileName);
		}
	}

	// ファイルを閉じる
	file.close();

	// テクスチャを返す
	return pTex;
}

void Mesh::Draw(const UINT texRPIndex)
{
	// テクスチャ
	pTex_->SetDrawCommand(texRPIndex);

	// 頂点バッファを送る + 描画コマンド
	vtIdx_.Draw();
}
