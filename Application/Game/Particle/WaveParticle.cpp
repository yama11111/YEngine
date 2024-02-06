#include "WaveParticle.h"
#include "BaseParticle.h"
#include "ParticleManager.h"
#include "DrawObjectForSprite3D.h"
#include "ConstBufferObject.h"
#include "CBColor.h"
#include "MathUtil.h"
#include <memory>

#include "WorldManager.h"

using YGame::WaveParticle;
using YGame::WorldManager;
using YMath::Vector3;

namespace
{
	YGame::Sprite3D* pSpr = nullptr;
	WorldManager* pWorldMan = WorldManager::GetInstance();
}

namespace YGame
{
	class impl_WaveParticle final :
		public WaveParticle,
		public BaseParticle
	{

	public:

		// 生成
		static impl_WaveParticle* Create();

		// 初期化
		void Initialize(
			const uint32_t aliveFrame,
			const YMath::Vector3& pos,
			const YMath::Vector3& rota,
			const float endScale,
			const YMath::Vector4& color,
			const float exponent,
			ViewProjection* pVP);

		// 更新
		void Update() override;

	private:

		DrawObjectForSprite3D* pObj_ = nullptr;

		// 色定数バッファ
		std::unique_ptr<ConstBufferObject<CBColor>> cbColor_;

		// スケールイージング
		YMath::Ease<float> scaleEas_;

		// アルファ値イージング
		YMath::Ease<float> alphaEas_;
	};

	impl_WaveParticle* impl_WaveParticle::Create()
	{
		impl_WaveParticle* newParticle = new impl_WaveParticle();

		DrawObjectForSprite3D* newObj = DrawObjectForSprite3D::Create({}, false, false, nullptr, pSpr, false);

		// オブジェクトのポインタを保持
		newParticle->pObj_ = newObj;
		newParticle->SetObject(newObj);

		newParticle->cbColor_.reset(ConstBufferObject<CBColor>::Create(false));

		return newParticle;
	}

	void impl_WaveParticle::Initialize(
		const uint32_t aliveFrame,
		const YMath::Vector3& pos,
		const YMath::Vector3& rota,
		const float endScale,
		const YMath::Vector4& color,
		const float exponent,
		ViewProjection* pVP)
	{
		BaseParticle::Initialize(aliveFrame, { pos, rota }, "Sprite3DDefault", 1);

		pObj_->InsertConstBuffer(cbColor_.get());
		pObj_->SetViewProjection(pVP);

		cbColor_->data_.baseColor = color;

		scaleEas_.Initialize(endScale / 2.0f, endScale, exponent);

		alphaEas_.Initialize(1.0f, 0.0f, exponent);
	}

	void impl_WaveParticle::Update()
	{
		if (isAlive_ == false) { return; }

		// タイマーの割合
		float ratio = aliveTimer_.Ratio();

		// だんだん大きく
		float scaleVal = scaleEas_.Out(ratio);
		obj_->transform_.scale_ = Vector3(scaleVal, scaleVal, scaleVal);

		// だんだん薄く
		cbColor_->data_.baseColor.w = alphaEas_.In(ratio);

		worldPos_ = initPos_ + localPos_;
		obj_->transform_.pos_ = worldPos_ - pWorldMan->CurrentMileage();
		obj_->Update();

		BaseParticle::UpdateLife();
	}
}

namespace
{
	const size_t kParticleNum = 100;
	const std::string kParticleTag = "WaveParticle";
	const float kExponent = 3.0f;

	bool isInit = false;
	std::array<std::unique_ptr<YGame::impl_WaveParticle>, kParticleNum> particles;
}

void WaveParticle::StaticInitialize()
{
	pSpr = Sprite3D::Create({ {"Texture0", Texture::Load("play/circle.png")} });

	if (isInit == false)
	{
		// 生成
		for (size_t i = 0; i < particles.size(); i++)
		{
			particles[i].reset(impl_WaveParticle::Create());
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

static YGame::impl_WaveParticle* DeadParticlePtr()
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

void WaveParticle::Emit(
	const uint32_t aliveFrame,
	const YMath::Vector3& pos,
	const YMath::Vector3& rota,
	const float endScale,
	const YMath::Vector4& color,
	ViewProjection* pVP)
{
	// 死んでいるパーティクルを初期化 (無いなら弾く)
	impl_WaveParticle* pParticle = DeadParticlePtr();
	if (pParticle == nullptr) { return; }

	pParticle->Initialize(aliveFrame, pos, rota, endScale, color, kExponent, pVP);
}
