#pragma once
#include "Model.h"
#include "Lerp.h"
#include "Timer.h"
#include "Power.h"

namespace YGame
{
	// パーティクル基底クラス
	class IParticle
	{
	public:
		// 生存フラグ
		bool isAlive_ = false;
	protected:
		// オブジェクト
		std::unique_ptr<YGame::ModelObject> obj_;
		// 生存タイマー
		YMath::Timer aliveTim_;
	public:
		// 更新
		virtual void Update() = 0;
		// 描画
		virtual void Draw() = 0;
	protected:
		// ビュープロジェクションポインタ
		static YGame::ViewProjection* spVP_;
	public:
		// 静的初期化
		static void StaticInitialize(YGame::ViewProjection* pVP);
	public:
		// デストラクタ
		virtual ~IParticle() = default;
	};

	class FireWork : public IParticle
	{
	private:
		// 位置
		YMath::Ease<YMath::Vector3> posEas_;
		// 回転
		YMath::Ease<YMath::Vector3> rotaEas_;
		// 大きさ
		YMath::Ease<float> scaleEas_;
		// 色
		std::unique_ptr<YGame::Color> color_;
		// アルファ値
		YMath::Ease<float> alphaEas_;
	public:
		void Emit(
			const uint32_t aliveTime,
			const YMath::Ease<YMath::Vector3>& pos,
			const YMath::Ease<YMath::Vector3>& rota,
			const float scale, 
			const YMath::Vector4& color);
		void Update() override;
		void Draw() override;
	private:
		static YGame::Model* spModel_;
	public:
		static void StaticInitialize(YGame::Model* pModel);
	public:
		~FireWork() = default;
	};
}
