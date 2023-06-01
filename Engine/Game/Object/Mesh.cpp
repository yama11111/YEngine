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
using YMath::Matrix4;

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

Mesh* Mesh::LoadObj(const std::string& directoryPath, const std::string& objFileName, const bool isSmoothing)
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

Mesh* Mesh::LoadFbx(const std::string& folderPath, FbxNode* fbxNode, const bool isSmoothing)
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


	// ノードのメッシュを取得
	FbxMesh* fbxMesh = fbxNode->GetMesh();


	// 頂点読み取り
	FbxLoader::ParseMeshVertices(v, fbxMesh);

	// 面を構成するデータの読み取り
	FbxLoader::ParseMeshFaces(v, i, fbxMesh);

	// マテリアルの読み取り
	FbxLoader::ParseMaterial(folderPath, pTex, fbxNode);


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


#pragma region FbxLoader

void Mesh::FbxLoader::ParseMeshVertices(std::vector<VData>& vertices, FbxMesh* fbxMesh)
{
	// 頂点座標データ数
	const int controlPointsCount = fbxMesh->GetControlPointsCount();

	// 必要数だけ頂点データ配列を確保
	VData vData{};
	vertices.resize(controlPointsCount, vData);


	// FBXメッシュの頂点座標配列を取得
	FbxVector4* pCoord = fbxMesh->GetControlPoints();

	// FBXメッシュの全頂点座標を頂点配列にコピーする
	for (int i = 0; i < controlPointsCount; i++)
	{
		// 頂点読み込み
		VData& refVertex = vertices[i];

		// 座標コピー
		refVertex.pos_.x_ = static_cast<float>(pCoord[i][0]);
		refVertex.pos_.y_ = static_cast<float>(pCoord[i][1]);
		refVertex.pos_.z_ = static_cast<float>(pCoord[i][2]);
	}
}

void Mesh::FbxLoader::ParseMeshFaces(std::vector<VData>& vertices, std::vector<uint16_t>& indices, FbxMesh* fbxMesh)
{
	// 複数メッシュのモデルは非対応
	assert(indices.size() == 0);

	// 面の数
	const int polygonCount = fbxMesh->GetPolygonCount();

	// UVデータの数
	const int textureUVCount = fbxMesh->GetTextureUVCount();

	// UV名リスト
	FbxStringList uvNames;
	fbxMesh->GetUVSetNames(uvNames);


	// 面ごとの情報読み取り
	for (int i = 0; i < polygonCount; i++)
	{
		// 面を構成する頂点の数を取得 (3なら三角ポリゴン)
		const int polygonSize = fbxMesh->GetPolygonSize(i);

		// 5以上は弾く
		assert(polygonSize <= 4);

		// 1頂点ずつ処理
		for (int j = 0; j < polygonSize; j++)
		{
			// FBX頂点配列のインデックス
			int index = fbxMesh->GetPolygonVertex(i, j);

			// 0以下は弾く
			assert(index >= 0);

			// 頂点読み込み
			VData& refVertex = vertices[index];

			// 法線読み込み
			FbxVector4 normal;
			if (fbxMesh->GetPolygonVertexNormal(i, j, normal))
			{
				// 代入
				refVertex.normal_.x_ = static_cast<float>(normal[0]);
				refVertex.normal_.y_ = static_cast<float>(normal[1]);
				refVertex.normal_.z_ = static_cast<float>(normal[2]);
			}

			// テクスチャUV読み込み
			if (textureUVCount > 0)
			{
				FbxVector2 uvs;
				bool lUnmapedUV = false;

				// 0番決め打ちで読み込み
				if (fbxMesh->GetPolygonVertexUV(i, j, uvNames[0], uvs, lUnmapedUV))
				{
					refVertex.uv_.x_ = static_cast<float>(uvs[0]);
					refVertex.uv_.y_ = static_cast<float>(uvs[1]);
				}

				// インデックス配列に頂点インデックス追加
				// 3頂点目までなら
				if (j < 3)
				{
					// 1点追加し、他の2点と三角形を構築する
					indices.push_back(index);
				}
				// 4頂点目
				else
				{
					// 3点追加し、
					// 四角形の 0,1,2,3 の内 2,3,0 で三角形を構築する
					int index2 = indices[indices.size() - 1];
					int index3 = index;
					int index0 = indices[indices.size() - 3];
					indices.push_back(index2);
					indices.push_back(index3);
					indices.push_back(index0);
				}
			}
		}
	}
}

void Mesh::FbxLoader::ParseMaterial(const std::string& folderPath, Texture*& refPtrTex, FbxNode* fbxNode)
{
	// マテリアル数
	const int materialCount = fbxNode->GetMaterialCount();

	// マテリアルがあるなら
	if (materialCount > 0)
	{
		// 先頭のマテリアルを取得
		FbxSurfaceMaterial* pMaterial = fbxNode->GetMaterial(0);

		// テクスチャを読み込んだか
		bool texLoaded = false;

		// マテリアルがあるなら
		if (pMaterial)
		{
			// FbxSurfaceLambertクラスかどうか調べる
			if (pMaterial->GetClassId().Is(FbxSurfaceLambert::ClassId))
			{
				//// 変換
				//FbxSurfaceLambert* pLambert = static_cast<FbxSurfaceLambert*>(pMaterial);

				//// 環境光係数
				//FbxPropertyT<FbxDouble3> ambient = pLambert->Ambient;
				//pModel->ambient.x_ = static_cast<float>(ambient.Get()[0]);
				//pModel->ambient.y_ = static_cast<float>(ambient.Get()[1]);
				//pModel->ambient.z_ = static_cast<float>(ambient.Get()[2]);

				//// 拡散反射光係数
				//FbxPropertyT<FbxDouble3> diffuse = pLambert->Diffuse;
				//pModel->diffuse.x_ = static_cast<float>(diffuse.Get()[0]);
				//pModel->diffuse.y_ = static_cast<float>(diffuse.Get()[1]);
				//pModel->diffuse.z_ = static_cast<float>(diffuse.Get()[2]);
			}

			// ディフューズテクスチャを取り出す
			const FbxProperty diffuseProperty = pMaterial->FindProperty(FbxSurfaceMaterial::sDiffuse);

			// ディフューズテクスチャが有効なら
			if (diffuseProperty.IsValid())
			{
				// テクスチャ取得
				const FbxFileTexture* pTexture = diffuseProperty.GetSrcObject<FbxFileTexture>();

				// テクスチャがあるなら
				if (pTexture)
				{
					// テクスチャファイルパス
					const std::string texFilePath = pTexture->GetFileName();

					// テクスチャファイル名取得
					const std::string texFileName = YUtil::FilePath(texFilePath);

					// テクスチャ読み込み
					refPtrTex = Texture::Load(folderPath, texFileName);

					// 完了
					texLoaded = true;
				}
			}
		}

		// テクスチャを読み込んでいないなら
		if (!texLoaded)
		{
			// デフォルトテクスチャ読み込み
			refPtrTex = Texture::Load("white1x1.png");
		}
	}
}

Matrix4 Mesh::FbxLoader::ConvertFromFbxAMatrixToMatrix4(const FbxAMatrix& fbxMat)
{
	Matrix4 result{};

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			result.m_[i][j] = static_cast<float>(fbxMat.Get(i, j));
		}
	}

	return result;
}

#pragma endregion