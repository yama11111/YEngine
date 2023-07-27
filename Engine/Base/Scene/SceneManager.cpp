#include "SceneManager.h"
#include <cassert>

using YGame::SceneManager;
using YGame::ISceneFactory;

std::unique_ptr<ISceneFactory> SceneManager::sceneFactory_;

void SceneManager::Initialize(const std::string& sceneName)
{
	// nullチェック
	assert(sceneFactory_);

	// シーン生成
	scene_.reset(sceneFactory_->CreateScene(sceneName));
	// シーンnullチェック
	assert(scene_);

	// シーン名保存
	sceneName_ = sceneName;

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

	// シーンファクトリー削除
	sceneFactory_.reset();
}

void SceneManager::Update()
{
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
	assert(pDescHeap_);

	// 現在シーン終了処理
	scene_->Finalize();
	scene_.reset();

	// デスクリプタヒープをクリア
	pDescHeap_->ClearMutableCount();

	// 次のシーンを挿入
	scene_.reset(sceneFactory_->CreateScene(sceneName));
	// シーンnullチェック
	assert(scene_);

	// シーン名保存
	sceneName_ = sceneName;

	// シーン初期化
	scene_->Load();
	scene_->Initialize();
}

void SceneManager::SetSceneFactory(ISceneFactory* sceneFactory)
{
	// nullチェック
	assert(sceneFactory);
	
	// 専用シーンファクトリー設定
	sceneFactory_.reset(sceneFactory);
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
