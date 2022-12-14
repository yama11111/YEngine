#pragma once
#include "Vec3.h"
#include "ConstBuffer.h"
#include "TextureManager.h"

namespace Game
{
	class Material
	{
	public:
		std::string name_; // マテリアル名
		Math::Vec3 ambient_; // アンビエント影響度
		Math::Vec3 diffuse_; // ディフューズ影響度
		Math::Vec3 specular_; // スペキュラー影響度
		float alpha_; // アルファ値
		std::string textureFileName_; // テクスチャファイル名
		UINT texIndex_ = UINT32_MAX;
	private:
		// 定数バッファ(マテリアル2)
		DX::ConstBuffer<DX::MaterialCBData> cbMtrl_;
	public:
		// コンストラクタ
		Material();
	public:
		// マテリアル読み込み
		void Load(const std::string& directoryPath, const std::string& mtlFileName);
		// テクスチャ読み込み
		void LoadTexture(const std::string& directoryPath, const std::string& texFileName);
		// 描画前コマンド
		void SetDrawCommand(const UINT tex);
		// 描画前コマンド
		void SetDrawCommand();
	private:
		// 静的テクスチャマネージャーポインタ
		static TextureManager* pTexManager_;
	public:
		// 静的初期化
		static void StaticInitialize(TextureManager* pTexManager);
	};
}