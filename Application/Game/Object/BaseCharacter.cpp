#include "BaseCharacter.h"
#include "BaseCharacterDrawer.h"

#include "WorldManager.h"

#include "MathVector.h"
#include "MathUtil.h"

#include "FileUtil.h"
#include <fstream>
#include <sstream>
#include <cassert>
#include <imgui.h>

using YGame::BaseCharacter;
using YGame::WorldManager;
using YMath::Vector3;

namespace
{
	const YMath::Vector3 kMaxWorldSize = { 2000.0f, 150.0f, 150.0f };

	WorldManager* pWorldMan = WorldManager::GetInstance();
}

void BaseCharacter::Initialize(
	const std::string& name,
	const WorldKey worldKey,
	const Transform::Status& status)
{
	GameObject::Initialize(name, status);
	
	LoadStatus(name);

	SetWorldKey(worldKey);
}

void BaseCharacter::UpdateBeforeCollision()
{
	GameObject::UpdateBeforeCollision();
	
	speed_.Update(moveDirection_);

	moveDirection_ = Vector3();
}

void BaseCharacter::UpdateAfterCollision()
{
	// 位置更新
	UpdatePos();

	// 向き調整
	transform_->rota_ = YMath::AdjustAngle(direction_);

	GameObject::UpdateAfterCollision();
	
	status_.Update();

	OffScreenProcess();
}

YGame::ICollisionInfomation BaseCharacter::GetCollisionInfomation()
{
	ICollisionInfomation result;

	result.pTrfm = transform_.get();
	result.pWorldPos = &worldPos_;
	result.pMoveDirection = &moveDirection_;
	result.pStatus = &status_;

	return result;
}

Vector3 BaseCharacter::WorldPos() const
{
	return worldPos_;
}

void BaseCharacter::SetWorldKey(const WorldKey worldKey)
{
	worldKey_ = worldKey;

	transform_->parent_ = WorldManager::GetInstance()->BasePosMatPointer(worldKey);
	transform_->UpdateMatrix();

	std::string key = WorldKeyStr(worldKey);

	SetUpdateKey(key);
	SetDrawKeys({ key });

	if (drawer_)
	{
		static_cast<BaseCharacterDrawer*>(drawer_.get())->SetWorldKey(worldKey);
	}
}

void BaseCharacter::LoadStatus(const std::string& name)
{
	// 読み込むデータ
	Vector3 direction;
	Vector3 accel; Vector3 maxSpeed; 
	bool isGravity = false;
	uint32_t hp = 0; uint32_t attack = 0; uint32_t invincibleTime = 0;

	// ファイル読み込み
	std::ifstream file;
	file.open("Resources/CharaData/" + name + ".sts");
	assert(file);

	// 1行ずつ読み込み
	std::string line;
	while (std::getline(file, line))
	{
		std::istringstream lineStream(line);

		std::string key;
		std::getline(lineStream, key, ' ');

		if (key == "direction")
		{
			lineStream >> direction.x;
			lineStream >> direction.y;
			lineStream >> direction.z;
		}
		else if (key == "accel")
		{
			lineStream >> accel.x;
			lineStream >> accel.y;
			lineStream >> accel.z;
		}
		else if (key == "maxSpeed")
		{
			lineStream >> maxSpeed.x;
			lineStream >> maxSpeed.y;
			lineStream >> maxSpeed.z;
		}
		else if (key == "isGravity")
		{
			lineStream >> isGravity;
		}
		else if (key == "hp")
		{
			lineStream >> hp;
		}
		else if (key == "attack")
		{
			lineStream >> attack;
		}
		else if (key == "invincibleTime")
		{
			lineStream >> invincibleTime;
		}
	}

	// 初期化
	direction_ = direction;
	speed_.Initialize(accel, maxSpeed, isGravity);
	status_.Initialize(hp, attack, invincibleTime);
}

void BaseCharacter::UpdatePos()
{
	localPos_ += speed_.Velocity();

	worldPos_ = initPos_ + localPos_;

	transform_->pos_ = worldPos_;

	posMat_ = YMath::MatTranslation(worldPos_) * pWorldMan->BasePosMat(WorldKeyEnum(updateKey_));
}

void BaseCharacter::OffScreenProcess()
{
	// 画面外なら死ぬ
	if (YMath::InRange(transform_->pos_, -kMaxWorldSize, kMaxWorldSize) == false)
	{
		status_.Damage(1000, false);
	}
}

void BaseCharacter::DrawDebugTextContent()
{
	status_.DrawDebugTextContent();

	GameObject::DrawDebugTextContent();
}