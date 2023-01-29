#include "Model.h"
#include "CalcTransform.h"
#include "FilePath.h"
#include <cassert>
#include <fstream>
#include <sstream>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

using YGame::ModelCommon;
using YGame::Model;
using YMath::Vec2;
using YMath::Vec3;
using YMath::Vec4;

const UINT ModIndex	 = static_cast<UINT>(ModelCommon::RootParameterIndex::ModelCB);
const UINT ColIndex	 = static_cast<UINT>(ModelCommon::RootParameterIndex::ColorCB);
const UINT MateIndex = static_cast<UINT>(ModelCommon::RootParameterIndex::MaterialCB);
const UINT TexIndex	 = static_cast<UINT>(ModelCommon::RootParameterIndex::TexDT);

void Model::Draw(ObjectModel& obj, const ViewProjection& vp, Color& color, const UINT tex)
{
	obj.cBuff_.map_->mat_ = obj.m_ * vp.view_ * vp.pro_;
	obj.cBuff_.SetDrawCommand(ModIndex);

	color.SetDrawCommand(ColIndex);

	for (size_t i = 0; i < meshes_.size(); i++)
	{
		meshes_[i].mtrl_.cBuff_.SetDrawCommand(MateIndex);
		pTexManager_->SetDrawCommand(TexIndex, tex);
		meshes_[i].vtIdx_.Draw();
	}
}
void Model::Draw(ObjectModel& obj, const ViewProjection& vp, const UINT tex)
{
	Draw(obj, vp, defColor_, tex);
}
void Model::Draw(ObjectModel& obj, const ViewProjection& vp, Color& color)
{
	obj.cBuff_.map_->mat_ = obj.m_ * vp.view_ * vp.pro_;
	obj.cBuff_.SetDrawCommand(ModIndex);

	color.SetDrawCommand(ColIndex);

	for (size_t i = 0; i < meshes_.size(); i++)
	{
		meshes_[i].mtrl_.cBuff_.SetDrawCommand(MateIndex);
		pTexManager_->SetDrawCommand(TexIndex, meshes_[i].mtrl_.texIndex_);
		meshes_[i].vtIdx_.Draw();
	}
}
void Model::Draw(ObjectModel& obj, const ViewProjection& vp)
{
	Draw(obj, vp, defColor_);
}

Model* Model::Create()
{
	// インスタンス
	Model* instance = new Model();

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

	Normalized(v, i);

	instance->meshes_.clear();
	instance->meshes_.resize(1);
	instance->meshes_[0].vtIdx_.Initialize(v, i);
	instance->meshes_[0].mtrl_ = Material();

	return instance;
}

Model* Model::Load(const std::string& modelFileName)
{
	// インスタンス
	Model* instance = new Model();
	instance->meshes_.clear();
	instance->meshes_.resize(1);

	// 頂点
	std::vector<VData> v;
	// インデックス
	std::vector<uint16_t> i;

	// ファイルストリーム
	std::ifstream file;

	// ファイル名
	std::string objFileName  = modelFileName + ".obj";
	objFileName = YUtil::FilePath(objFileName);
	std::string directoryPath = "Resources/Models/" + modelFileName + "/";
	// .objファイルを開く
	file.open(directoryPath + objFileName);
	// ファイルオープン失敗をチェック
	assert(file);

	// 頂点座標
	std::vector<Vec3> positions;
	// 法線
	std::vector<Vec3> normals;
	// UV座標
	std::vector<Vec2> uvs;

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
			instance->meshes_[0].mtrl_ = LoadMaterial(directoryPath, mtlFileName);
		}

#pragma endregion

#pragma region 頂点データ

		// 先頭文字列が "v" なら頂点座標
		if (key == "v")
		{	
			// 頂点座標
			Vec3 pos;
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
			Vec2 uv;
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
			Vec3 normal;
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
				vData.pos_ = positions[idPositon - 1];
				vData.normal_ = normals[idNormal - 1];
				vData.uv_ = uvs[idTexcoord - 1];

				// 追加
				v.push_back(vData);
				// 追加
				i.push_back(static_cast<uint16_t>(i.size()));
			}
		}

#pragma endregion

	}

	file.close();

	instance->meshes_[0].vtIdx_.Initialize(v, i);

	return instance;
}

Model* Model::Load(const LoadStatus& state)
{
	// インスタンス
	Model* instance = new Model();

	std::string directoryPath = "Resources/Models/" + state.directoryPath_;

	Assimp::Importer importer;
	int flag = 0;
	flag |= aiProcess_Triangulate;
	flag |= aiProcess_PreTransformVertices;
	flag |= aiProcess_CalcTangentSpace;
	flag |= aiProcess_GenSmoothNormals;
	flag |= aiProcess_GenUVCoords;
	flag |= aiProcess_RemoveRedundantMaterials;
	flag |= aiProcess_OptimizeMeshes;

	const aiScene* scene = importer.ReadFile(directoryPath + state.modelFileName_, flag);
	if (scene == nullptr)
	{
		printf(importer.GetErrorString());
		printf("\n");
		assert(false);
	}

	instance->meshes_.clear();
	instance->meshes_.resize(scene->mNumMeshes);
	for (size_t i = 0; i < instance->meshes_.size(); i++)
	{
		// 頂点情報読み込み
		const aiMesh* pMesh = scene->mMeshes[i];
		instance->meshes_[i].vtIdx_ = 
			LoadVertices(pMesh, state.isInverseU_, state.isInverseV_, state.isNormalized_);

		// マテリアル読み込み
		const aiMaterial* pMaterial = scene->mMaterials[i];
		instance->meshes_[i].mtrl_ = 
			LoadMaterial(directoryPath, pMaterial, state.extension_);
	}

	scene = nullptr;

	return instance;
}
