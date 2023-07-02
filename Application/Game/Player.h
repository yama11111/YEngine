#pragma once
#include "ICharacter.h"
#include "IPet.h"

namespace YGame
{
	// �v���C���[
	class Player final :
		public ICharacter
	{

	public:

		/// <summary>
		/// ������
		/// </summary>
		/// <param name="status"> : �g�����X�t�H�[�����</param>
		/// <param name="pPet"> : �y�b�g�|�C���^</param>
		void Initialize(
			const Transform::Status& status, 
			IPet* pPet = nullptr);

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

		/// <summary>
		/// �y�b�g�ɏ��
		/// </summary>
		/// <param name="pPet"> : �y�b�g�|�C���^</param>
		void RideOnPet(IPet* pPet);
		
		/// <summary>
		/// �y�b�g����~���
		/// </summary>
		void GetOffPet();

	public:

		/// <summary>
		/// �ÓI������
		/// </summary>
		/// <param name="pScrollCamera"> : �X�N���[���J�����|�C���^</param>
		static void StaticInitialize(ScrollCamera* pScrollCamera);

	public:

		Player() = default;

		~Player() = default;

	private:

		// �W�����v�J�E���^�[
		uint16_t jumpCounter_ = 0;

		// �ő�W�����v��
		uint16_t maxJumpCount_ = 0;

		// �Z�𒅂Ă��邩
		bool isArmed_ = false;

		// �y�b�g�|�C���^
		IPet* pPet_ = nullptr;

	private:

		// �ÓI�X�N���[���J�����|�C���^
		static ScrollCamera* spScrollCamera_;

	private:
		
		/// <summary>
		/// �W�����v
		/// </summary>
		/// <param name="isJumpCount"> : �J�E���g���邩</param>
		void Jump(const bool isJumpCount = true);

		/// <summary>
		/// �U��
		/// </summary>
		void Attack();
		
		/// <summary>
		/// �f�o�b�O�e�L�X�g�{��
		/// </summary>
		void DrawDebugTextContent() override;

	};
}
