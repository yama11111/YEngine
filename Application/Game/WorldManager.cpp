#include "WorldManager.h"
#include "PipelineManager.h"
#include "GameObjectManager.h"
#include "ViewProjectionManager.h"
#include "Player.h"
#include <cassert>

using YGame::WorldManager;
using YGame::GameObjectManager;
using YGame::PipelineManager;
using YMath::Vector3;

namespace
{
	const std::vector<std::string> kKeyStrs = 
	{
		"Start", "World", "Fever", "Goal",
	};
}

WorldManager* WorldManager::GetInstance()
{
	static WorldManager instance;
	return &instance;
}

void WorldManager::Initialize(const WorldKey& key)
{
	SetWorldKey(key);

	for (size_t i = 0; i < kKeyNum; i++)
	{
		ViewProjectionManager::GetInstance()->Insert(
			kKeyStrs[i], &cameraSets_[static_cast<size_t>(currentWorldKey_)].transferVP);
	}
	
	Player::StaticInitialize(&cameraSets_[static_cast<size_t>(currentWorldKey_)].camera);
	GameObjectManager::GetInstance()->Initialize();

	for (size_t i = 0; i < cameraSets_.size(); i++)
	{
		cameraSets_[i].camera.Initialize();
		cameraSets_[i].transferVP.Initialize();
	}

	for (size_t i = 0; i < gatePoss_.size(); i++)
	{
		gatePoss_[i] = {};
	}

	for (size_t i = 0; i < postEffects_.size(); i++)
	{
		if (postEffects_[i].obj == nullptr)
		{
			postEffects_[i].pPE = PostEffect::Create({ "Texture0" });
			postEffects_[i].obj.reset(
				DrawObjectForPostEffect::Create(
					Transform::Status::Default(), 
					postEffects_[i].pPE));
		}
		if (postEffects_[i].cbDiscardColor == nullptr)
		{
			postEffects_[i].cbDiscardColor.reset(ConstBufferObject<CBDiscardColor>::Create());
			postEffects_[i].obj->InsertConstBuffer(postEffects_[i].cbDiscardColor.get());
		}
	}
}

void WorldManager::Update(const bool isControlUpdate)
{
	GameObjectManager::GetInstance()->Prepare(isControlUpdate);
	GameObjectManager::GetInstance()->Update(kKeyStrs);
	
	Player::StaticInitialize(&cameraSets_[static_cast<size_t>(currentWorldKey_)].camera);

	for (size_t i = 0; i < cameraSets_.size(); i++)
	{
		cameraSets_[i].camera.Update();
		cameraSets_[i].transferVP = cameraSets_[i].camera.GetViewProjection();
	}

	for (size_t i = 0; i < postEffects_.size(); i++)
	{
		postEffects_[i].obj->Update();
		postEffects_[i].isDraw = (static_cast<size_t>(currentWorldKey_) == i);
	}
}

void WorldManager::Draw()
{
	for (size_t i = 0; i < postEffects_.size(); i++)
	{
		if (postEffects_[i].isDraw == false) { continue; }
		
		GameObjectManager::GetInstance()->Draw({ kKeyStrs[i] });
		std::vector<PostEffect*> pes = { postEffects_[i].pPE };
		PipelineManager::GetInstance()->RenderToPostEffect(pes);
		
		postEffects_[i].obj->Draw("World", postEffects_[i].priority);
	}
}

void WorldManager::DrawDebug()
{
	GameObjectManager::GetInstance()->DrawDebugText();
	for (size_t i = 0; i < cameraSets_.size(); i++)
	{
		cameraSets_[i].camera.DrawDebugText();
	}
}

Vector3 WorldManager::Pass()
{
	if(currentWorldKey_ == WorldKey::eWorldKey)
	{
		currentWorldKey_ = WorldKey::eFeverKey;
	}
	else
	{
		currentWorldKey_ = WorldKey::eWorldKey;
	}

	return gatePoss_[static_cast<size_t>(currentWorldKey_)];
}

void WorldManager::SetWorldKey(const WorldKey& key)
{
	currentWorldKey_ = key;
}

void WorldManager::SetGatePos(const WorldKey& key, const Vector3& pos)
{
	gatePoss_[static_cast<size_t>(key)] = pos;
}

std::string WorldManager::WorldKeyStr(const WorldKey& key) const
{
	size_t index = static_cast<size_t>(key);

	return kKeyStrs[index];
}

WorldKey WorldManager::CurrentWorldKey() const
{
	return currentWorldKey_;
}

std::string WorldManager::CurrentWorldKeyStr() const
{
	return kKeyStrs[static_cast<size_t>(currentWorldKey_)];
}

