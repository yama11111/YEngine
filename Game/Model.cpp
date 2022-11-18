#include "Model.h"
#include <cassert>
#include <fstream>
#include <sstream>
#include <cassert>

using Game::Model;

DX::PipelineSet Model::pplnSet_;
DX::ConstBufferManager* Model::pCBManager_ = nullptr;
Game::TextureManager* Model::pTexManager_ = nullptr;

void Model::StaticInitialize(const StaticInitState& state)
{
	assert(state.pCBManage);
	assert(state.pTexManager);
	pCBManager_ = state.pCBManage;
	pTexManager_ = state.pTexManager;
	pplnSet_.Initialize(DX::PipelineSet::Type::ModelT, state.rootParams);
}

void Model::StaticSetDrawCommand()
{
	pplnSet_.SetDrawCommand();
}

Model* Model::Create()
{
	// インスタンス
	Model* instance = new Model();

	// 頂点
	std::vector<DX::ModelVData> v =
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

	instance->vtIdx_.Initialize(v, i, true, false);
	instance->pCBManager_->CreateCB(instance->cbMtrl_, instance->mtrl_);

	return instance;
}

Model* Model::Load(const char* fileName)
{
	// インスタンス
	Model* instance = new Model();

	// 頂点
	std::vector<DX::ModelVData> v;
	// インデックス
	std::vector<uint16_t> i;

	// ファイルストリーム
	std::ifstream file;
	// .objファイルを開く
	file.open(fileName);
	// ファイルオープン失敗をチェック
	assert(file);

	// 頂点座標
	std::vector<Math::Vec3> positions;
	// 法線
	std::vector<Math::Vec3> normals;
	// UV座標
	std::vector<Math::Vec2> uvs;

	// 1行ずつ読み込み
	std::string line;
	while (std::getline(file, line))
	{
		// 1行分の文字列をストリームに変換して解析しやすくする
		std::istringstream lineStream(line);

		// 半角スペース区切りで行の先頭文字列を取得
		std::string key;
		std::getline(lineStream, key, ' ');

#pragma region 頂点データ

		// 先頭文字列が "v" なら頂点座標
		if (key == "v")
		{	
			// 頂点座標
			Math::Vec3 pos;
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
			Math::Vec2 uv;
			// 読み込み
			lineStream >> uv.x_;
			lineStream >> uv.y_;
			// v反転
			//uv.y_ = 1.0f - uv.y_;
			// 追加
			uvs.push_back(uv);
		}
		// 先頭文字列が "vn" なら法線ベクトル
		if (key == "vn")
		{
			// 法線
			Math::Vec3 normal;
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
				DX::ModelVData vData;
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

	instance->vtIdx_.Initialize(v, i, false, false);
	instance->pCBManager_->CreateCB(instance->cbMtrl_, instance->mtrl_);

	return instance;
}

void Model::Draw(Transform& trfm, ViewProjection& vp, const UINT tex)
{
	pTexManager_->SetDrawCommand(tex);
	trfm.SetDrawCommand(vp.view_, vp.pro_);
	pCBManager_->SetDrawCommand(cbMtrl_);
	vtIdx_.Draw();
}
