#pragma once
#include "GameObjectCollider.h"
#include <list>

namespace YGame
{
	class GameObjectCollisionManager
	{

	public:

		/// <summary>
		/// ������
		/// </summary>
		void Initialize();

		/// <summary>
		/// �X�V
		/// </summary>
		void Update();

	public:

		/// <summary>
		/// �i�[
		/// </summary>
		/// <param name="pCollider"> : �R���C�_�[�|�C���^</param>
		void PushBack(GameObjectCollider* pCollider);

		/// <summary>
		/// ���X�g�N���A
		/// </summary>
		void Clear();

	private:

		/// <summary>
		/// �S�R���W�����m�F
		/// </summary>
		void CheckAllCollision();

	private:

		/// <summary>
		/// �A�^������
		/// </summary>
		/// <param name="pColliderA"> : �R���C�_�[�|�C���^A</param>
		/// <param name="pColliderB"> : �R���C�_�[�|�C���^B</param>
		static void CheckCollisionPair(GameObjectCollider* pColliderA, GameObjectCollider* pColliderB);

	private:

		// �R���C�_�[�i�[���X�g
		std::list<GameObjectCollider*> pColliders_;

	};
}
