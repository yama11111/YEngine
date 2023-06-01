#include "SceneExecutive.h"

using YScene::SceneExecutive;
using YScene::SceneManager;
using YScene::TransitionManager;

void SceneExecutive::Initialize(const std::string& sceneName, const std::string& transitionName)
{
	// �V�[���}�l�[�W���[
	sceneMan_ = SceneManager::GetInstance();
	sceneMan_->Initialize(sceneName);

	// �V�[���J�ڃ}�l�[�W���[
	transitionMan_ = TransitionManager::GetInstance();
	transitionMan_->Initialize(transitionName);
}

void SceneExecutive::Update()
{
	// �J�ڃ}�l�[�W���[�X�V
	transitionMan_->Update();

	// ���J���̓r���Ȃ�e��
	if (transitionMan_->IsFalling()) { return; }

	// �J�ڂ̏u�ԂȂ�
	if (transitionMan_->IsChangeMoment())
	{
		// �V�[���J��
		sceneMan_->Change(nextSceneName_);
	}

	// �V�[���}�l�[�W���[�X�V
	sceneMan_->Update();
}

void SceneExecutive::Draw()
{
	// �V�[���}�l�[�W���[�`��
	sceneMan_->Draw();

	// �J�ڃ}�l�[�W���[�`��
	transitionMan_->Draw();
}

void SceneExecutive::Change(
	const std::string& sceneName,
	const std::string& transitionName,
	const uint32_t changeFrame, const uint32_t loadFrame)
{
	// �J�ڂ̓r���Ȃ�e��
	if (TransitionManager::GetInstance()->IsAct()) { return; }

	// ���V�[�������
	nextSceneName_ = sceneName;

	// ���V�[���J�ڏ�����
	transitionMan_->Initialize(transitionName);

	// �J�ڊJ�n
	transitionMan_->Activate(changeFrame, loadFrame);
}

void SceneExecutive::SetFactory(ISceneFactory* sceneFactory, ITransitionFactory* transitionFactory)
{
	// �V�[���t�@�N�g���[
	SceneManager::SetSceneFactory(sceneFactory);

	// �V�[���J�ڃt�@�N�g���[
	TransitionManager::SetTransitionFactory(transitionFactory);
}

SceneExecutive* SceneExecutive::GetInstance()
{
	static SceneExecutive instance;
	return &instance;
}
