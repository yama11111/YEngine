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
		if (scene_)
		{
			scene_->Finalize();
			scene_.reset();
		}

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
	assert(sceneFactory_);
	assert(nextScene_ == nullptr);

	nextScene_ = sceneFactory_->CreateScene(sceneName);
}

void SceneManager::SetSceneFactory(ISceneFactory* sceneFactory)
{
	assert(sceneFactory);
	sceneFactory_.reset(sceneFactory);
}

SceneManager* SceneManager::GetInstance()
{
	static SceneManager instance;
	return &instance;
}
