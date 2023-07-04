#pragma once
#include "IPet.h"

namespace YGame
{
	class Horse final:
		public IPet
	{

	public:

		/// <summary>
		/// ������
		/// </summary>
		/// <param name="status"> : �g�����X�t�H�[�����</param>
		void Initialize(const Transform::Status& status);

		/// <summary>
		/// �X�V
		/// </summary>
		void Update() override;

		/// <summary>
		/// �`��
		/// </summary>
		void Draw() override;

		/// <summary>
		/// �W�����v
		/// </summary>
		/// <param name="isJumpCount"> : �J�E���g���邩</param>
		void Jump(const bool isJumpCount = true) override;

		/// <summary>
		/// �U��
		/// </summary>
		void Attack() override;

	public:

		/// <summary>
		/// �Փˎ����擾
		/// </summary>
		/// <returns>�Փˎ����</returns>
		CollisionInfo GetCollisionInfo() override;

		/// <summary>
		/// ���ʒu�̍����擾
		/// </summary>
		/// <returns>���ʒu�̍���</returns>
		float RidingPosHeight() override;

	public:

		Horse() = default;

		~Horse() = default;

	protected:

		/// <summary>
		/// �Փˎ�����
		/// </summary>
		void Hit() override;
	};
}
