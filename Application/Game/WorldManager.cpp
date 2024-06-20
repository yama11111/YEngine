#include "WorldManager.h"
#include "PipelineManager.h"
#include "GameObjectManager.h"
#include "ViewProjectionManager.h"
#include "Player.h"
#include "SceneManager.h"
#include "ScoreManager.h"
#include "StageStatusManager.h"
#include <cassert>

#include "StarParticle.h"
#include "MathUtil.h"

using YGame::WorldManager;
using YGame::GameObjectManager;
using YGame::PipelineManager;
using YMath::Vector3;
using YMath::Matrix4;

namespace
{
	YGame::Sprite2D* pSpr = nullptr;

	const size_t kStarIdx = 4;
	const size_t kEmitFrame = 10;
	const float kDistance = 120.0f;
	const Vector3 kMinRange = { - 10.0f,-80.0f,-20.0f };
	const Vector3 kMaxRange = { +200.0f,+40.0f,+20.0f };
}

WorldManager* WorldManager::GetInstance()
{
	static WorldManager instance;
	return &instance;
}

void WorldManager::Initialize(const WorldKey& key)
{
	elderWorldKey_ = key;
	currentWorldKey_ = key;

	postEffects_.clear();
	basePosMatMap_.clear();

	std::vector<WorldKey> keys = WorldKeys();
	for (size_t i = 0; i < keys.size(); i++)
	{
		postEffects_.insert({ keys[i], PostEffectSet() });
		basePosMatMap_.insert({ keys[i], YMath::Matrix4::Identity() });
	}

	cameraSet_.camera.Initialize();
	cameraSet_.transferVP.Initialize();
	ViewProjectionManager::GetInstance()->Insert("Game", &cameraSet_.transferVP);
	Player::StaticInitialize(&cameraSet_.camera);

	for (auto itr = postEffects_.begin(); itr != postEffects_.end(); ++itr)
	{
		if (itr->second.obj == nullptr)
		{
			itr->second.pPE = PostEffect::Create({ "Texture0" });
			itr->second.obj.reset(
				DrawObjectForPostEffect::Create(Transform::Status::Default(), itr->second.pPE));
		}
		if (itr->second.cbDiscardColor == nullptr)
		{
			itr->second.cbDiscardColor.reset(ConstBufferObject<CBDiscardColor>::Create());
			itr->second.obj->InsertConstBuffer(itr->second.cbDiscardColor.get());
		}
	}
	
	Player::StaticInitialize(&cameraSet_.camera);
	GameObjectManager::GetInstance()->Initialize();

	for (size_t i = 0; i < gatePoss_.size(); i++)
	{
		gatePoss_[i] = {};
	}

	drawKeys_ = { WorldKey::eJourneyKey, WorldKey::eWorldKey };

	feverEmitTimer_.Initialize(kEmitFrame, true);
}

void WorldManager::Update(const bool isControlUpdate)
{
	GameObjectManager::GetInstance()->Prepare(isControlUpdate);
	GameObjectManager::GetInstance()->Update(WorldKeyStrs());

	UpdateFever();
	
	cameraSet_.camera.Update();
	cameraSet_.transferVP = cameraSet_.camera.GetViewProjection();

	for (auto itr = postEffects_.begin(); itr != postEffects_.end(); ++itr)
	{
		itr->second.obj->Update();
	}
}

void WorldManager::Draw()
{
	for (size_t i = 0; i < drawKeys_.size(); i++)
	{
		WorldKey key = drawKeys_[i];

		if (postEffects_[key].isDraw == false) { continue; }
		GameObjectManager::GetInstance()->Draw({ WorldKeyStr(key) });
		std::vector<PostEffect*> pes = { postEffects_[key].pPE };
		PipelineManager::GetInstance()->RenderToPostEffect(pes);

	}
	
	for (size_t i = 0; i < drawKeys_.size(); i++)
	{
		WorldKey key = drawKeys_[i];
		postEffects_[key].obj->Draw("World", postEffects_[key].priority);
	}
}

