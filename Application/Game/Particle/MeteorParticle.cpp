#include "MeteorParticle.h"
#include "BaseGameParticle.h"
#include "ParticleManager.h"

#include "DrawObjectForModel.h"
#include "ConstBufferObject.h"
#include "CBColor.h"
#include "Speed.h"
#include "WorldManager.h"
#include "ColorConfig.h"

#include "MathUtil.h"
#include "MathVector.h"
#include "Lerp.h"
#include "Def.h"

#include <memory>
#include <cmath>

using YGame::MeteorParticle;
using YMath::Vector3;
using YMath::Vector4;

namespace YGame
{
	class impl_MeteorParticle final :
		public MeteorParticle,
		public BaseGameParticle
	{

	public:

		// 生成
		static impl_MeteorParticle* Create();

		// 初期化
		void Initialize(
			const WorldKey worldKey,
			const uint32_t aliveFrame,
			const Vector3& pos,
			const Vector3& endSpeed,
			const Vector3& endScale,
			const Vector4& color,
			const float exponent,
			ViewProjection* pVP);

		// 更新
		void Update() override;

	private:

		DrawObjectForModel* pObj_ = nullptr;

		// 色定数バッファ
		std::unique_ptr<ConstBufferObject<CBColor>> cbColor_;

		// スピードイージング
		YMath::Ease<Vector3> speedEas_;

		// スケールイージング
		YMath::Ease<Vector3> scaleEas_;
	};

	impl_MeteorParticle* impl_MeteorParticle::Create()
	{
		impl_MeteorParticle* newParticle = new impl_MeteorParticle();

		DrawObjectForModel* newObj = DrawObjectForModel::Create({}, nullptr, nullptr, false);

		// オブジェクトのポインタを保持
		newParticle->pObj_ = newObj;
		newParticle->SetObject(newObj);

		newParticle->cbColor_.reset(ConstBufferObject<CBColor>::Create(false));

		return newParticle;
	}

	void impl_MeteorParticle::Initialize(
		const WorldKey worldKey,
		const uint32_t aliveFrame,
		const Vector3& pos,
		const Vector3& endSpeed,
		const Vector3& endScale,
		const Vector4& color,
		const float exponent,
		ViewProjection* pVP)
	{
		BaseGameParticle::Initialize(worldKey, aliveFrame, { pos }, "ModelSingleColor", 1);

		cbColor_->data_.baseColor = color;
		pObj_->InsertConstBuffer(cbColor_.get());
		pObj_->SetViewProjection(pVP);

		speedEas_.Initialize({}, endSpeed, exponent);
		scaleEas_.Initialize({}, endScale, exponent);
	}

	void impl_MeteorParticle::Update()
	{
		if (isAlive_ == false) { return; }

		// タイマーの割合
		float ratio = aliveTimer_.Ratio();

		obj_->transform_.pos_ += speedEas_.In(ratio);
		obj_->transform_.scale_ = scaleEas_.In(ratio);
		obj_->transform_.rota_ = YMath::AdjustAngle(speedEas_.End().Normalized());

		obj_->Update();

		BaseParticle::UpdateLife();
	}
}

namespace
{
	// パーティクル静的に用意
	const size_t skParticleNum = 100;
	std::array<std::unique_ptr<YGame::impl_MeteorParticle>, skParticleNum> sParticles;
	const std::string skTag = "MeteorParticle";
	bool sIsInit = false;
}

void MeteorParticle::StaticInitialize()
{
	if (sIsInit == false)
	{
		// 生成
		for (size_t i = 0; i < sParticles.size(); i++)
		{
			sParticles[i].reset(impl_MeteorParticle::Create());
		}

		sIsInit = true;
	}

	// パーティクルマネージャーに挿入
	std::list<BaseParticle*> particlePtrs;

	for (size_t i = 0; i < sParticles.size(); i++)
	{
		particlePtrs.emplace_back(sParticles[i].get());
	}

	ParticleManager::GetInstance()->InsertParticles(skTag, particlePtrs);
}

static YGame::impl_MeteorParticle* DeadParticlePtr()
{
	// 死んでいるパーティクルを返す
	for (size_t i = 0; i < sParticles.size(); i++)
	{
		if (sParticles[i]->IsAlive() == false)
		{
			return sParticles[i].get();
		}
	}

	return nullptr;
}

void MeteorParticle::Emit(
	const WorldKey worldKey,
	const Vector3& pos,
	const Vector3& speed,
	const Vector4& color,
	ViewProjection* pVP)
{
	// 固有設定
	static const uint32_t kAliveFrame = 120;
	static const float kStartScale = 1.0f;
	static const float kExponent = 3.0f;

	// 死んでいるパーティクルを初期化 (無いなら弾く)
	impl_MeteorParticle* pParticle = DeadParticlePtr();
	if (pParticle == nullptr) { return; }

	Vector3 scale = Vector3(kStartScale, kStartScale, kStartScale);
	float ratio = YMath::Clamp(speed.Length() / 20.0f, 0.0f, 1.0f);

	scale.z = YMath::Lerp(kStartScale, 10.0f, ratio);

	pParticle->Initialize(
		worldKey,
		kAliveFrame,
		pos, speed, scale, color, 
		kExponent, pVP);
}
