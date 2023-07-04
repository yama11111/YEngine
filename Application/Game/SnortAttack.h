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
		/// <param name="aliveTimer"> : ��������</param>
		/// <param name="emitPos"> : �����ʒu</param>
		/// <param name="acceleration"> : �����x</param>
		/// <param name="maxspeed"> : �ō����x</param>
		/// <param name="radius"> : ���a</param>
		/// <param name="attackPower"> : �U����</param>
		void Initialize(
			const uint32_t aliveTimer,
			const YMath::Vector3& emitPos,
			const YMath::Vector3& acceleration,
			const YMath::Vector3& maxSpeed,
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