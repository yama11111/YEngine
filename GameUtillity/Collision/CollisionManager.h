#pragma once
#include "Collider.h"
#include <memory>
#include <list>

namespace Collision
{
	class CollisionManager
	{
	private:
		// �R���C�_�[�i�[���X�g
		std::list<Collider*> colliders_;
	public:
		// ������
		void Initialize();
		// �X�V
		void Update();
	public:
		// �i�[
		void PushBack(Collider* collider);
		// ���X�g�N���A
		void Clear();
	private:
		// �S�R���C�_�[�m�F
		void CheckAllColliders();
	private:
		// �A�^������(��)
		static void CheckCollisionPair(Collider* colliderA, Collider* colliderB);
	};
}
