#include "TransitionManager.h"
#include <cassert>

#include "Blackout.h"
#include "InfectionBlocks.h"

using YScene::TransitionManager;
using YScene::ITransitionFactory;
using YGame::Texture;

std::unique_ptr<ITransitionFactory> TransitionManager::transitionFactory_;

void TransitionManager::StaticInitialize()
{
	Blackout::StaticInitialize();
	InfectionBlocks::StaticInitialize(Texture::Load("white1x1.png"));
}

void TransitionManager::Initialize(const std::string& transitionName)
{
	// null�`�F�b�N
	assert(transitionFactory_);

	// �g�����W�V��������
	transition_.reset(transitionFactory_->CreateTransition(transitionName));
	// �g�����W�V����null�`�F�b�N
	assert(transition_);

	// �g�����W�V�������ۑ�
	transitionName_ = transitionName;

	// �g�����W�V����������
	transition_->Initialize();
}

void TransitionManager::Finalize()
{
	// ���݃V�[���J�ڏI������
	if (transition_) { transition_->Finalize(); }

	// �V�[���J�ڃt�@�N�g���[�폜
	transitionFactory_.reset();
}

void TransitionManager::Reset()
{
	// ���Z�b�g
	transition_->Reset();
}

void TransitionManager::Update()
{
	// �V�[���J�ڍX�V
	transition_->Update();
}

void TransitionManager::Draw()
{
	// �V�[���J�ڕ`��
	transition_->Draw();
}

void TransitionManager::Activate(const uint32_t changeFrame, const uint32_t loadFrame)
{
	// �V�[���J�ڊJ�n
	transition_->Activate(changeFrame, loadFrame);
}

void TransitionManager::SetTransitionFactory(ITransitionFactory* transitionFactory)
{
	// null�`�F�b�N
	assert(transitionFactory);

	// ��p�J�ڃt�@�N�g���[�ݒ�
	transitionFactory_.reset(transitionFactory);
}

void TransitionManager::SetTransition(const std::string& transitionName)
{
	// null�`�F�b�N
	assert(transitionFactory_);

	// �V�[���J�ڐ���
	transition_.reset(transitionFactory_->CreateTransition(transitionName));
	// �g�����W�V����null�`�F�b�N
	assert(transition_);

	// �g�����W�V�������ۑ�
	transitionName_ = transitionName;

	// �g�����W�V����������
	transition_->Initialize();
}

bool TransitionManager::IsAct() const
{
	// �߂�l�p
	bool result = false;

	// ���
	result = transition_->IsAct();

	// �߂�l�Ԃ�
	return result;
}

bool TransitionManager::IsRising() const
{
	// �߂�l�p
	bool result = false;

	// ���
	result = transition_->IsRising();

	// �߂�l�Ԃ�
	return result;
}

bool TransitionManager::IsChangeMoment() const
{
	// �߂�l�p
	bool result = false;

	// ���
	result = transition_->IsChangeMoment();

	// �߂�l�Ԃ�
	return result;
}

bool TransitionManager::IsFalling() const
{
	// �߂�l�p
	bool result = false;

	// ���
	result = transition_->IsFalling();

	// �߂�l�Ԃ�
	return result;
}

bool TransitionManager::IsEnd() const
{

	// �߂�l�p
	bool result = false;

	// ���
	result = transition_->IsEnd();

	// �߂�l�Ԃ�
	return result;
}

TransitionManager* TransitionManager::GetInstance()
{
	static TransitionManager instance;
	return &instance;
}
