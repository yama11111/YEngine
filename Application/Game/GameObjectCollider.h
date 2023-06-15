#pragma once
#include "CollisionPrimitive.h"

namespace YGame
{
	class GameObjectCollider :
		public Sphere
	{

	public:

		// ���
		enum class Type
		{
			eNone,	 // ����
			ePlayer, // �v���C���[
			eEnemy,	 // �G
			eCoin,	 // �R�C��
			eItem,	 // �A�C�e��
			eGoal,	 // �S�[��
			eEnd, // ���T�C�Y�p
		};

	public:

		/// <summary>
		/// �Փˎ��̔���
		/// </summary>
		/// <param name="pPair"> : �Փ˂�������̃|�C���^</param>
		virtual void OnCollision(const GameObjectCollider* pPair);

		/// <summary>
		/// ���蔲���t���O�擾
		/// </summary>
		/// <returns>���蔲���t���O</returns>
		bool IsSlip() const;
		
	protected:

		/// <summary>
		/// ������
		/// </summary>
		/// <param name="type"> : ���</param>
		/// <param name="pPos"> : �ʒu�|�C���^</param>
		/// <param name="radius"> : ���a</param>
		/// <param name="isSlip"> : ����ʂ��t���O</param>
		void Initialize(
			const Type type,
			YMath::Vector3* pPos,
			const float radius,
			const bool isSlip = false);

		/// <summary>
		/// �X�V
		/// </summary>
		void Update();

		/// <summary>
		/// ��ސݒ�
		/// </summary>
		/// <param name="type"> : ���</param>
		void SetType(const Type type);

		/// <summary>
		/// �ʒu�|�C���^�ݒ�
		/// </summary>
		/// <param name="pPos"> : �ʒu�|�C���^</param>
		void SetPosPointer(YMath::Vector3* pPos);

		/// <summary>
		/// ���蔲���t���O�ݒ�
		/// </summary>
		/// <param name="isSlip"> : ���蔲���t���O</param>
		void SetIsSlip(const bool isSlip);

	private:

		// ���
		Type type_ = Type::eNone;

		// �ʒu�|�C���^
		YMath::Vector3* pPos_ = nullptr;

		// ���蔲���邩
		bool isSlip_ = false;

	};
}
