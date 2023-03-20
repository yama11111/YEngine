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

using YGame::ModelCommon;
using YGame::Model;
using YGame::ObjectModel;
using YMath::Vector2;
using YMath::Vector3;
using YMath::Vector4;

#pragma endregion

#pragma region ルートパラメータ番号

static const UINT ObjIndex	 = static_cast<UINT>(ModelCommon::RootParameterIndex::ObjCB); // obj
static const UINT LigIndex	 = static_cast<UINT>(ModelCommon::RootParameterIndex::LightCB); // light
static const UINT ColIndex	 = static_cast<UINT>(ModelCommon::RootParameterIndex::ColorCB); // color
static const UINT MateIndex	 = static_cast<UINT>(ModelCommon::RootParameterIndex::MaterialCB); // material
static const UINT TexIndex	 = static_cast<UINT>(ModelCommon::RootParameterIndex::TexDT); // tex

#pragma endregion


ObjectModel* ObjectModel::Create(const Status& state)
{
	// インスタンス生成 (動的)
	ObjectModel* instance = new ObjectModel();

	// 定数バッファ生成
	instance->cBuff_.Create();
	// 初期化
	instance->Initialize(state);

	// インスタンスを返す
	return instance;
}

void Model::Draw(ObjectModel* pObj, const ViewProjection& vp, LightGroup* lightGroup, Color* pColor, const UINT tex)
{
	// 描画しないなら弾く
	if (isInvisible_) { return; }

	// ----- シェーダーに定数バッファを送る ----- //

	// 行列
	pObj->cBuff_.map_->matWorld_ = pObj->m_;
	pObj->cBuff_.map_->matViewProj_ = vp.view_ * vp.pro_;
	pObj->cBuff_.map_->cameraPos_ = vp.eye_;
	pObj->cBuff_.SetDrawCommand(ObjIndex);

	// 光
	lightGroup->SetDrawCommand(LigIndex);

	// 色
	pColor->SetDrawCommand(ColIndex);

	// メッシュ毎に違うバッファ
	for (size_t i = 0; i < meshes_.size(); i++)
	{
		// マテリアル
		meshes_[i].mtrl_.cBuff_.SetDrawCommand(MateIndex);
		
		// テクスチャ
		pTexManager_->SetDrawCommand(TexIndex, tex);
		
		// 頂点バッファを送る + 描画コマンド
		meshes_[i].vtIdx_.Draw();
	}
}
void Model::Draw(ObjectModel* pObj, const ViewProjection& vp, LightGroup* pLightGroup, const UINT tex)
{
	// デフォルトの色を渡して描画
	Draw(pObj, vp, pLightGroup, defColor_.get(), tex);
}
void Model::Draw(ObjectModel* pObj, const ViewProjection& vp, LightGroup* lightGroup, Color* pColor)
{
	// 描画しないなら弾く
	if (isInvisible_) { return; }
	
	// ----- シェーダーに定数バッファを送る ----- //

	// 行列
	pObj->cBuff_.map_->matWorld_ = pObj->m_;
	pObj->cBuff_.map_->matViewProj_ = vp.view_ * vp.pro_;
	pObj->cBuff_.map_->cameraPos_ = vp.eye_;
	pObj->cBuff_.SetDrawCommand(ObjIndex);

	// 光
	lightGroup->SetDrawCommand(LigIndex);

	// 色
	pColor->SetDrawCommand(ColIndex);

	// メッシュ毎に違うバッファ
	for (size_t i = 0; i < meshes_.size(); i++)
	{
		// マテリアル
		meshes_[i].mtrl_.cBuff_.SetDrawCommand(MateIndex);
		
		// テクスチャ
		pTexManager_->SetDrawCommand(TexIndex, meshes_[i].mtrl_.texIndex_);
		
		// 頂点バッファを送る + 描画コマンド
		meshes_[i].vtIdx_.Draw();
	}
}
void Model::Draw(ObjectModel* pObj, const ViewProjection& vp, LightGroup* pLightGroup)
{
	// デフォルトの色を渡して描画
	Draw(pObj, vp, pLightGroup, defColor_.get());
}

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
	// 色初期化
	instance->defColor_.reset(Color::Create());

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
			m = LoadMaterial(directoryPath, mtlFileName);
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
	// 色初期化
	instance->defColor_.reset(Color::Create());

	// インスタンスを返す
	return instance;
}

Model* Model::Load(const LoadStatus& state)
{
	// インスタンス生成 (動的)
	Model* instance = new Model();

	// ディレクトリパス設定
	std::string directoryPath = "Resources/Models/" + state.directoryPath_;

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
	const aiScene* scene = importer.ReadFile(directoryPath + state.modelFileName_, flag);
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
			LoadVertices(pMesh, state.isInverseU_, state.isInverseV_, state.isNormalized_);

		// マテリアル読み込み
		const aiMaterial* pMaterial = scene->mMaterials[i];
		instance->meshes_[i].mtrl_ = 
			LoadMaterial(directoryPath, pMaterial, state.extension_);
	}

	// 後処理
	scene = nullptr;

	// 色初期化
	instance->defColor_.reset(Color::Create());

	// インスタンスを返す
	return instance;
}
