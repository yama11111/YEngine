#include "DebriParticle.h"
#include "BaseParticle.h"
#include "ParticleManager.h"
#include "DrawObjectForModel.h"
#include "ConstBufferObject.h"
#include "CBColor.h"
#include "MathUtil.h"
#include "Speed.h"
#include <memory>

using YGame::DebriParticle;
using YMath::Vector3;
using YMath::Vector4;

namespace YGame
{
	class impl_DebriParticle final :
		public DebriParticle,
		public BaseParticle
	{

	public:

		// 生成
		static impl_DebriParticle* Create();

		// 初期化
		void Initialize(
			const uint32_t aliveFrame,
			const YMath::Vector3& pos,
			const float endScale,
			const Vector3& power,
			const Vector3& acceleration,
			const Vector3& maxSpeed,
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
	};

	impl_DebriParticle* impl_DebriParticle::Create()
	{
		impl_DebriParticle* newParticle = new impl_DebriParticle();

		DrawObjectForModel* newObj = DrawObjectForModel::Create({}, nullptr, nullptr, false);

		// オブジェクトのポインタを保持
		newParticle->pObj_ = newObj;
		newParticle->SetObject(newObj);

		newParticle->cbColor_.reset(ConstBufferObject<CBColor>::Create(false));

		return newParticle;
	}

	void impl_DebriParticle::Initialize(
		const uint32_t aliveFrame,
		const YMath::Vector3& pos,
		const float endScale,
		const Vector3& power,
		const Vector3& acceleration,
		const Vector3& maxSpeed,
		const float exponent,
		ViewProjection* pVP)
	{
		BaseParticle::Initialize(aliveFrame, { pos }, "ModelPhong", 1);

		cbColor_->data_.baseColor = Vector4(1.0f, 1.0f, 0.0f, 0.75f);
		pObj_->InsertConstBuffer(cbColor_.get());
		pObj_->SetViewProjection(pVP);

		scaleEas_.Initialize(endScale, endScale / 2.0f, exponent);

		speed_.Initialize(maxSpeed, acceleration, false);
		movePowerEas_.Initialize(power, {}, exponent);
	}

	void impl_DebriParticle::Update()
	{
		if (isAlive_ == false) { return; }

		// タイマーの割合
		float ratio = aliveTimer_.Ratio();

		// だんだん遅く
		speed_.Update(movePowerEas_.Out(ratio));
		obj_->transform_.pos_ += speed_.Velocity();

		// だんだん小さく
		float scaleVal = scaleEas_.In(ratio);
		obj_->transform_.scale_ = Vector3(scaleVal, scaleVal, scaleVal);


		obj_->Update();

		BaseParticle::UpdateLife();
	}
}

// パーティクル静的に用意
static const size_t skParticleNum = 100;
static std::array<std::unique_ptr<YGame::impl_DebriParticle>, skParticleNum> sParticles;
static const std::string skTag = "DebriParticle";
static bool sIsInit = false;

void DebriParticle::StaticInitialize()
{
	if (sIsInit == false)
	{
		// 生成
		for (size_t i = 0; i < sParticles.size(); i++)
		{
			sParticles[i].reset(impl_DebriParticle::Create());
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

static YGame::impl_DebriParticle* DeadParticlePtr()
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

void DebriParticle::Emit(
	const size_t num,
	const Vector3& pos,
	ViewProjection* pVP)
{
	// 固有設定
	static const uint32_t kAliveFrame = 35;

	static const float kScaleVal = 0.25f;

	static const YMath::Vector3 kMinAccelVal = { 0.1f, 0.05f, 0.1f };
	static const YMath::Vector3 kMaxAccelVal = { 0.2f, 0.10f, 0.2f };

	static const float kMaxSpeedVal = 0.5f;

	//static const float kEndAlpha = 0.6f;

	static const float kExponent = 6.0f;

	for (size_t i = 0; i < num; i++)
	{
		// 死んでいるパーティクルを初期化 (無いなら弾く)
		impl_DebriParticle* pParticle = DeadParticlePtr();
		if (pParticle == nullptr) { return; }

		Vector3 powerDirection = 
			YMath::GetRand(Vector3(-1.0f, -1.0f, -1.0f), Vector3(+1.0f, +1.0f, +1.0f), 100.0f);

		// ランダムな加速度で個々の動きを変化
		Vector3 accel = YMath::GetRand(kMinAccelVal, kMaxAccelVal, 100.0f);

		Vector3 maxSpeed = { kMaxSpeedVal, kMaxSpeedVal , kMaxSpeedVal };

		pParticle->Initialize(kAliveFrame, pos, kScaleVal, powerDirection, accel, maxSpeed, kExponent, pVP);
	}
}
