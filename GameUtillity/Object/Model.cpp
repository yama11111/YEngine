#include "Model.h"
#include "CalcTransform.h"
#include "FileUtillity.h"
#include <cassert>
#include <fstream>
#include <sstream>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#pragma region 名前空間

using YGame::ModelObject;
using YGame::ModelCommon;
using YGame::Model;
using YMath::Vector2;
using YMath::Vector3;
using YMath::Vector4;

#pragma endregion

#pragma region ルートパラメータ番号

static const UINT TraIndex	 = static_cast<UINT>(ModelCommon::RootParameterIndex::TransformCB); // transform
static const UINT ColIndex	 = static_cast<UINT>(ModelCommon::RootParameterIndex::ColorCB); // color
static const UINT LigIndex	 = static_cast<UINT>(ModelCommon::RootParameterIndex::LightCB); // light
static const UINT MateIndex	 = static_cast<UINT>(ModelCommon::RootParameterIndex::MaterialCB); // material
static const UINT TexIndex	 = static_cast<UINT>(ModelCommon::RootParameterIndex::TexDT); // tex

#pragma endregion


#pragma region ModelObject

ModelObject* ModelObject::Create(const Status& status)
{
	// インスタンスを返す
	return Create(status, nullptr, nullptr, nullptr);
}

ModelObject* ModelObject::Create(const Status& status, ViewProjection* pVP, Color* pColor, LightGroup* pLightGroup)
{
	// インスタンス生成 (動的)
	ModelObject* instance = new ModelObject();

	// 定数バッファ生成
	instance->cBuff_.Create();

	// 初期化(デフォルト)
	instance->Initialize(status);
	instance->SetViewProjection(pVP);
	instance->SetColor(pColor);
	instance->SetLightGroup(pLightGroup);

	// インスタンスを返す
	return instance;
}

void ModelObject::SetViewProjection(ViewProjection* pVP)
{
	// nullなら
	if (pVP == nullptr)
	{
		// デフォルト代入
		pVP_ = sDefVP_.get();
		return;
	}

	// 代入
	pVP_ = pVP;
}
void ModelObject::SetColor(Color* pColor)
{
	// nullなら
	if (pColor == nullptr)
	{
		// デフォルト代入
		pColor_ = sDefColor_.get();
		return;
	}

	// 代入
	pColor_ = pColor;
}
void ModelObject::SetLightGroup(LightGroup* pLightGroup)
{
	// nullなら
	if (pLightGroup == nullptr)
	{
		// デフォルト代入
		pLightGroup_ = sDefLightGroup_.get();
		return;
	}

	// 代入
	pLightGroup_ = pLightGroup;
}

void ModelObject::SetDrawCommand()
{
	// 行列
	cBuff_.map_->matWorld_ = m_;
	cBuff_.map_->matViewProj_ = pVP_->view_ * pVP_->pro_;
	cBuff_.map_->cameraPos_ = pVP_->eye_;
	cBuff_.SetDrawCommand(TraIndex);

	// 色
	pColor_->SetDrawCommand(ColIndex);

	// 光
	pLightGroup_->SetDrawCommand(LigIndex);
}

#pragma endregion


#pragma region Model

Model* Model::Create()
{
	// インスタンス生成 (動的)
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

	// 法線を計算
	CalculateNormals(v, i);

	// クリア + リサイズ(メッシュ1つ)
	instance->meshes_.clear();
	instance->meshes_.resize(1);
	
	// 頂点インデックス初期化(代入)
	instance->meshes_[0].vtIdx_.Initialize(v, i);
	// マテリアル初期化
	instance->meshes_[0].mtrl_ = Material();

	// インスタンスを返す
	return instance;
}

Model* Model::LoadObj(const std::string& modelFileName, const bool isSmoothing)
{
	// インスタンス生成 (動的)
	Model* instance = new Model();
	
	// クリア + リサイズ(メッシュ1つ)
	instance->meshes_.clear();
	instance->meshes_.resize(1);

	// 頂点
	std::vector<VData> v;
	// インデックス
	std::vector<uint16_t> i;
	// 頂点法線スムーシング用データ
	std::unordered_map<unsigned short, std::vector<unsigned short>> sd;
	// マテリアル
	Material m;

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
			m = Material::Load(directoryPath, mtlFileName);
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
	instance->meshes_[0].vtIdx_.Initialize(v, i);
	// スムースデータ代入
	instance->meshes_[0].smoothData_ = sd;
	// マテリアル代入
	instance->meshes_[0].mtrl_ = m;

	// インスタンスを返す
	return instance;
}

Model* Model::Load(const LoadStatus& status)
{
	// インスタンス生成 (動的)
	Model* instance = new Model();

	// ディレクトリパス設定
	std::string directoryPath = "Resources/Models/" + status.directoryPath_;

	// Assimp設定
	Assimp::Importer importer;
	int flag = 0;
	flag |= aiProcess_Triangulate;
	flag |= aiProcess_PreTransformVertices;
	flag |= aiProcess_CalcTangentSpace;
	flag |= aiProcess_GenSmoothNormals;
	flag |= aiProcess_GenUVCoords;
	flag |= aiProcess_RemoveRedundantMaterials;
	flag |= aiProcess_OptimizeMeshes;

	// ファイルを開く
	const aiScene* scene = importer.ReadFile(directoryPath + status.modelFileName_, flag);
	if (scene == nullptr)
	{
		// 無いならエラー
		printf(importer.GetErrorString());
		printf("\n");
		assert(false);
	}

	/// クリア + リサイズ(メッシュの数だけ)
	instance->meshes_.clear();
	instance->meshes_.resize(scene->mNumMeshes);
	
	// メッシュ毎に
	for (size_t i = 0; i < instance->meshes_.size(); i++)
	{
		// 頂点情報読み込み
		const aiMesh* pMesh = scene->mMeshes[i];
		instance->meshes_[i].vtIdx_ = 
			LoadVertices(pMesh, status.isInverseU_, status.isInverseV_, status.isNormalized_);

		// マテリアル読み込み
		const aiMaterial* pMaterial = scene->mMaterials[i];
		instance->meshes_[i].mtrl_ = 
			Material::Load(directoryPath, pMaterial, status.extension_);
	}

	// 後処理
	scene = nullptr;

	// インスタンスを返す
	return instance;
}

void Model::Draw(ModelObject* pObj)
{
	// 描画しないなら弾く
	if (isInvisible_) { return; }

	// 定数バッファをシェーダーに送る
	pObj->SetDrawCommand();

	// メッシュ毎に違うバッファ
	for (size_t i = 0; i < meshes_.size(); i++)
	{
		// マテリアル
		meshes_[i].mtrl_.SetDrawCommand(MateIndex, TexIndex);

		// 頂点バッファを送る + 描画コマンド
		meshes_[i].vtIdx_.Draw();
	}
}

#pragma endregion