void WorldManager::DrawDebug()
{
	GameObjectManager::GetInstance()->DrawDebugText();
	
	cameraSet_.camera.DrawDebugText();
}

Vector3 WorldManager::Pass()
{
	if (currentWorldKey_ == WorldKey::eWorldKey)
	{
		SetWorldKey(WorldKey::eJourneyKey);
		drawKeys_ = { WorldKey::eWorldKey, WorldKey::eFeverKey, WorldKey::eJourneyKey };
	}
	else if (currentWorldKey_ == WorldKey::eFeverKey)
	{
		SetWorldKey(WorldKey::eJourneyKey);
		drawKeys_ = { WorldKey::eFeverKey, WorldKey::eWorldKey, WorldKey::eJourneyKey };
	}
	else if (currentWorldKey_ == WorldKey::eJourneyKey)
	{
		if (elderWorldKey_ == WorldKey::eWorldKey)
		{
			SetWorldKey(WorldKey::eFeverKey);
			drawKeys_ = { WorldKey::eJourneyKey, WorldKey::eFeverKey };
		}
		else if (elderWorldKey_ == WorldKey::eFeverKey)
		{
			SetWorldKey(WorldKey::eWorldKey);
			drawKeys_ = { WorldKey::eJourneyKey, WorldKey::eWorldKey };
		}
	}

	return gatePoss_[static_cast<size_t>(currentWorldKey_)];
}

void WorldManager::GameOver()
{
	if (SceneManager::GetInstance()->IsTransition()) { return; }
	
	SceneManager::GetInstance()->Transition("PLAY", "BLACKOUT");
}

void WorldManager::ClearStage()
{
	if (SceneManager::GetInstance()->IsTransition()) { return; }

	uint32_t score = ScoreManager::GetInstance()->ScoreInCurrentStage();
	StageStatusManager::GetInstance()->SetCurrentStageStatus(score);
	StageStatusManager::GetInstance()->Save();
	
	uint32_t stageIdx = StageStatusManager::GetInstance()->CurrentStageIndex();
	StageStatusManager::GetInstance()->SetStageIndex(stageIdx + 1);

	SceneManager::GetInstance()->Transition("SELECT", "WAVE");
}

void WorldManager::SetWorldKey(const WorldKey& key)
{
	elderWorldKey_ = currentWorldKey_;
	currentWorldKey_ = key;
}

void WorldManager::SetBaseMat(const WorldKey& key, const YMath::Matrix4& mat)
{
	basePosMatMap_[key] = mat;
}

void WorldManager::SetGatePos(const WorldKey& key, const Vector3& pos)
{
	gatePoss_[static_cast<size_t>(key)] = pos;
}

void WorldManager::SetGatePos(const std::string& key, const YMath::Vector3& pos)
{
	for (size_t i = 0; i < kWorldKeyNum; i++)
	{
		if (WorldKeyStr(i) == key)
		{
			gatePoss_[i] = pos;
			break;
		}
	}
}

YGame::WorldKey WorldManager::CurrentWorldKey() const
{
	return currentWorldKey_;
}

YMath::Matrix4 WorldManager::BasePosMat(const WorldKey& key)
{
	return basePosMatMap_[key];
}

YMath::Matrix4* WorldManager::BasePosMatPointer(const WorldKey& key)
{
	return &basePosMatMap_[key];
}

void WorldManager::UpdateFever()
{
	if (currentWorldKey_ != WorldKey::eFeverKey) { return; }
	
	feverEmitTimer_.Update();
	if (feverEmitTimer_.IsEnd() == false) { return; }

	feverEmitTimer_.Reset(true);
	Vector3 camPos = cameraSet_.camera.Pos();
	camPos.z += kDistance;

	for (size_t i = 0; i < kStarIdx; i++)
	{
		Vector3 pos = YMath::GetRand(camPos + kMinRange, camPos + kMaxRange, 100.0f);
		StarParticle::Emit(currentWorldKey_, pos, Vector3(-1.0f, -1.0f, 0.0f), &cameraSet_.transferVP);
	}
}

