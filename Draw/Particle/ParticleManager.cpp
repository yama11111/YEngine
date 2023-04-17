#include "ParticleManager.h"
#include "MathUtillity.h"
#include "YAssert.h"
#include "Def.h"

using YGame::ParticleManager;
using YGame::Model;
using YMath::Ease;
using YMath::Vector3;

void ParticleManager::StaticInitialize(YGame::ViewProjection* pVP)
{
	// 基底クラス
	IParticle::StaticInitialize(pVP);

	// ----- モデル設定 ----- //
	
	// 花火
	FireWork::StaticInitialize(Model::CreateCube());
}

void ParticleManager::Initialize()
{
	// パーティクル全削除
	if (particles_.empty() == false)
	{
		particles_.clear();
	}
}

void ParticleManager::Update()
{
	// パーティクル死んだら削除
	particles_.remove_if([](std::unique_ptr<IParticle>& particle) { return particle->isAlive_ == false; });

	// パーティクル毎更新
	for (std::unique_ptr<IParticle>& particle : particles_)
	{
		particle->Update();
	}
}

void ParticleManager::Draw()
{
	// パーティクル描画
	for (std::unique_ptr<IParticle>& particle : particles_)
	{
		particle->Draw();
	}
}

void YGame::ParticleManager::EmitFireWorks(
	const uint32_t frame, const size_t num, 
	const YMath::Vector3& pos, const float scale, 
	const YMath::Vector4& color)
{
	for (size_t i = 0; i < num; i++)
	{
		// パーティクル
		std::unique_ptr<FireWork> newParticle = std::make_unique<FireWork>();

		// ----- 位置 ----- //
		Ease<Vector3> posEas;

		// 終点
		Vector3 posEnd = pos;
		// 範囲
		float posRange = scale * 3.0f;
		
		// 設定
		posEnd.x_ += YMath::GetRand(-posRange, posRange, 100.0f);
		posEnd.y_ += YMath::GetRand(-posRange, posRange, 100.0f);
		posEnd.z_ += YMath::GetRand(-posRange, posRange, 100.0f);

		// 初期化
		posEas.Initialize(pos, posEnd, 3.0f);


		// ----- 回転 ----- //
		Ease<Vector3> rotaEas;
		
		// 終点
		Vector3 rotaEnd = {};
		// 範囲
		float rotaRange = PI * 2.0f;

		// 設定
		rotaEnd.x_ += YMath::GetRand(-rotaRange, rotaRange, 100.0f);
		rotaEnd.y_ += YMath::GetRand(-rotaRange, rotaRange, 100.0f);
		rotaEnd.z_ += YMath::GetRand(-rotaRange, rotaRange, 100.0f);

		// 初期化
		rotaEas.Initialize({}, rotaEnd, 3.0f);


		// 発生
		newParticle->Emit(frame, posEas, rotaEas, scale / 3.0f, color);
		// 挿入
		particles_.push_back(std::move(newParticle));
	}
}