#include "GameObjectCollisionManager.h"
#include <cassert>

using YGame::GameObjectCollisionManager;

void GameObjectCollisionManager::Initialize()
{
	Clear();
}

void GameObjectCollisionManager::Update()
{
	// �N�����Ȃ��Ȃ�e��
	if (pColliders_.empty()) { return; }
	
	// �S�R���C�_�[����`�F�b�N
	CheckAllCollision();
	
	// �S�R���C�_�[�N���A
	Clear();
}

void GameObjectCollisionManager::PushBack(GameObjectCollider* pCollider)
{
	// null�`�F�b�N
	assert(pCollider);
	
	// �}��
	pColliders_.push_back(pCollider);
}

void GameObjectCollisionManager::Clear()
{
	// ��Ȃ�e��
	if (pColliders_.empty()) { return; }

	// �R���C�_�[�S�폜
	pColliders_.clear();
}

void GameObjectCollisionManager::CheckAllCollision()
{
	// �R���C�_�[A�̎n�߂���
	std::list<GameObjectCollider*>::iterator itrA = pColliders_.begin();
	
	// �I���܂�
	for (; itrA != pColliders_.end(); ++itrA)
	{
		// �|�C���^���擾
		GameObjectCollider* colA = *itrA;

		// �R���C�_�[A�̏��� + 1���� (�R���C�_�[B)
		std::list<GameObjectCollider*>::iterator itrB = itrA;
		itrB++;

		// �I���܂�
		for (; itrB != pColliders_.end(); ++itrB)
		{
			// �|�C���^���擾
			GameObjectCollider* colB = *itrB;
			
			// ����`�F�b�N
			CheckCollisionPair(colA, colB);
		}
	}
}

void GameObjectCollisionManager::CheckCollisionPair(GameObjectCollider* pColliderA, GameObjectCollider* pColliderB)
{
	// �ǂ��炩���蔲����Ȃ�e��
	if (pColliderA->IsSlip() == true || pColliderB->IsSlip() == true) { return; }

	// �� �� �� �̔���
	if (YGame::CollisionSphereSphere(*pColliderA, *pColliderB))
	{
		// ���݂��ɏՓˎ�����
		pColliderA->OnCollision(pColliderB);
		pColliderB->OnCollision(pColliderA);
	}
}
