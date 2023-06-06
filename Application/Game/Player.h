#pragma once
#include "IGameCharacter.h"
#include "IPet.h"

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
		/// <param name="pos"> : �ʒu</param>
		/// <param name="pPet"> : �y�b�g�|�C���^</param>
		void Initialize(
			const YMath::Vector3& pos, 
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
		void SetPointer(IPet* pPet);

	public:

		Player() = default;

		~Player() = default;

	private:

		// �Z�𒅂Ă��邩
		bool isArmed_ = false;

		// �y�b�g�|�C���^
		IPet* pPet_ = nullptr;

	};
}
