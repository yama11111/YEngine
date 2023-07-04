#pragma once
#include "IAttack.h"

namespace YGame
{
	class SlashAttack final:
		public IAttack
	{

	public:

		/// <summary>
		/// ������
		/// </summary>
		/// <param name="aliveTimer"> : ��������</param>
		/// <param name="pAttackerPos"> : �U���҂̈ʒu�|�C���^</param>
		/// <param name="offset"> : �I�t�Z�b�g</param>
		/// <param name="radius"> : ���a</param>
		/// <param name="attackPower"> : �U����</param>
		void Initialize(
			const uint32_t aliveTimer, 
			YMath::Vector3* pAttackerPos,
			const YMath::Vector3& offset,
			const float radius,
			const uint32_t attackPower);

		/// <summary>
		/// �X�V
		/// </summary>
		void Update() override;

		/// <summary>
		/// �Փ˔���
		/// </summary>
		/// <param name="info"> : �Փˎ����</param>
		void OnCollision(const CollisionInfo& info) override;

		/// <summary>
		/// �Փˎ����擾
		/// </summary>
		/// <returns>�Փˎ����</returns>
		CollisionInfo GetCollisionInfo() override;

	public:

		SlashAttack() = default;

		~SlashAttack() = default;
	
	private:

		// �e�|�C���^
		YMath::Vector3* pAttackerPos_ = nullptr;
		
		// �I�t�Z�b�g
		YMath::Vector3 offset_;

		// �����^�C�}�[
		YMath::Timer aliveTimer_;
	
	private:

		/// <summary>
		/// �ʒu�X�V
		/// </summary>
		void UpdatePos();

		/// <summary>
		/// �f�o�b�O�e�L�X�g�{��
		/// </summary>
		void DrawDebugTextContent() override;

	};
}