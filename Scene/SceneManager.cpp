#include "SceneManager.h"
#include "TransitionManager.h"
#include <cassert>

using YScene::SceneManager;
using YGame::TransitionManager;

void SceneManager::Initialize(const std::string& sceneName)
{
	// null�`�F�b�N
	assert(sceneFactory_);
	assert(transitionFactory_);

	// �V�[������
	scene_.reset(sceneFactory_->CreateScene(sceneName));
	// �V�[��null�`�F�b�N
	assert(sceneFactory_);

	// ���݃V�[���ǂݍ���
	scene_->Load();
	// ���݃V�[��������
	scene_->Initialize();

	// �I���t���O������
	isEnd_ = false;
}

void SceneManager::Finalize()
{
	// ���݃V�[���I������
	if (scene_) { scene_->Finalize(); }

	// ���V�[���폜
	if (nextScene_) { delete nextScene_; }

	// �V�[���t�@�N�g���[�폜
	sceneFactory_.reset();

	// �V�[���J�ڃt�@�N�g���[�폜
	transitionFactory_.reset();
}

void SceneManager::Update()
{
	// �J�ڂ̓r���Ȃ�e��
	if (TransitionManager::GetInstance()->IsPreChange()) { return; }

	// �J�ڂ̏u�ԂȂ�
	if (TransitionManager::GetInstance()->IsChangeMoment())
	{
		// ���V�[��������Ȃ�
		if (nextScene_)
		{
			// ���݃V�[��������Ȃ�
			if (scene_)
			{
				// ���݃V�[���I������
				scene_->Finalize();
				scene_.reset();
			}

			// �o�b�t�@�N���A
			pDescHeap_->ClearMutableCount();

			// ���̃V�[����}��
			scene_.reset(nextScene_);
			nextScene_ = nullptr;

			// �V�[��������
			scene_->Load();
			scene_->Initialize();
		}
	}

	// ���݃V�[���X�V
	scene_->Update();
}

void SceneManager::Draw()
{
	// ���݃V�[���`��
	scene_->Draw();
}

void SceneManager::Change(const std::string& sceneName, const std::string& transitionName)
{
	// ���V�[��������Ȃ�e��
	if (nextScene_) { return; }

	// null�`�F�b�N
	assert(sceneFactory_);
	assert(transitionFactory_);

	// ���V�[���쐬
	nextScene_ = sceneFactory_->CreateScene(sceneName);

	// �V�[���J�ڊJ�n
	transitionFactory_->ActivateTransition(transitionName);
}

void SceneManager::SetSceneFactory(ISceneFactory* sceneFactory)
{
	// null�`�F�b�N
	assert(sceneFactory);
	
	// ��p�V�[���t�@�N�g���[�ݒ�
	sceneFactory_.reset(sceneFactory);
}

void SceneManager::SetTransitionFactory(ITransitionFactory* transitionFactory)
{
	// null�`�F�b�N
	assert(transitionFactory);

	// ��p�J�ڃt�@�N�g���[�ݒ�
	transitionFactory_.reset(transitionFactory);
}

void SceneManager::SetDescriptorHeapPointer(YDX::DescriptorHeap* pDescHeap)
{
	// null�`�F�b�N
	assert(pDescHeap);

	// ���
	pDescHeap_ = pDescHeap;
}

SceneManager* SceneManager::GetInstance()
{
	static SceneManager instance;
	return &instance;
}
