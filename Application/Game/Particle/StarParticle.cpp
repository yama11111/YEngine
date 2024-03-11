#include "StarParticle.h"
#include "BaseParticle.h"
#include "ParticleManager.h"
#include "DrawObjectForSprite3D.h"
#include "ConstBufferObject.h"
#include "CBColor.h"
#include "Speed.h"
#include "ColorConfig.h"
#include "MathUtil.h"
#include "MathVector.h"
#include "SplineEase.h"
#include "Def.h"
#include <memory>
#include <cmath>

using YGame::StarParticle;
using YMath::Vector3;
using YMath::Vector4;
namespace Color = YGame::ColorConfig;

namespace 
{
	YGame::Sprite3D* pSpr = nullptr;
}

namespace YGame
{
	class impl_StarParticle final :
		public StarParticle,
		public BaseParticle
	{

	public:

		// 生成
		static impl_StarParticle* Create();

		// 初期化
		void Initialize(
			const uint32_t aliveFrame,
			const Vector3& pos,
			const float exponent,
			ViewProjection* pVP);

		// 更新
		void Update() override;

	private:

		DrawObjectForSprite3D* pObj_ = nullptr;

		// 色定数バッファ
		std::unique_ptr<ConstBufferObject<CBColor>> cbColor_;
		
		// スケールイージング
		YMath::SplineEase<Vector3> scaleEas_;

		// スケールパワー
		YMath::Power scalePow_;
		bool scalePowSwitch_ = false;

		// 虹
		YMath::SplineEase<YMath::Vector4> rainbowEas_;
	};

	impl_StarParticle* impl_StarParticle::Create()
	{
		impl_StarParticle* newParticle = new impl_StarParticle();

		DrawObjectForSprite3D* newObj = DrawObjectForSprite3D::Create({}, true, true, nullptr, pSpr, false);

		// オブジェクトのポインタを保持
		newParticle->pObj_ = newObj;
		newParticle->SetObject(newObj);

		newParticle->cbColor_.reset(ConstBufferObject<CBColor>::Create(false));

		return newParticle;
	}

	void impl_StarParticle::Initialize(
		const uint32_t aliveFrame,
		const Vector3& pos,
		const float exponent,
		ViewProjection* pVP)
	{
		BaseParticle::Initialize(aliveFrame, { pos }, "Sprite3DBack", 1);
		
		pObj_->InsertConstBuffer(cbColor_.get());
		pObj_->SetViewProjection(pVP);

		scaleEas_.Initialize(
			{
				Vector3(3.0f, 1.5f, 0.0f),
				Vector3(0.3f, 0.3f, 0.0f),
				Vector3(1.5f, 3.0f, 0.0f),
			}, exponent);
		scalePow_.Initialize(8);
		scalePowSwitch_ = true;

		std::vector<YMath::Vector4> rainbow(std::begin(Color::skRainbow), std::end(Color::skRainbow));
		rainbowEas_.Initialize(rainbow, 1.0f);
	}

	void impl_StarParticle::Update()
	{
		if (isAlive_ == false) { return; }

		// タイマーの割合
		float aliveRatio = aliveTimer_.Ratio();
		cbColor_->data_.baseColor = rainbowEas_.In(aliveRatio);

		scalePow_.Update(scalePowSwitch_);
		if (scalePow_.IsZero()) { scalePowSwitch_ = true; }
		if (scalePow_.IsMax()) { scalePowSwitch_ = false; }
		float scaleRatio = scalePow_.Ratio();
		
		obj_->transform_.scale_ = scaleEas_.InOut(scaleRatio);
		obj_->Update();

		BaseParticle::UpdateLife();
	}
}

namespace
{
	// パーティクル静的に用意
	const size_t skParticleNum = 100;
	std::array<std::unique_ptr<YGame::impl_StarParticle>, skParticleNum> sParticles;
	const std::string skTag = "StarParticle";
	bool sIsInit = false;
}

void StarParticle::StaticInitialize()
{
	pSpr = Sprite3D::Create({ {"Texture0", Texture::Load("play/star.png")} });

	if (sIsInit == false)
	{
		// 生成
		for (size_t i = 0; i < sParticles.size(); i++)
		{
			sParticles[i].reset(impl_StarParticle::Create());
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

static YGame::impl_StarParticle* DeadParticlePtr()
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

void StarParticle::Emit(const Vector3& pos, ViewProjection* pVP)
{
	// 固有設定
	static const uint32_t kAliveFrame = 20;

	static const float kExponent = 3.0f;

	// 死んでいるパーティクルを初期化 (無いなら弾く)
	impl_StarParticle* pParticle = DeadParticlePtr();
	if (pParticle == nullptr) { return; }

	pParticle->Initialize(
		kAliveFrame,
		pos,
		kExponent, pVP);
}
