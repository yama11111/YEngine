#include "CharacterManager.h"
#include "SphereCollider.h"
#include <cassert>

using YGame::CharacterManager;

void CharacterManager::Initialize()
{
	Clear();
}

void CharacterManager::Update()
{
	// �I�u�W�F�N�gnull�Ȃ�폜
	characters_.remove_if([](std::unique_ptr<ICharacter>& character) { return character->IsAlive(); });

	// �S�L�����N�^�[
	for (std::unique_ptr<ICharacter>& character : characters_)
	{
		// ����O�X�V
		character->Update();
	}

	// �A�^������S�`�F�b�N
	CheckAllCollision();
}

void CharacterManager::Draw()
{
	// �S�L�����N�^�[
	for (std::unique_ptr<ICharacter>& character : characters_)
	{
		// �`��
		character->Draw();
	}
}

void CharacterManager::Clear()
{
	// �I�u�W�F�N�g�S�폜
	if (characters_.empty() == false)
	{
		characters_.clear();
	}
}

void CharacterManager::PushBack(ICharacter* character)
{
	// null�`�F�b�N
	assert(character);

	// �V�K�L�����N�^�[
	std::unique_ptr<ICharacter> newCharacter;
	
	// �L�����N�^�[���Z�b�g
	newCharacter.reset(character);

	// �}��
	characters_.push_back(std::move(newCharacter));
}

void CharacterManager::CheckAllCollision()
{
	// A�̎n�߂���
	std::list<std::unique_ptr<ICharacter>>::iterator itrA = characters_.begin();

	// A�̏I���܂�
	for (; itrA != characters_.end(); ++itrA)
	{
		// �|�C���^���擾
		ICharacter* pCharaA = itrA->get();

		// B�̏���(A + 1)����
		std::list<std::unique_ptr<ICharacter>>::iterator itrB = itrA;
		itrB++;

		// B�̏I���܂�
		for (; itrB != characters_.end(); ++itrB)
		{
			// �|�C���^���擾
			ICharacter* pCharaB = itrB->get();

			// ����`�F�b�N
			CheckCollisionCharacterPair(pCharaA, pCharaB);
		}
	}
}

void CharacterManager::CheckCollisionCharacterPair(ICharacter* pCharacterA, ICharacter* pCharacterB)
{
	// �� �� �� �̔���
	if (CheckCollision(pCharacterA->ColliderPtr(), pCharacterB->ColliderPtr()))
	{
		// ���݂��ɏՓˎ�����
		//pCharacterA->OnCollision({});
		//pCharacterB->OnCollision({});
	}
}

bool CharacterManager::CheckCollision(BaseCollider* pColliderA, BaseCollider* pColliderB)
{
	// �R���C�_�[�������Ȃ�e��
	if (pColliderA == nullptr || pColliderB == nullptr)
	{
		return false;
	}

	// �ǂ��炩���蔲����Ȃ�e��
	if (pColliderA->IsSlip() || pColliderB->IsSlip()) 
	{
		return false; 
	}

	// �����ƃ}�X�N��v���Ȃ��Ȃ�e��
	if ((pColliderA->Attribute() & pColliderB->Mask()) == 0 ||
		(pColliderB->Attribute() & pColliderA->Mask()) == 0)
	{
		return false;
	}

	// �ǂ�������Ȃ�
	if (pColliderA->Shape() == BaseCollider::ShapeType::eSphere && 
		pColliderB->Shape() == BaseCollider::ShapeType::eSphere)
	{
		// �L���X�g
		SphereCollider* pSphereA = static_cast<SphereCollider*>(pColliderA);
		SphereCollider* pSphereB = static_cast<SphereCollider*>(pColliderB);

		// �� �� �� �̔���
		return YGame::CollisionSphereSphere(*pSphereA, *pSphereB);
	}

	return false;
}

