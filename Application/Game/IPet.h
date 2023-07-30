#pragma once
#include "BaseCharacter.h"
#include "ScrollCamera.h"

namespace YGame
{
	class IPet :
		public BaseCharacter
	{

	public:

		/// <summary>
		/// �X�V
		/// </summary>
		virtual void Update() override;

		/// <summary>
		/// �Փ˔���
		/// </summary>
		/// <param name="info"> : �Փˎ����</param>
		virtual void OnCollision(const CollisionInfo& info) override;

		/// <summary>
		/// �U��
		/// </summary>
		virtual void Attack() = 0;

		/// <summary>
		/// �W�����v
		/// </summary>
		/// <param name="isJumpCount"> : �J�E���g���邩</param>
		virtual void Jump(const bool isJumpCount = true);

		/// <summary>
		/// ���ʒu�̍����擾
		/// </summary>
		/// <returns>���ʒu�̍���</returns>
		virtual float RidingPosHeight() = 0;

		/// <summary>
		/// �����
		/// </summary>
		virtual void Rideen();
		
		/// <summary>
		/// �~�����
		/// </summary>
		virtual void GotOff();
		
		/// <summary>
		/// �����������擾
		/// </summary>
		/// <returns>����������</returns>
		inline bool IsHit() { return isHit_; }

	public:

		IPet() = default;

		~IPet() = default;

	public:

		/// <summary>
		/// �ÓI������
		/// </summary>
		/// <param name="pScrollCamera"> : �X�N���[���J�����|�C���^</param>
		static void StaticInitialize(ScrollCamera* pScrollCamera);

	protected:

		// ��������
		bool isHit_ = false;

		// ����Ă���t���O
		bool isRidden_ = false;

		// �W�����v�J�E���^�[
		uint16_t jumpCounter_ = 0;

		// �ő�W�����v��
		uint16_t maxJumpCount_ = 0;

		// �ÓI�X�N���[���J�����|�C���^
		static ScrollCamera* spScrollCamera_;
	
	protected:

		/// <summary>
		/// �Փˎ�����
		/// </summary>
		virtual void Hit();

		/// <summary>
		/// ��ʊO����
		/// </summary>
		void OffScreenProcess() override;

	};
}
