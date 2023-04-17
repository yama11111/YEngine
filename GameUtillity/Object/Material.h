#pragma once
#include "ConstBuffer.h"
#include "Texture.h"
#include "Vector3.h"

namespace YGame
{
	// マテリアル構造体
	struct Material
	{
	public:
		// 定数バッファデータ構造体 (マテリアル)
		struct CBData
		{
			YMath::Vector3 ambient_;  // アンビエント係数
			float pad1_; // パディング1
			YMath::Vector3 diffuse_;  // ディフューズ係数
			float pad2_; // パディング2
			YMath::Vector3 specular_; // スペキュラー係数
			float alpha_;			  // アルファ値
		};
	public:
		// マテリアル名
		std::string name_;
		// アンビエント影響度
		YMath::Vector3 ambient_;
		// ディフューズ影響度
		YMath::Vector3 diffuse_;
		// スペキュラー影響度
		YMath::Vector3 specular_;
		// アルファ値
		float alpha_;

		// テクスチャファイル名
		std::string texFileName_;
		// テクスチャ
		Texture* pTex_ = nullptr;
		
		// 定数バッファ(マテリアル)
		YDX::ConstBuffer<CBData> cBuff_;
	public:
		/// <summary>
		/// マテリアル読み込み
		/// </summary>
		/// <param name="directoryPath"> : ディレクトリパス</param>
		/// <param name="fileName"> : ファイル名</param>
		/// <returns>マテリアル</returns>
		static Material Load(const std::string& directoryPath, const std::string& fileName);
	public:
		/// <summary>
		/// 画像読み込み
		/// </summary>
		/// <param name="texFileName"> : 画像ファイル名</param>
		void LoadTexture(const std::string& texFileName);
		/// <summary>
		/// 描画前コマンド
		/// </summary>
		/// <param name="mateRPIndex"> : ルートパラメータ番号</param>
		/// <param name="texRPIndex"> : ルートパラメータ番号</param>
		void SetDrawCommand(UINT mateRPIndex, UINT texRPIndex);
	private:
		// 静的デフォルトテクスチャ
		static Texture* spDefTexIndex_;
	public:
		// 静的初期化
		static void StaticInitialize();
	public:
		// コンストラクタ
		Material();
	};
}
