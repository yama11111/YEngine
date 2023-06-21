#include "GameCharacterManager.h"
#include <cassert>

using YGame::GameCharacterManager;

void GameCharacterManager::Initialize()
{
	Clear();
}

void GameCharacterManager::Update()
{
	// �I�u�W�F�N�gnull�Ȃ�폜
	characters_.remove_if([](std::unique_ptr<IGameCharacter>& character) { return character->IsAlive(); });

	// �S�L�����N�^�[
	for (std::unique_ptr<IGameCharacter>& character : characters_)
	{
		// ����O�X�V
		character->Update();
	}

	// �A�^������S�`�F�b�N
	CheckAllCollision();
}

void GameCharacterManager::Draw()
{
	// �S�L�����N�^�[
	for (std::unique_ptr<IGameCharacter>& character : characters_)
	{
		// �`��
		character->Draw();
	}
}

void GameCharacterManager::Clear()
{
	// �I�u�W�F�N�g�S�폜
	if (characters_.empty() == false)
	{
		characters_.clear();
	}
}

void GameCharacterManager::PushBack(IGameCharacter* character)
{
	// null�`�F�b�N
	assert(character);

	// �V�K�L�����N�^�[
	std::unique_ptr<IGameCharacter> newCharacter;
	
	// �L�����N�^�[���Z�b�g
	newCharacter.reset(character);

	// �}��
	characters_.push_back(std::move(newCharacter));
}

void GameCharacterManager::CheckAllCollision()
{
	// A�̎n�߂���
	std::list<std::unique_ptr<IGameCharacter>>::iterator itrA = characters_.begin();

	// A�̏I���܂�
	for (; itrA != characters_.end(); ++itrA)
	{
		// �|�C���^���擾
		IGameCharacter* pCharaA = itrA->get();

		// B�̏���(A + 1)����
		std::list<std::unique_ptr<IGameCharacter>>::iterator itrB = itrA;
		itrB++;

		// B�̏I���܂�
		for (; itrB != characters_.end(); ++itrB)
		{
			// �|�C���^���擾
			IGameCharacter* pCharaB = itrB->get();

			// ����`�F�b�N
			CheckCollisionPair(pCharaA, pCharaB);
		}
	}
}

void GameCharacterManager::CheckCollisionPair(IGameCharacter* pCharacterA, IGameCharacter* pCharacterB)
{
	// �ǂ��炩���蔲����Ȃ�e��
	if (pCharacterA->IsSlip() || pCharacterB->IsSlip()) { return; }

	// �����ƃ}�X�N��v���Ȃ��Ȃ�e��
	if ((pCharacterA->Attribute() & pCharacterB->Mask()) == 0 || 
		(pCharacterB->Attribute() & pCharacterA->Mask()) == 0) 
	{
		return;
	}

	// �� �� �� �̔���
	if (YGame::CollisionSphereSphere(*pCharacterA, *pCharacterB))
	{
		// ���݂��ɏՓˎ�����
		pCharacterA->OnCollision(pCharacterB);
		pCharacterB->OnCollision(pCharacterA);
	}
}
