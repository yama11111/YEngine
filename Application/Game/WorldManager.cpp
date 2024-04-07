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

	cameraSets_.clear();
	postEffects_.clear();

	std::vector<WorldKey> keys = WorldKeys();
	for (size_t i = 0; i < keys.size(); i++)
	{
		cameraSets_.insert({ keys[i], CameraSet() });
		postEffects_.insert({ keys[i], PostEffectSet() });
	}

	for (auto itr = cameraSets_.begin(); itr != cameraSets_.end(); ++itr)
	{
		itr->second.camera.Initialize();
		itr->second.transferVP.Initialize();
		
		ViewProjectionManager::GetInstance()->
			Insert(WorldKeyStr(itr->first), &itr->second.transferVP);
	}

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
	
	Player::StaticInitialize(&cameraSets_[currentWorldKey_].camera);
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

	CameraSet& currentCam = cameraSets_[currentWorldKey_];
	
	Player::StaticInitialize(&currentCam.camera);
	UpdateFever();
	
	for (auto itr = cameraSets_.begin(); itr != cameraSets_.end(); ++itr)
	{
		itr->second.camera.Update();
		itr->second.transferVP = itr->second.camera.GetViewProjection();
	}

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
	for (auto itr = cameraSets_.begin(); itr != cameraSets_.end(); ++itr)
	{
		itr->second.camera.DrawDebugText();
	}
}

Vector3 WorldManager::Pass()
{
	if (currentWorldKey_ == WorldKey::eWorldKey)
	{
		SetWorldKey(WorldKey::eJourneyKey);
		drawKeys_ = { WorldKey::eFeverKey, WorldKey::eJourneyKey };
	}
	else if (currentWorldKey_ == WorldKey::eFeverKey)
	{
		SetWorldKey(WorldKey::eJourneyKey);
		drawKeys_ = { WorldKey::eWorldKey, WorldKey::eJourneyKey };
	}
	else if (currentWorldKey_ == WorldKey::eJourneyKey)
	{
		if (elderWorldKey_ == WorldKey::eWorldKey)
		{
			SetWorldKey(WorldKey::eFeverKey);
			drawKeys_ = { WorldKey::eWorldKey, WorldKey::eFeverKey };
		}
		else if (elderWorldKey_ == WorldKey::eFeverKey)
		{
			SetWorldKey(WorldKey::eWorldKey);
			drawKeys_ = { WorldKey::eFeverKey, WorldKey::eWorldKey };
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

void WorldManager::UpdateFever()
{
	if (currentWorldKey_ != WorldKey::eFeverKey) { return; }
	
	feverEmitTimer_.Update();
	if (feverEmitTimer_.IsEnd() == false) { return; }

	feverEmitTimer_.Reset(true);
	CameraSet& camSet = cameraSets_[WorldKey::eFeverKey];
	Vector3 camPos = camSet.camera.Pos();
	camPos.z += kDistance;

	for (size_t i = 0; i < kStarIdx; i++)
	{
		Vector3 pos = YMath::GetRand(camPos + kMinRange, camPos + kMaxRange, 100.0f);
		StarParticle::Emit(pos, Vector3(-1.0f, -1.0f, 0.0f), &camSet.transferVP);
	}
}

