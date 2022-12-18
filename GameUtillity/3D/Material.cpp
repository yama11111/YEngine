#include "Material.h"
#include <cassert>
#include <fstream>
#include <sstream>

using Game::Material;

Game::TextureManager* Material::pTexManager_ = nullptr;

void Material::StaticInitialize(TextureManager* pTexManager)
{
	assert(pTexManager);
	pTexManager_ = pTexManager;
}

Material::Material() :
	ambient_(0.3f, 0.3f, 0.3f),
	diffuse_(1.0f, 1.0f, 1.0f),
	specular_(0.0f, 0.0f, 0.0f),
	alpha_(1.0f),
	texIndex_(0)
{
	cbMtrl_.Create();
	cbMtrl_.map_->ambient_ = ambient_;
	cbMtrl_.map_->diffuse_ = diffuse_;
	cbMtrl_.map_->specular_ = specular_;
	cbMtrl_.map_->alpha_ = alpha_;
}

void Material::Load(const std::string& directoryPath, const std::string& mtlFileName)
{
	// ファイルストリーム
	std::ifstream file;
	// .mtlファイルを開く
	file.open(directoryPath + mtlFileName);
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
			lineStream >> name_;
		}
		// 先頭文字列が "Ka" ならアンビエント色
		if (key == "Ka")
		{
			// 読み込み
			lineStream >> ambient_.x_;
			lineStream >> ambient_.y_;
			lineStream >> ambient_.z_;
		}
		// 先頭文字列が "Kd" ならディフューズ色
		if (key == "Kd")
		{
			// 読み込み
			lineStream >> diffuse_.x_;
			lineStream >> diffuse_.y_;
			lineStream >> diffuse_.z_;
		}
		// 先頭文字列が "vn" ならスペキュラー色
		if (key == "Ks")
		{
			// 読み込み
			lineStream >> specular_.x_;
			lineStream >> specular_.y_;
			lineStream >> specular_.z_;
		}

		// 先頭文字列が "map_Kd" ならテクスチャファイル名
		if (key == "map_Kd")
		{
			// 読み込み
			lineStream >> textureFileName_;
			texIndex_ = pTexManager_->Load(directoryPath, textureFileName_);
		}

	}

	file.close();
}

void Material::LoadTexture(const std::string& directoryPath, const std::string& texFileName)
{
	textureFileName_ = texFileName;
	texIndex_ = pTexManager_->Load(directoryPath, texFileName);
}

void Material::SetDrawCommand(const UINT tex)
{
	pTexManager_->SetDrawCommand(tex);
	cbMtrl_.SetDrawCommand();
}

void Material::SetDrawCommand()
{
	pTexManager_->SetDrawCommand(texIndex_);
	cbMtrl_.SetDrawCommand();
}
