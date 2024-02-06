#include "DamageParticle.h"
#include "BaseParticle.h"
#include "ParticleManager.h"
#include "UINumber.h"
#include "ConstBufferObject.h"
#include "CBColor.h"
#include "ColorConfig.h"
#include "MathUtil.h"
#include <memory>

#include "WorldManager.h"

using YGame::DamageParticle;
using YMath::Vector3;
using YGame::WorldManager;

namespace
{
	const size_t kMaxDigitNum = 4;
	const float kInterval = 0.75f;
	const float kScaleValue = 3.0f;
	
	const size_t kPopIdx = 0;
	const size_t kRemainIdx = 1;
	const size_t kVanishIdx = 2;
	
	WorldManager* pWorldMan = WorldManager::GetInstance();
}

namespace YGame
{
	class impl_DamageParticle final :
		public DamageParticle,
		public BaseParticle
	{

	public:

		// 生成
		static impl_DamageParticle* Create();

		// 初期化
		void Initialize(
			const uint32_t damageVal, 
			const YMath::Vector3& pos,
			ViewProjection* pVP);

		// 更新
		void Update() override;

		// 描画
		void Draw() override;

	private:

		// 数UI
		std::unique_ptr<UINumber> uiNum_;

		// 色定数バッファ
		std::unique_ptr<ConstBufferObject<CBColor>> cbColor_;

		// アニメーションタイマー
		std::array<YMath::Timer, 3> animeTims_;

		// 上昇イージング
		YMath::Ease<float> upEas_;

		// スケールイージング
		YMath::Ease<float> popScaEas_;

		// アルファ値イージング
		YMath::Ease<float> vanishAlphaEas_;
	};

	impl_DamageParticle* impl_DamageParticle::Create()
	{
		impl_DamageParticle* newParticle = new impl_DamageParticle();
		
		newParticle->uiNum_.reset(
			UINumber::Create3D(0, kMaxDigitNum, kInterval, false, true, nullptr, true, true, nullptr, false));

		newParticle->cbColor_.reset(ConstBufferObject<CBColor>::Create(false));

		return newParticle;
	}

	void impl_DamageParticle::Initialize(
		const uint32_t damageVal, 
		const YMath::Vector3& pos,
		ViewProjection* pVP)
	{
		BaseParticle::Initialize(0, {}, "", 0);
		
		uiNum_->InitializeTransform({ pos, {}, { kScaleValue, kScaleValue, kScaleValue } });
		uiNum_->InsertConstBuffer(cbColor_.get());
		uiNum_->SetViewProjection(pVP);
		
		uiNum_->SetNumber(damageVal);

		cbColor_->data_.baseColor = ColorConfig::skYellow;

		animeTims_[kPopIdx].Initialize(30, true);
		animeTims_[kRemainIdx].Initialize(30);
		animeTims_[kVanishIdx].Initialize(10);

		upEas_.Initialize(0.0f, 5.0f, 3.0f);
		popScaEas_.Initialize(-kScaleValue, 0.0f, 3.0f);
		vanishAlphaEas_.Initialize(1.0f, 0.0f, 2.0f);
	}

	void impl_DamageParticle::Update()
	{
		if (isAlive_ == false) { return; }

		for (size_t i = 0; i < animeTims_.size(); i++)
		{
			animeTims_[i].Update();
			
			// 終了したら
			if(animeTims_[i].IsEnd())
			{
				// 次のタイマーを始める
				if (i < animeTims_.size() - 1)
				{
					animeTims_[i + 1].SetActive(true);
				}
				// 最後なら終わる
				else
				{
					isAlive_ = false;
				}
			}
		}

		Transform::Status animeStatus;
		
		animeStatus.pos_ = -pWorldMan->CurrentMileage();
		animeStatus.pos_.y += upEas_.Out(animeTims_[kPopIdx].Ratio());

		float sca = popScaEas_.Out(animeTims_[kPopIdx].Ratio());
		animeStatus.scale_ += { sca, sca, sca };

		uiNum_->Update(animeStatus);

		cbColor_->data_.baseColor.w = vanishAlphaEas_.In(animeTims_[kVanishIdx].Ratio());
	}

	void impl_DamageParticle::Draw()
	{
		if (isAlive_ == false) { return; }

		uiNum_->Draw("Sprite3DDefault", 1);
	}
}

namespace
{
	const size_t kParticleNum = 100;
	const std::string kParticleTag = "DamageParticle";

	bool isInit = false;
	std::array<std::unique_ptr<YGame::impl_DamageParticle>, kParticleNum> particles;
}

void DamageParticle::StaticInitialize()
{
	if (isInit == false)
	{
		// 生成
		for (size_t i = 0; i < particles.size(); i++)
		{
			particles[i].reset(impl_DamageParticle::Create());
		}

		isInit = true;
	}

	// パーティクルマネージャーに挿入
	std::list<BaseParticle*> particlePtrs;

	for (size_t i = 0; i < particles.size(); i++)
	{
		particlePtrs.emplace_back(particles[i].get());
	}

	ParticleManager::GetInstance()->InsertParticles(kParticleTag, particlePtrs);
}

static YGame::impl_DamageParticle* DeadParticlePtr()
{
	// 死んでいるパーティクルを返す
	for (size_t i = 0; i < particles.size(); i++)
	{
		if (particles[i]->IsAlive() == false)
		{
			return particles[i].get();
		}
	}

	return nullptr;
}

void DamageParticle::Emit(
	const uint32_t damageVal,
	const YMath::Vector3& pos,
	ViewProjection* pVP)
{
	// 死んでいるパーティクルを初期化 (無いなら弾く)
	impl_DamageParticle* pParticle = DeadParticlePtr();
	if (pParticle == nullptr) { return; }

	pParticle->Initialize(damageVal, pos, pVP);
}
