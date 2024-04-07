#include "AfterimageParticle.h"
#include "BaseParticle.h"
#include "ParticleManager.h"

#include "DrawObjectForModel.h"
#include "ConstBufferObject.h"
#include "CBColor.h"

#include "ColorConfig.h"

#include "Speed.h"
#include "MathUtil.h"
#include "MathVector.h"
#include "SplineEase.h"

#include "Def.h"
#include <memory>
#include <cmath>

using YGame::AfterimageParticle;
using YMath::Vector3;
using YMath::Vector4;

namespace YGame
{
	class impl_AfterimageParticle final :
		public AfterimageParticle,
		public BaseParticle
	{

	public:

		// 生成
		static impl_AfterimageParticle* Create();

		// 初期化
		void Initialize(
			const uint32_t aliveFrame,
			const Transform& trfm,
			const float startScale, const float endScale,
			const Vector4& color,
			const float exponent,
			Model* pModel,
			ViewProjection* pVP);

		// 更新
		void Update() override;

	private:

		DrawObjectForModel* pObj_ = nullptr;

		// 色定数バッファ
		std::unique_ptr<ConstBufferObject<CBColor>> cbColor_;

		Vector3 scale_;

		// スケールイージング
		YMath::Ease<float> scaleEas_;
		
		// アルファ値イージング
		YMath::Ease<float> alphaEas_;
	};

	impl_AfterimageParticle* impl_AfterimageParticle::Create()
	{
		impl_AfterimageParticle* newParticle = new impl_AfterimageParticle();

		DrawObjectForModel* newObj = DrawObjectForModel::Create({}, nullptr, nullptr, false);

		// オブジェクトのポインタを保持
		newParticle->pObj_ = newObj;
		newParticle->SetObject(newObj);

		newParticle->cbColor_.reset(ConstBufferObject<CBColor>::Create(false));

		return newParticle;
	}

	void impl_AfterimageParticle::Initialize(
		const uint32_t aliveFrame,
		const Transform& trfm,
		const float startScale, const float endScale,
		const Vector4& color,
		const float exponent,
		Model* pModel,
		ViewProjection* pVP)
	{
		BaseParticle::Initialize(aliveFrame, { trfm.pos_, trfm.rota_, trfm.scale_ }, "ModelSingleColor", 1);

		scale_ = trfm.scale_;

		cbColor_->data_.baseColor = color;
		pObj_->InsertConstBuffer(cbColor_.get());
		pObj_->SetViewProjection(pVP);
		pObj_->SetGraphic(pModel);

		scaleEas_.Initialize(startScale, endScale, exponent);
		alphaEas_.Initialize(1.0f, 0.0f, exponent);
	}

	void impl_AfterimageParticle::Update()
	{
		if (isAlive_ == false) { return; }

		// タイマーの割合
		float ratio = aliveTimer_.Ratio();

		// だんだん小さく
		//float scaleVal = scaleEas_.In(ratio);
		//obj_->transform_.scale_ = scale_ * scaleVal;
		
		obj_->Update();

		cbColor_->data_.baseColor.w = alphaEas_.Out(ratio);

		BaseParticle::UpdateLife();
	}
}

namespace
{
	// パーティクル静的に用意
	const size_t skParticleNum = 100;
	std::array<std::unique_ptr<YGame::impl_AfterimageParticle>, skParticleNum> sParticles;
	const std::string skTag = "AfterimageParticle";
	bool sIsInit = false;
}

void AfterimageParticle::StaticInitialize()
{
	if (sIsInit == false)
	{
		// 生成
		for (size_t i = 0; i < sParticles.size(); i++)
		{
			sParticles[i].reset(impl_AfterimageParticle::Create());
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

static YGame::impl_AfterimageParticle* DeadParticlePtr()
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

void AfterimageParticle::Emit(
	const Transform& trfm,
	const Vector4& color,
	Model* pModel,
	ViewProjection* pVP)
{
	// 固有設定
	static const uint32_t kAliveFrame = 35;

	static const float kDistance = 5.0f;

	static const float kStartScale = 1.0f;
	static const float kEndScale = 0.1f;

	static const float kExponent = 3.0f;

	// 死んでいるパーティクルを初期化 (無いなら弾く)
	impl_AfterimageParticle* pParticle = DeadParticlePtr();
	if (pParticle == nullptr) { return; }


	pParticle->Initialize(
		kAliveFrame,
		trfm,
		kStartScale, kEndScale,
		color,
		kExponent, 
		pModel, 
		pVP);
}
