#include "Material.h"
#include "FileUtillity.h"
#include <memory>
#include <cassert>
#include <fstream>
#include <sstream>

#pragma region 名前空間

using YGame::Material;
using YGame::Texture;

#pragma endregion

#pragma region Static

Texture* Material::spDefTexIndex_ = nullptr;

void Material::StaticInitialize()
{
	// デフォルトのテクスチャを設定
	spDefTexIndex_ = Texture::Load("white1x1.png", false);
}

#pragma endregion

Material::Material() :
	name_(),
	ambient_(0.8f, 0.8f, 0.8f),
	diffuse_(0.5f, 0.5f, 0.5f),
	specular_(0.10f, 0.10f, 0.10f),
	alpha_(1.0f),
	texFileName_(),
	pTex_(spDefTexIndex_)
{
	// 定数バッファ生成
	cBuff_.Create(false);
	cBuff_.map_->ambient_ = ambient_;
	cBuff_.map_->diffuse_ = diffuse_;
	cBuff_.map_->specular_ = specular_;
	cBuff_.map_->alpha_ = alpha_;
}

Material Material::Load(const std::string& directoryPath, const std::string& fileName)
{
	// 戻り値用
	Material m;

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

		// 先頭文字列が "newmtl" ならマテリアル名
		if (key == "newmtl")
		{
			// 読み込み
			lineStream >> m.name_;
		}
		// 先頭文字列が "Ka" ならアンビエント色
		if (key == "Ka")
		{
			// 読み込み
			lineStream >> m.ambient_.x_;
			lineStream >> m.ambient_.y_;
			lineStream >> m.ambient_.z_;
		}
		// 先頭文字列が "Kd" ならディフューズ色
		if (key == "Kd")
		{
			// 読み込み
			lineStream >> m.diffuse_.x_;
			lineStream >> m.diffuse_.y_;
			lineStream >> m.diffuse_.z_;
		}
		// 先頭文字列が "vn" ならスペキュラー色
		if (key == "Ks")
		{
			// 読み込み
			lineStream >> m.specular_.x_;
			lineStream >> m.specular_.y_;
			lineStream >> m.specular_.z_;
		}

		// 先頭文字列が "map_Kd" ならテクスチャファイル名
		if (key == "map_Kd")
		{
			// 読み込み
			lineStream >> m.texFileName_;
			m.pTex_ = Texture::Load(directoryPath, m.texFileName_);
		}

	}

	// ファイルを閉じる
	file.close();

	// マテリアルを返す
	return m;
}

void Material::LoadTexture(const std::string& texFileName)
{
	// 画像名代入
	texFileName_ = texFileName;
	
	// 画像読み込み
	pTex_ = Texture::Load(texFileName);
}

void Material::SetDrawCommand(UINT mateRPIndex, UINT texRPIndex)
{
	// マテリアル
	cBuff_.SetDrawCommand(mateRPIndex);

	// テクスチャ
	pTex_->SetDrawCommand(texRPIndex);
}
