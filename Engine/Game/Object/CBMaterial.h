#pragma once
#include "ConstBuffer.h"
#include "Vector3.h"

namespace YGame
{
	// マテリアル構造体
	struct CBMaterial
	{
	
	public:
		
		// 定数バッファデータ構造体 (マテリアル)
		struct CBData
		{
			YMath::Vector3 ambient_;  // アンビエント係数
			float pad1_;
			YMath::Vector3 diffuse_;  // ディフューズ係数
			float pad2_;
			YMath::Vector3 specular_; // スペキュラー係数
			float alpha_;			  // アルファ値
		};

	public:

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="ambient"> : アンビエント影響度 (環境光)</param>
		/// <param name="diffuse"> : ディフューズ影響度 (拡散反射光)</param>
		/// <param name="specular"> : スペキュラー影響度 (鏡面反射光)</param>
		/// <param name="alpha"> : アルファ値</param>
		/// <param name="isMutable"> : シーン遷移時に開放するか</param>
		/// <returns>動的インスタンス (newされたもの)</returns>
		static CBMaterial* Create(
			const YMath::Vector3& ambient = { 1.0f,1.0f,1.0f },
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
		/// <param name="rootParamIndex"> : ルートパラメータ番号</param>
		void SetDrawCommand(const UINT rootParamIndex);
	
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

		CBMaterial() = default;

	public:

		~CBMaterial() = default;

	private:

		// 定数バッファ(色)
		YDX::ConstBuffer<CBData> cBuff_;

		// アンビエント影響度 (環境光)
		YMath::Vector3 ambient_ = { 1.0f,1.0f,1.0f };

		// ディフューズ影響度 (拡散反射光)
		YMath::Vector3 diffuse_ = { 1.0f,1.0f,1.0f };

		// スペキュラー影響度 (鏡面反射光)
		YMath::Vector3 specular_ = { 1.0f,1.0f,1.0f };

		// アルファ値
		float alpha_ = 1.0f;

	};
}
