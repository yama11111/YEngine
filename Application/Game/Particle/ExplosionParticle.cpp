#include "ExplosionParticle.h"
#include "BaseParticle.h"
#include "ParticleManager.h"

#include "DrawObjectForModel.h"
#include "ConstBufferObject.h"
#include "CBColor.h"
#include "MathUtil.h"

#include "WorldManager.h"
#include "Speed.h"
#include <memory>

using YGame::ExplosionParticle;
using YGame::WorldManager;
using YMath::Vector3;

namespace
{
	WorldManager* pWorldMan = WorldManager::GetInstance();
}

namespace YGame
{
	class impl_ExplosionParticle final :
		public ExplosionParticle,
		public BaseParticle
	{

	public:

		// 生成
		static impl_ExplosionParticle* Create();

		// 初期化
		void Initialize(
			const uint32_t aliveFrame,
			const YMath::Vector3& pos,
			const float endScale,
			const Vector3& power,
			const Vector3& acceleration,
			const Vector3& maxSpeed,
			const float endAlpha,
			const float exponent,
			ViewProjection* pVP);

		// 更新
		void Update() override;

	private:

		DrawObjectForModel* pObj_ = nullptr;

		// 色定数バッファ
		std::unique_ptr<ConstBufferObject<CBColor>> cbColor_;

		// スピード
		YMath::Speed speed_;

		// スケールイージング
		YMath::Ease<float> scaleEas_;

		// 進行力イージング
		YMath::Ease<YMath::Vector3> movePowerEas_;

		// アルファ値イージング
		YMath::Ease<float> alphaEas_;

	};

	impl_ExplosionParticle* impl_ExplosionParticle::Create()
	{
		impl_ExplosionParticle* newParticle = new impl_ExplosionParticle();

		DrawObjectForModel* newObj = DrawObjectForModel::Create({}, nullptr, nullptr, false);

		// オブジェクトのポインタを保持
		newParticle->pObj_ = newObj;
		newParticle->SetObject(newObj);

		newParticle->cbColor_.reset(ConstBufferObject<CBColor>::Create(false));

		return newParticle;
	}

	void impl_ExplosionParticle::Initialize(
		const uint32_t aliveFrame,
		const YMath::Vector3& pos,
		const float endScale,
		const Vector3& power,
		const Vector3& acceleration,
		const Vector3& maxSpeed,
		const float endAlpha,
		const float exponent,
		ViewProjection* pVP)
	{
		BaseParticle::Initialize(aliveFrame, { pos }, "ModelPhong", 1);

		obj_->transform_.parent_ = WorldManager::GetInstance()->BasePosMatPointer();
		pObj_->InsertConstBuffer(cbColor_.get());
		pObj_->SetViewProjection(pVP);

		scaleEas_.Initialize(endScale / 2.0f, endScale, exponent);

		speed_.Initialize(maxSpeed, acceleration, false);
		movePowerEas_.Initialize(power, {}, exponent);

		alphaEas_.Initialize(endAlpha, 0.0f, exponent);
	}

	void impl_ExplosionParticle::Update()
	{
		if (isAlive_ == false) { return; }

		// タイマーの割合
		float ratio = aliveTimer_.Ratio();

		// だんだん遅く
		speed_.Update(movePowerEas_.Out(ratio));
		localPos_ += speed_.Velocity();

		// だんだん大きく
		float scaleVal = scaleEas_.Out(ratio);
		obj_->transform_.scale_ = Vector3(scaleVal, scaleVal, scaleVal);

		// だんだん薄く
		cbColor_->data_.baseColor.w = alphaEas_.In(ratio);

		worldPos_ = initPos_ + localPos_;
		obj_->transform_.pos_ = worldPos_;
		obj_->Update();

		BaseParticle::UpdateLife();
	}
}

// パーティクル静的に用意
static const size_t skParticleNum = 100;
static std::array<std::unique_ptr<YGame::impl_ExplosionParticle>, skParticleNum> sParticles;
static const std::string skTag = "DustParticle";
static bool sIsInit = false;

void ExplosionParticle::StaticInitialize()
{
	if (sIsInit == false)
	{
		// 生成
		for (size_t i = 0; i < sParticles.size(); i++)
		{
			sParticles[i].reset(impl_ExplosionParticle::Create());
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

static YGame::impl_ExplosionParticle* DeadParticlePtr()
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

void ExplosionParticle::Emit(
	const size_t num,
	const Vector3& pos,
	const Vector3& powerDirection,
	ViewProjection* pVP)
{
	// 固有設定
	static const uint32_t kAliveFrame = 15;

	static const float kScaleVal = 0.25f;

	static const YMath::Vector3 kMinAccelVal = { 0.1f, 0.05f, 0.1f };
	static const YMath::Vector3 kMaxAccelVal = { 0.2f, 0.10f, 0.2f };

	static const float kMaxSpeedVal = 0.5f;

	static const float kEndAlpha = 0.6f;

	static const float kExponent = 3.0f;

	for (size_t i = 0; i < num; i++)
	{
		// 死んでいるパーティクルを初期化 (無いなら弾く)
		impl_ExplosionParticle* pParticle = DeadParticlePtr();
		if (pParticle == nullptr) { return; }

		// ランダムな加速度で個々の動きを変化
		Vector3 accel = YMath::GetRand(kMinAccelVal, kMaxAccelVal, 100.0f);

		Vector3 maxSpeed = { kMaxSpeedVal, kMaxSpeedVal , kMaxSpeedVal };

		pParticle->Initialize(kAliveFrame, pos, kScaleVal, powerDirection, accel, maxSpeed, kEndAlpha, kExponent, pVP);
	}
}
