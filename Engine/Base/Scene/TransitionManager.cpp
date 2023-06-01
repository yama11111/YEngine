#include "TransitionManager.h"
#include <cassert>

#include "Blackout.h"
#include "InfectionBlocks.h"

using YScene::TransitionManager;
using YScene::ITransitionFactory;
using YGame::Texture;

std::unique_ptr<ITransitionFactory> TransitionManager::transitionFactory_;

void TransitionManager::StaticInitialize()
{
	Blackout::StaticInitialize();
	InfectionBlocks::StaticInitialize(Texture::Load("white1x1.png"));
}

void TransitionManager::Initialize(const std::string& transitionName)
{
	// nullチェック
	assert(transitionFactory_);

	// トランジション生成
	transition_.reset(transitionFactory_->CreateTransition(transitionName));
	// トランジションnullチェック
	assert(transition_);

	// トランジション名保存
	transitionName_ = transitionName;

	// トランジション初期化
	transition_->Initialize();
}

void TransitionManager::Finalize()
{
	// 現在シーン遷移終了処理
	if (transition_) { transition_->Finalize(); }

	// シーン遷移ファクトリー削除
	transitionFactory_.reset();
}

void TransitionManager::Reset()
{
	// リセット
	transition_->Reset();
}

void TransitionManager::Update()
{
	// シーン遷移更新
	transition_->Update();
}

void TransitionManager::Draw()
{
	// シーン遷移描画
	transition_->Draw();
}

void TransitionManager::Activate(const uint32_t changeFrame, const uint32_t loadFrame)
{
	// シーン遷移開始
	transition_->Activate(changeFrame, loadFrame);
}

void TransitionManager::SetTransitionFactory(ITransitionFactory* transitionFactory)
{
	// nullチェック
	assert(transitionFactory);

	// 専用遷移ファクトリー設定
	transitionFactory_.reset(transitionFactory);
}

void TransitionManager::SetTransition(const std::string& transitionName)
{
	// nullチェック
	assert(transitionFactory_);

	// シーン遷移生成
	transition_.reset(transitionFactory_->CreateTransition(transitionName));
	// トランジションnullチェック
	assert(transition_);

	// トランジション名保存
	transitionName_ = transitionName;

	// トランジション初期化
	transition_->Initialize();
}

bool TransitionManager::IsAct() const
{
	// 戻り値用
	bool result = false;

	// 代入
	result = transition_->IsAct();

	// 戻り値返す
	return result;
}

bool TransitionManager::IsRising() const
{
	// 戻り値用
	bool result = false;

	// 代入
	result = transition_->IsRising();

	// 戻り値返す
	return result;
}

bool TransitionManager::IsChangeMoment() const
{
	// 戻り値用
	bool result = false;

	// 代入
	result = transition_->IsChangeMoment();

	// 戻り値返す
	return result;
}

bool TransitionManager::IsFalling() const
{
	// 戻り値用
	bool result = false;

	// 代入
	result = transition_->IsFalling();

	// 戻り値返す
	return result;
}

bool TransitionManager::IsEnd() const
{

	// 戻り値用
	bool result = false;

	// 代入
	result = transition_->IsEnd();

	// 戻り値返す
	return result;
}

TransitionManager* TransitionManager::GetInstance()
{
	static TransitionManager instance;
	return &instance;
}
