#include "SceneManager.h"
#include <cassert>

using YScene::SceneManager;

void SceneManager::Load()
{
	// 現在シーン読み込み
	scene_->Load();
}

void SceneManager::Initialize()
{
	// 現在シーン初期化
	scene_->Initialize();
}

void SceneManager::Finalize()
{
	// 現在シーン終了処理
	scene_->Finalize();

	// 次シーン削除
	if (nextScene_) { delete nextScene_; }

	// シーンファクトリー削除
	sceneFactory_.reset();
}

void SceneManager::Update()
{
	// シーン切り替え
	if (nextScene_)
	{
		// 現在シーンがあるなら
		if (scene_)
		{
			// 現在シーン終了処理
			scene_->Finalize();
			scene_.reset();
		}

		// 次のシーンを挿入
		scene_.reset(nextScene_);
		nextScene_ = nullptr;

		// シーン初期化
		scene_->Load();
		scene_->Initialize();
	}

	// 現在シーン更新
	scene_->Update();
}

void SceneManager::Draw()
{
	// 現在シーン描画
	scene_->Draw();
}

void SceneManager::Change(const std::string& sceneName)
{
	// nullチェック
	assert(sceneFactory_);
	assert(nextScene_ == nullptr);

	// 次シーン作成
	nextScene_ = sceneFactory_->CreateScene(sceneName);
}

void SceneManager::SetSceneFactory(ISceneFactory* sceneFactory)
{
	// nullチェック
	assert(sceneFactory);
	
	// 専用シーンファクトリー設定
	sceneFactory_.reset(sceneFactory);
}

SceneManager* SceneManager::GetInstance()
{
	static SceneManager instance;
	return &instance;
}
