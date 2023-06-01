#include "SceneManager.h"
#include <cassert>

using YScene::SceneManager;
using YScene::ISceneFactory;

std::unique_ptr<ISceneFactory> SceneManager::sceneFactory_;

void SceneManager::Initialize(const std::string& sceneName)
{
	// null�`�F�b�N
	assert(sceneFactory_);

	// �V�[������
	scene_.reset(sceneFactory_->CreateScene(sceneName));
	// �V�[��null�`�F�b�N
	assert(scene_);

	// �V�[�����ۑ�
	sceneName_ = sceneName;

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

	// �V�[���t�@�N�g���[�폜
	sceneFactory_.reset();
}

void SceneManager::Update()
{
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
	assert(pDescHeap_);

	// ���݃V�[���I������
	scene_->Finalize();
	scene_.reset();

	// �f�X�N���v�^�q�[�v���N���A
	pDescHeap_->ClearMutableCount();

	// ���̃V�[����}��
	scene_.reset(sceneFactory_->CreateScene(sceneName));
	// �V�[��null�`�F�b�N
	assert(scene_);

	// �V�[�����ۑ�
	sceneName_ = sceneName;

	// �V�[��������
	scene_->Load();
	scene_->Initialize();
}

void SceneManager::SetSceneFactory(ISceneFactory* sceneFactory)
{
	// null�`�F�b�N
	assert(sceneFactory);
	
	// ��p�V�[���t�@�N�g���[�ݒ�
	sceneFactory_.reset(sceneFactory);
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
