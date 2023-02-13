#pragma once
#include "Collider.h"
#include <list>

namespace YGame
{
	class CollisionManager
	{
	private:
		// �R���C�_�[�i�[���X�g
		std::list<Collider*> pColliders_;
	public:
		// ������
		void Initialize();
		// �X�V
		void Update();
	public:
		// �i�[
		void PushBack(Collider* pCollider);
		// ���X�g�N���A
		void Clear();
	private:
		// �S�R���C�_�[�m�F
		void CheckAllColliders();
	private:
		// �A�^������(��)
		static void CheckCollisionPair(Collider* pColliderA, Collider* pColliderB);
	};
}
