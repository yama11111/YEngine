#pragma once
#include "Model.h"
#include "Lerp.h"
#include "Timer.h"
#include "Power.h"

namespace YGame
{
	class IParticle
	{
	public:
		bool isAlive_ = false;
	protected:
		std::unique_ptr<YGame::ObjectModel> obj_;
	public:
		virtual void Update() = 0;
		virtual void Draw(const YGame::ViewProjection& pVP_, YGame::LightGroup* pLightGroup) = 0;
	public:
		virtual ~IParticle() = default;
	};

	class FireSpark : public IParticle
	{
	private:
		YMath::Timer aliveTim_;

		bool isSwitching_ = false;
		YMath::Power swayingPow_;
		YMath::Vector3 spd_;

		YMath::Ease<float> scaleEas_;
		std::unique_ptr<YGame::Color> color_;
		YMath::Ease<float> alphaEas_;
	public:
		void Emit(
			const uint32_t aliveTime,
			const uint32_t swayingTime,
			const YMath::Vector3& speed,
			const YMath::Vector3& pos, const float scale,
			const YMath::Vector4& color);
		void Update() override;
		void Draw(const YGame::ViewProjection& vp, YGame::LightGroup* pLightGroup) override;
	public:
		~FireSpark() override = default;
	private:
		static YGame::Model* pModel_;
	public:
		static void StaticInitialize(YGame::Model* pModel);
	};
}
