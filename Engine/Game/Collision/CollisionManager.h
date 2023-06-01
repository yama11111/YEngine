#pragma once
#include "BaseCollider.h"
#include <list>

namespace YGame
{
	class CollisionManager
	{
	private:
		// �R���C�_�[�i�[���X�g
		std::list<BaseCollider*> pColliders_;
	public:
		// ������
		void Initialize();
		// �X�V
		void Update();
	public:
		// �i�[
		void PushBack(BaseCollider* pCollider);
		// ���X�g�N���A
		void Clear();
	private:
		// �S�R���W�����m�F
		void CheckAllCollision();
	private:
		// �A�^������(��)
		static void CheckCollisionPair(BaseCollider* pColliderA, BaseCollider* pColliderB);
	};
}
