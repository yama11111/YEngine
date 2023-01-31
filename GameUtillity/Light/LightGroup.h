#pragma once
#include "ConstBuffer.h"
#include "DirectionalLight.h"
#include <array>

namespace YGame
{
	class LightGroup
	{
	public:
		// 平行光源数
		static const size_t DireLightNum_ = 3;
	public:
		// 定数バッファデータ構造体 (光)
		struct CBData
		{
			YMath::Vec3 ambientColor_; // 環境光の色
			float pad_; // パディング
			std::array<DirectionalLight::CBData, DireLightNum_> direLights_; // 平行光源
		};
	private:
		// 環境光の色
		YMath::Vec3 ambientColor_;
		// 定数バッファ(光)
		YDX::ConstBuffer<CBData> cBuff_;
	private:
		// 平行光源
		std::array<DirectionalLight, DireLightNum_> direLights_;
	public:
		// 生成
		static LightGroup* Create();
	public:
		// 初期化
		void Initialize(const YMath::Vec3& ambientColor = { 1.0f,1.0f,1.0f });
		// 描画前コマンド
		void SetDrawCommand(const UINT rootParamIndex);
	public:
		// 色設定 (0.0f ～ 1.0f)
		void SetAmbientColor(const YMath::Vec3& color);
		// 色設定 (0 ～ 255)
		void SetAmbientColor(const UINT R, const UINT G, const UINT B);
	public:
		// 向き設定 (平行光源)
		void SetDirectionalLightDirection(const size_t index, const YMath::Vec3& direction);
		// 色設定 (平行光源)
		void SetDirectionalLightColor(const size_t index, const YMath::Vec3& color);
		// 有効フラグ設定 (平行光源)
		void SetDirectionalLightActive(const size_t index, const bool isAct);
	public:
		LightGroup();
		~LightGroup() = default;
	};
}
