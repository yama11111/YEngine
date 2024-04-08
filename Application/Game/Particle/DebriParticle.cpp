#include "DebriParticle.h"
#include "BaseParticle.h"
#include "ParticleManager.h"

#include "DrawObjectForModel.h"
#include "ConstBufferObject.h"
#include "CBColor.h"

#include "Speed.h"
#include "WorldManager.h"
#include "ColorConfig.h"

#include "MathUtil.h"
#include "MathVector.h"
#include "SplineEase.h"
#include "Def.h"
#include <memory>
#include <cmath>

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
			const std::vector<Vector3>& pos,
			const float startScale, const float endScale,
			const Vector4& color,
			const float exponent,
			ViewProjection* pVP);

		// 更新
		void Update() override;

	private:

		DrawObjectForModel* pObj_ = nullptr;

		// 色定数バッファ
		std::unique_ptr<ConstBufferObject<CBColor>> cbColor_;

		// 位置イージング
		YMath::BezierEase<Vector3> posEas_;
		
		// スケールイージング
		YMath::Ease<float> scaleEas_;
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
		const std::vector<Vector3>& pos,
		const float startScale, const float endScale,
		const Vector4& color,
		const float exponent,
		ViewProjection* pVP)
	{
		BaseParticle::Initialize(aliveFrame, { pos[0] }, "ModelPhong", 1);

		obj_->transform_.parent_ = WorldManager::GetInstance()->BasePosMatPointer();
		cbColor_->data_.baseColor = color;
		pObj_->InsertConstBuffer(cbColor_.get());
		pObj_->SetViewProjection(pVP);

		posEas_.Initialize(pos, exponent);
		scaleEas_.Initialize(startScale, endScale, exponent);
	}

	void impl_DebriParticle::Update()
	{
		if (isAlive_ == false) { return; }

		// タイマーの割合
		float ratio = aliveTimer_.Ratio();

		// だんだん小さく
		float scaleVal = scaleEas_.In(ratio);
		obj_->transform_.scale_ = Vector3(scaleVal, scaleVal, scaleVal);

		obj_->transform_.pos_ = posEas_.Out(ratio);
		obj_->Update();

		BaseParticle::UpdateLife();
	}
}

namespace
{
	// パーティクル静的に用意
	const size_t skParticleNum = 100;
	std::array<std::unique_ptr<YGame::impl_DebriParticle>, skParticleNum> sParticles;
	const std::string skTag = "DebriParticle";
	bool sIsInit = false;
}

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

	static const float kDistance = 5.0f;
	
	static const float kStartScale = 0.25f;
	static const float kEndScale = 0.1f;

	static const float kExponent = 3.0f;

	static const Vector4 kColor = ColorConfig::skYellow;
	
	for (size_t i = 0; i < num; i++)
	{
		// 死んでいるパーティクルを初期化 (無いなら弾く)
		impl_DebriParticle* pParticle = DeadParticlePtr();
		if (pParticle == nullptr) { return; }
		
		float angle1 = (kPI * 2.0f) / num * i;
		Vector3 angleVec1 = Vector3(sinf(angle1), 0.0f, cosf(angle1));
		float angle2 = (kPI * 2.0f) / num * i + 1;
		Vector3 angleVec2 = Vector3(sinf(angle2), 0.0f, cosf(angle2));
		
		std::vector<Vector3> points =
		{
			pos,
			pos + Vector3(kDistance * angleVec1),
			pos + Vector3(kDistance * angleVec2),
		};


		pParticle->Initialize(
			kAliveFrame,
			points,
			kStartScale, kEndScale,
			kColor,
			kExponent, pVP);
	}
}
