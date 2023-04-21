#pragma once
#include "ConstBuffer.h"
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

	private:

		// 定数バッファ(マテリアル)
		YDX::ConstBuffer<CBData> cBuff_;

		// アンビエント影響度 (環境光)
		YMath::Vector3 ambient_;

		// ディフューズ影響度 (拡散反射光)
		YMath::Vector3 diffuse_;

		// スペキュラー影響度 (鏡面反射光)
		YMath::Vector3 specular_;

		// アルファ値
		float alpha_ = 1.0f;

	public:

		/// <summary>
		/// 生成
		/// </summary>
		/// <param name="ambient"> : アンビエント影響度 (環境光)</param>
		/// <param name="diffuse"> : ディフューズ影響度 (拡散反射光)</param>
		/// <param name="specular"> : スペキュラー影響度 (鏡面反射光)</param>
		/// <param name="alpha"> : アルファ値</param>
		/// <param name="isMutable"> : シーン遷移時に開放するか</param>
		/// <returns>動的インスタンス (newされたもの)</returns>
		static Material* Create(
			const YMath::Vector3& ambient = { 0.8f,0.8f,0.8f },
			const YMath::Vector3& diffuse = { 1.0f,1.0f,1.0f },
			const YMath::Vector3& specular = { 1.0f,1.0f,1.0f },
			const float alpha = 1.0f,
			const bool isMutable = true);

	public:

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="ambient"> : アンビエント影響度 (環境光)</param>
		/// <param name="diffuse"> : ディフューズ影響度 (拡散反射光)</param>
		/// <param name="specular"> : スペキュラー影響度 (鏡面反射光)</param>
		/// <param name="alpha"> : アルファ値</param>
		void Initialize(
			const YMath::Vector3& ambient = { 1.0f,1.0f,1.0f },
			const YMath::Vector3& diffuse = { 1.0f,1.0f,1.0f },
			const YMath::Vector3& specular = { 1.0f,1.0f,1.0f },
			const float alpha = 1.0f);

		/// <summary>
		/// 描画前コマンド
		/// </summary>
		/// <param name="rpIndex"> : ルートパラメータ番号</param>
		void SetDrawCommand(const UINT rpIndex);

	public:

		/// <summary>
		/// アンビエント影響度 (環境光)取得
		/// </summary>
		/// <returns>アンビエント影響度 (環境光)</returns>
		YMath::Vector3 GetAmbient() { return ambient_; }

		/// <summary>
		/// アンビエント影響度 (環境光)設定
		/// </summary>
		/// <param name="ambient">アンビエント影響度 (環境光)</param>
		void SetAmbient(const YMath::Vector3& ambient);


		/// <summary>
		/// ディフューズ影響度 (拡散反射光)取得
		/// </summary>
		/// <returns>ディフューズ影響度 (拡散反射光)</returns>
		YMath::Vector3 GetDiffuse() { return diffuse_; }

		/// <summary>
		/// ディフューズ影響度 (拡散反射光)設定
		/// </summary>
		/// <param name="diffuse">ディフューズ影響度 (拡散反射光)</param>
		void SetDiffuse(const YMath::Vector3& diffuse);


		/// <summary>
		/// スペキュラー影響度 (鏡面反射光)取得
		/// </summary>
		/// <returns>スペキュラー影響度 (鏡面反射光)</returns>
		YMath::Vector3 GetSpecular() { return specular_; }

		/// <summary>
		/// スペキュラー影響度 (鏡面反射光)設定
		/// </summary>
		/// <param name="specular">スペキュラー影響度 (鏡面反射光)</param>
		void SetSpecular(const YMath::Vector3& specular);


		/// <summary>
		/// アルファ値取得
		/// </summary>
		/// <returns>アルファ値</returns>
		float GetAlpha() { return alpha_; }

		/// <summary>
		/// アルファ値設定
		/// </summary>
		/// <param name="alpha">アルファ値</param>
		void SetAlpha(const float alpha);

	private:

		Material() = default;

	public:

		~Material() = default;

	};
}
