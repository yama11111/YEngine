#include "SceneManager.h"
#include "TransitionManager.h"
#include <cassert>

using YScene::SceneManager;
using YGame::TransitionManager;

void SceneManager::Initialize(const std::string& sceneName)
{
	// nullチェック
	assert(sceneFactory_);
	assert(transitionFactory_);

	// シーン生成
	scene_.reset(sceneFactory_->CreateScene(sceneName));
	// シーンnullチェック
	assert(sceneFactory_);

	// 現在シーン読み込み
	scene_->Load();
	// 現在シーン初期化
	scene_->Initialize();

	// 終了フラグ初期化
	isEnd_ = false;
}

void SceneManager::Finalize()
{
	// 現在シーン終了処理
	if (scene_) { scene_->Finalize(); }

	// 次シーン削除
	if (nextScene_) { delete nextScene_; }

	// シーンファクトリー削除
	sceneFactory_.reset();

	// シーン遷移ファクトリー削除
	transitionFactory_.reset();
}

void SceneManager::Update()
{
	// 遷移の途中なら弾く
	if (TransitionManager::GetInstance()->IsPreChange()) { return; }

	// 遷移の瞬間なら
	if (TransitionManager::GetInstance()->IsChangeMoment())
	{
		// 次シーンがあるなら
		if (nextScene_)
		{
			// 現在シーンがあるなら
			if (scene_)
			{
				// 現在シーン終了処理
				scene_->Finalize();
				scene_.reset();
			}

			// バッファクリア
			pDescHeap_->ClearMutableCount();

			// 次のシーンを挿入
			scene_.reset(nextScene_);
			nextScene_ = nullptr;

			// シーン初期化
			scene_->Load();
			scene_->Initialize();
		}
	}

	// 現在シーン更新
	scene_->Update();
}

void SceneManager::Draw()
{
	// 現在シーン描画
	scene_->Draw();
}

void SceneManager::Change(const std::string& sceneName, const std::string& transitionName)
{
	// 次シーンがあるなら弾く
	if (nextScene_) { return; }

	// nullチェック
	assert(sceneFactory_);
	assert(transitionFactory_);

	// 次シーン作成
	nextScene_ = sceneFactory_->CreateScene(sceneName);

	// シーン遷移開始
	transitionFactory_->ActivateTransition(transitionName);
}

void SceneManager::SetSceneFactory(ISceneFactory* sceneFactory)
{
	// nullチェック
	assert(sceneFactory);
	
	// 専用シーンファクトリー設定
	sceneFactory_.reset(sceneFactory);
}

void SceneManager::SetTransitionFactory(ITransitionFactory* transitionFactory)
{
	// nullチェック
	assert(transitionFactory);

	// 専用遷移ファクトリー設定
	transitionFactory_.reset(transitionFactory);
}

void SceneManager::SetDescriptorHeapPointer(YDX::DescriptorHeap* pDescHeap)
{
	// nullチェック
	assert(pDescHeap);

	// 代入
	pDescHeap_ = pDescHeap;
}

SceneManager* SceneManager::GetInstance()
{
	static SceneManager instance;
	return &instance;
}
