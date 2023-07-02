#pragma once
#include "IAttack.h"

namespace YGame
{
	class SnortAttack final :
		public IAttack
	{

	public:

		/// <summary>
		/// ������
		/// </summary>
		/// <param name="status"> : �g�����X�t�H�[�����</param>
		/// <param name="aliveTimer"> : ��������</param>
		/// <param name="attackPower"> : �U����</param>
		void Initialize(const Transform::Status& status, const uint32_t aliveTimer, const uint32_t attackPower);

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

		SnortAttack() = default;

		~SnortAttack() = default;

	private:

		/// <summary>
		/// �f�o�b�O�e�L�X�g�{��
		/// </summary>
		void DrawDebugTextContent() override;

	private:

		// �����^�C�}�[
		YMath::Timer aliveTimer_;

	};
}