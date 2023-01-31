#include "SceneManager.h"
#include <cassert>

using YScene::SceneManager;

void SceneManager::Load()
{
	// ���݃V�[���ǂݍ���
	scene_->Load();
}

void SceneManager::Initialize()
{
	// ���݃V�[��������
	scene_->Initialize();
}

void SceneManager::Finalize()
{
	// ���݃V�[���I������
	scene_->Finalize();

	// ���V�[���폜
	if (nextScene_) { delete nextScene_; }

	// �V�[���t�@�N�g���[�폜
	sceneFactory_.reset();
}

void SceneManager::Update()
{
	// �V�[���؂�ւ�
	if (nextScene_)
	{
		if (scene_)
		{
			scene_->Finalize();
			scene_.reset();
		}

		scene_.reset(nextScene_);
		nextScene_ = nullptr;

		// �V�[��������
		scene_->Load();
		scene_->Initialize();
	}


	// ���݃V�[���X�V
	scene_->Update();
}

void SceneManager::Draw()
{
	// ���݃V�[���`��
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
