#include "SceneExecutive.h"

using YScene::SceneExecutive;
using YScene::SceneManager;
using YScene::TransitionManager;

void SceneExecutive::Initialize(const std::string& sceneName, const std::string& transitionName)
{
	// シーンマネージャー
	sceneMan_ = SceneManager::GetInstance();
	sceneMan_->Initialize(sceneName);

	// シーン遷移マネージャー
	transitionMan_ = TransitionManager::GetInstance();
	transitionMan_->Initialize(transitionName);
}

void SceneExecutive::Update()
{
	// 遷移マネージャー更新
	transitionMan_->Update();

	// 幕開けの途中なら弾く
	if (transitionMan_->IsFalling()) { return; }

	// 遷移の瞬間なら
	if (transitionMan_->IsChangeMoment())
	{
		// シーン遷移
		sceneMan_->Change(nextSceneName_);
	}

	// シーンマネージャー更新
	sceneMan_->Update();
}

void SceneExecutive::Draw()
{
	// シーンマネージャー描画
	sceneMan_->Draw();

	// 遷移マネージャー描画
	transitionMan_->Draw();
}

void SceneExecutive::Change(
	const std::string& sceneName,
	const std::string& transitionName,
	const uint32_t changeFrame, const uint32_t loadFrame)
{
	// 遷移の途中なら弾く
	if (TransitionManager::GetInstance()->IsAct()) { return; }

	// 次シーン名代入
	nextSceneName_ = sceneName;

	// 次シーン遷移初期化
	transitionMan_->Initialize(transitionName);

	// 遷移開始
	transitionMan_->Activate(changeFrame, loadFrame);
}

void SceneExecutive::SetFactory(ISceneFactory* sceneFactory, ITransitionFactory* transitionFactory)
{
	// シーンファクトリー
	SceneManager::SetSceneFactory(sceneFactory);

	// シーン遷移ファクトリー
	TransitionManager::SetTransitionFactory(transitionFactory);
}

SceneExecutive* SceneExecutive::GetInstance()
{
	static SceneExecutive instance;
	return &instance;
}
