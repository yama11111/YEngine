#pragma once
#include "IGameCharacter.h"
#include "IPet.h"
#include "ScrollCamera.h"

namespace YGame
{
	// �v���C���[
	class Player final :
		public IGameCharacter
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
		/// �`��
		/// </summary>
		void Draw() override;

	public:

		/// <summary>
		/// �y�b�g�|�C���^�ݒ�
		/// </summary>
		/// <param name="pPet"> : �y�b�g�|�C���^</param>
		void SetPetPointer(IPet* pPet);

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

		// �Z�𒅂Ă��邩
		bool isArmed_ = false;

		// �y�b�g�|�C���^
		IPet* pPet_ = nullptr;

	private:

		// �ÓI�X�N���[���J�����|�C���^
		static ScrollCamera* spScrollCamera_;

	};
}
