#include "RecoveryParticle.h"
#include "BaseGameParticle.h"
#include "ParticleManager.h"

#include "DrawObjectForSprite3D.h"
#include "ConstBufferObject.h"
#include "CBColor.h"
#include "Speed.h"
#include "WorldManager.h"

#include "MathUtil.h"

#include <memory>

using YGame::RecoveryParticle;
using YMath::Vector3;
using YMath::Vector4;

namespace
{
	YGame::Sprite3D* pSpr = nullptr;
}

namespace YGame
{
	class impl_RecoveryParticle final :
		public RecoveryParticle,
		public BaseGameParticle
	{

	public:

		// 生成
		static impl_RecoveryParticle* Create();

		// 初期化
		void Initialize(
			const WorldKey worldKey,
			const uint32_t aliveFrame,
			const YMath::Vector3& pos,
			const float endScale,
			const Vector3& power,
			const Vector3& acceleration,
			const Vector3& maxSpeed,
			const YMath::Vector4& color,
			const float exponent,
			ViewProjection* pVP);

		// 更新
		void Update() override;

	private:

		DrawObjectForSprite3D* pObj_ = nullptr;

		// 色定数バッファ
		std::unique_ptr<ConstBufferObject<CBColor>> cbColor_;

		// スピード
		YMath::Speed speed_;

		// スケールイージング
		YMath::Ease<float> scaleEas_;

		// アルファ値イージング
		YMath::Ease<float> alphaEas_;


		// 進行力イージング
		YMath::Ease<YMath::Vector3> movePowerEas_;
	};

	impl_RecoveryParticle* impl_RecoveryParticle::Create()
	{
		impl_RecoveryParticle* newParticle = new impl_RecoveryParticle();

		DrawObjectForSprite3D* newObj = DrawObjectForSprite3D::Create({}, true, true, nullptr, pSpr, false);

		// オブジェクトのポインタを保持
		newParticle->pObj_ = newObj;
		newParticle->SetObject(newObj);

		newParticle->cbColor_.reset(ConstBufferObject<CBColor>::Create(false));

		return newParticle;
	}

	void impl_RecoveryParticle::Initialize(
		const WorldKey worldKey,
		const uint32_t aliveFrame,
		const YMath::Vector3& pos,
		const float endScale,
		const Vector3& power,
		const Vector3& acceleration,
		const Vector3& maxSpeed,
		const YMath::Vector4& color,
		const float exponent,
		ViewProjection* pVP)
	{
		BaseGameParticle::Initialize(worldKey, aliveFrame, { pos }, "Sprite3DDefault", 1);

		pObj_->InsertConstBuffer(cbColor_.get());
		pObj_->SetViewProjection(pVP);

		cbColor_->data_.baseColor = color;

		speed_.Initialize(maxSpeed, acceleration, false);
		
		scaleEas_.Initialize(endScale / 2.0f, endScale, exponent);

		alphaEas_.Initialize(1.0f, 0.0f, exponent);

		movePowerEas_.Initialize(power, {}, exponent);
	}

	void impl_RecoveryParticle::Update()
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

namespace
{
	// パーティクル静的に用意
	static const size_t skParticleNum = 100;
	static std::array<std::unique_ptr<YGame::impl_RecoveryParticle>, skParticleNum> sParticles;
	static const std::string skTag = "RecoveryParticle";
	static bool sIsInit = false;
}

void RecoveryParticle::StaticInitialize()
{
	pSpr = Sprite3D::Create({ {"Texture0", Texture::Load("play/recovery.png")} });

	if (sIsInit == false)
	{
		// 生成
		for (size_t i = 0; i < sParticles.size(); i++)
		{
			sParticles[i].reset(impl_RecoveryParticle::Create());
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

static YGame::impl_RecoveryParticle* DeadParticlePtr()
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

void RecoveryParticle::Emit(
	const WorldKey worldKey,
	const size_t num,
	const Vector3& pos,
	ViewProjection* pVP)
{
	// 固有設定
	static const uint32_t kAliveFrame = 60;

	static const float kScaleVal = 1.5f;

	static const YMath::Vector3 kMinAccelVal = { -0.1f, 0.1f, -0.1f };
	static const YMath::Vector3 kMaxAccelVal = { +0.1f, 0.2f, +0.1f };

	static const float kMaxSpeedVal = 0.5f;

	//static const float kEndAlpha = 0.6f;

	static const float kExponent = 6.0f;

	for (size_t i = 0; i < num; i++)
	{
		// 死んでいるパーティクルを初期化 (無いなら弾く)
		impl_RecoveryParticle* pParticle = DeadParticlePtr();
		if (pParticle == nullptr) { return; }

		Vector3 powerDirection =
			YMath::GetRand(Vector3(0.0f, 0.0f, 0.0f), Vector3(+1.0f, +1.0f, +1.0f), 100.0f);

		// ランダムな加速度で個々の動きを変化
		Vector3 accel = YMath::GetRand(kMinAccelVal, kMaxAccelVal, 100.0f);

		Vector3 maxSpeed = { kMaxSpeedVal, kMaxSpeedVal ,kMaxSpeedVal };

		pParticle->Initialize(
			worldKey, kAliveFrame, pos, kScaleVal, powerDirection, accel, maxSpeed, 
			{ 1.0f,1.0f,1.0f,1.0f }, kExponent, pVP);
	}
}
