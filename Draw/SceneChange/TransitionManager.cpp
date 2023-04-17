#include "TransitionManager.h"
#include "TransitionConfig.h"
#include "Blackout.h"
#include "InfectionBlocks.h"

using YGame::ITransition;
using YGame::TransitionManager;
using YGame::Blackout;
using YGame::InfectionBlocks;

void TransitionManager::Initialize()
{
	// 暗転
	Blackout* newBO = new Blackout();
	newBO->Initialize(BlackoutFrame::Change, BlackoutFrame::Load);

	// 浸食ブロック
	InfectionBlocks* newIB = new InfectionBlocks();
	newIB->Initialize(
		InfectionBlocksFrame::Change, InfectionBlocksFrame::Load,
		{ 0.0f,0.0f }, 128.0f, { 15.0f,8.0f },
		{ 0.0f,1.0f });
	

	// リサイズ
	tras_.resize(static_cast<size_t>(Type::End));

	// インデックスに合わせた位置に挿入
	tras_[static_cast<size_t>(TransitionManager::Type::Blackout)].reset(newBO);
	tras_[static_cast<size_t>(TransitionManager::Type::InfectionBlocks)].reset(newIB);
}

void TransitionManager::Reset()
{
	for (size_t i = 0; i < tras_.size(); i++)
	{
		// リセット
		tras_[i]->Reset();
	}
}

void TransitionManager::Update()
{
	for (size_t i = 0; i < tras_.size(); i++)
	{
		// 更新
		tras_[i]->Update();
	}
}

void TransitionManager::Draw()
{
	for (size_t i = 0; i < tras_.size(); i++)
	{
		// 描画
		tras_[i]->Draw();
	}
}

void TransitionManager::Activate(const Type& type)
{
	// リサイズ用使っていたら弾く
	if (type == Type::End) { return; }

	// インデックス取得 (キャスト)
	size_t idx = static_cast<size_t>(type);
	
	// 動作開始
	tras_[idx]->Activate();
}

bool TransitionManager::IsPreChange() const
{
	// 戻り値用
	bool result = false;

	// トランジションごとに
	for (size_t i = 0; i < tras_.size(); i++)
	{
		// 論理演算 (OR)
		result |= tras_[i]->IsPreChange();
	}

	return result;
}

bool TransitionManager::IsChangeMoment() const
{
	// 戻り値用
	bool result = false;

	// トランジションごとに
	for (size_t i = 0; i < tras_.size(); i++)
	{
		// 論理演算 (OR)
		result |= tras_[i]->IsChangeMoment();
	}

	return result;
}

bool TransitionManager::IsEnd() const
{
	// 戻り値用
	bool result = false;

	// トランジションごとに
	for (size_t i = 0; i < tras_.size(); i++)
	{
		// 論理演算 (OR)
		result |= tras_[i]->IsEnd();
	}

	return result;
}

void TransitionManager::StaticInitialize()
{
	Blackout::StaticInitialize();
	InfectionBlocks::StaticInitialize();
}

TransitionManager* TransitionManager::GetInstance()
{
	static TransitionManager instance;
	return &instance;
}
