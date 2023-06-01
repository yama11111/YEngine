#pragma once
#include "ConstBuffer.h"
#include "CBDirectionalLight.h"
#include "CBPointLight.h"
#include "CBSpotLight.h"
#include <array>

namespace YGame
{
	class CBLightGroup
	{
	
	public:
		
		// 平行光源数
		static const size_t DireLightNum_ = 3;
		
		// 点光源数
		static const size_t PointLightNum_ = 3;
		
		// スポットライト光源数
		static const size_t SpotLightNum_ = 1;
	
	public:
		
		// 定数バッファデータ構造体 (光)
		struct CBData
		{
			YMath::Vector3 ambientColor_; // 環境光の色
			float pad_; // パディング
			std::array<CBDirectionalLight::Data, DireLightNum_> direLights_; // 平行光源
			std::array<CBPointLight::Data, PointLightNum_> pointLights_; // 点光源
			//std::array<CBSpotLight::Data, SpotLightNum_> spotLights_; // スポットライト光源
		};

	public:

		/// <summary>
		/// 生成
		/// </summary>
		/// <param name="ambientColor"> : 環境光</param>
		/// <param name="isMutable"> : シーン遷移時に開放するか</param>
		/// <returns>動的インスタンス (newされたもの)</returns>
		static CBLightGroup* Create(
			const YMath::Vector3& ambientColor = { 1.0f,1.0f,1.0f },
			const bool isMutable = true);
	
	public:

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="ambientColor"> : 環境光</param>
		void Initialize(const YMath::Vector3& ambientColor = { 1.0f,1.0f,1.0f });

		/// <summary>
		/// 描画前コマンド
		/// </summary>
		/// <param name="rootParamIndex"> : ルートパラメータ番号</param>
		void SetDrawCommand(const UINT rootParamIndex);

	public:

		// 色設定 (0.0f ～ 1.0f)
		void SetAmbientColor(const YMath::Vector3& color);

	public:

		// 向き設定 (平行光源)
		void SetDirectionalLightDirection(const size_t index, const YMath::Vector3& direction);

		// 色設定 (平行光源)
		void SetDirectionalLightColor(const size_t index, const YMath::Vector3& color);

		// 有効フラグ設定 (平行光源)
		void SetDirectionalLightActive(const size_t index, const bool isAct);

	public:

		// 座標設定 (点光源)
		void SetPointLightPos(const size_t index, const YMath::Vector3& pos);

		// 色設定 (点光源)
		void SetPointLightColor(const size_t index, const YMath::Vector3& color);
		// 距離減衰係数設定 (点光源)

		void SetPointLightAtten(const size_t index, const YMath::Vector3& atten);

		// 有効フラグ設定 (平行光源)
		void SetPointLightActive(const size_t index, const bool isAct);

	public:

		// 座標設定 (スポットライト光源)
		void SetSpotLightPos(const size_t index, const YMath::Vector3& pos);

		// 向き設定 (スポットライト光源)
		void SetSpotLightDirection(const size_t index, const YMath::Vector3& direction);
		// 色設定 (スポットライト光源)

		void SetSpotLightColor(const size_t index, const YMath::Vector3& color);

		// 距離減衰係数設定 (スポットライト光源)
		void SetSpotLightAtten(const size_t index, const YMath::Vector3& atten);

		// 減衰角度設定 (スポットライト光源)
		void SetSpotLightFactorAngleCos(const size_t index, const float start, const float end);

		// 有効フラグ設定 (スポットライト光源)
		void SetSpotLightActive(const size_t index, const bool isAct);

	private:

		CBLightGroup() = default;
	
	public:

		~CBLightGroup() = default;
	
	private:

		// 定数バッファ(光)
		YDX::ConstBuffer<CBData> cBuff_;
		
		// 環境光の色
		YMath::Vector3 ambientColor_ = { 1.0f,1.0f,1.0f };

		// 平行光源
		std::array<CBDirectionalLight, DireLightNum_> direLights_;
		
		// 点光源
		std::array<CBPointLight, PointLightNum_> pointLights_;
		
		// スポットライト光源
		std::array<SpotLight, SpotLightNum_> spotLights_;
	};
}
