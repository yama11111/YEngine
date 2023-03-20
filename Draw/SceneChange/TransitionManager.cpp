#include "TransitionManager.h"
#include "TransitionConfig.h"
#include "Blackout.h"
#include "InfectionBlocks.h"

using YGame::ITransition;
using YGame::TransitionManagaer;
using YGame::Blackout;
using YGame::InfectionBlocks;

void TransitionManagaer::Initialize()
{
	// �Ó]
	Blackout* newBO = new Blackout();
	newBO->Initialize(BlackoutFrame::Change, BlackoutFrame::Load);

	// �Z�H�u���b�N
	InfectionBlocks* newIB = new InfectionBlocks();
	newIB->Initialize(
		InfectionBlocksFrame::Change, InfectionBlocksFrame::Load,
		{ 0.0f,0.0f }, 64.0f, { 20.0f,10.0f });
	

	// ���T�C�Y
	tras_.resize(static_cast<size_t>(Type::End));

	// �C���f�b�N�X�ɍ��킹���ʒu�ɑ}��
	tras_[static_cast<size_t>(TransitionManagaer::Type::Blackout)].reset(newBO);
	tras_[static_cast<size_t>(TransitionManagaer::Type::InfectionBlocks)].reset(newIB);
}

void TransitionManagaer::Reset()
{
	for (size_t i = 0; i < tras_.size(); i++)
	{
		// ���Z�b�g
		tras_[i]->Reset();
	}
}

void TransitionManagaer::Update()
{
	for (size_t i = 0; i < tras_.size(); i++)
	{
		// �X�V
		tras_[i]->Update();
	}
}

void TransitionManagaer::Draw()
{
	for (size_t i = 0; i < tras_.size(); i++)
	{
		// �`��
		tras_[i]->Draw();
	}
}

void TransitionManagaer::Activate(const Type& type)
{
	// ���T�C�Y�p�g���Ă�����e��
	if (type == Type::End) { return; }

	// �C���f�b�N�X�擾 (�L���X�g)
	size_t idx = static_cast<size_t>(type);
	
	// ����J�n
	tras_[idx]->Activate();
}

bool TransitionManagaer::IsChangeMoment() const 
{
	// �߂�l�p
	bool result = false;

	// �g�����W�V�������Ƃ�
	for (size_t i = 0; i < tras_.size(); i++)
	{
		// �_�����Z (OR)
		result |= tras_[i]->IsChangeMoment();
	}

	return result;
}

bool TransitionManagaer::IsEnd() const
{
	// �߂�l�p
	bool result = false;

	// �g�����W�V�������Ƃ�
	for (size_t i = 0; i < tras_.size(); i++)
	{
		// �_�����Z (OR)
		result |= tras_[i]->IsEnd();
	}

	return result;
}

void TransitionManagaer::StaticInitialize()
{
	Blackout::StaticInitialize();
	InfectionBlocks::StaticInitialize();
}
