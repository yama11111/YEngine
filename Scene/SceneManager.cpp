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
		// ���݃V�[��������Ȃ�
		if (scene_)
		{
			// ���݃V�[���I������
			scene_->Finalize();
			scene_.reset();
		}

		// ���̃V�[����}��
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
	// null�`�F�b�N
	assert(sceneFactory_);
	assert(nextScene_ == nullptr);

	// ���V�[���쐬
	nextScene_ = sceneFactory_->CreateScene(sceneName);
}

void SceneManager::SetSceneFactory(ISceneFactory* sceneFactory)
{
	// null�`�F�b�N
	assert(sceneFactory);
	
	// ��p�V�[���t�@�N�g���[�ݒ�
	sceneFactory_.reset(sceneFactory);
}

SceneManager* SceneManager::GetInstance()
{
	static SceneManager instance;
	return &instance;
}
