#pragma once
#include "IGameObject.h"
#include "CharacterStatus.h"
#include "Speed.h"

namespace YGame
{
	class IGameCharacter :
		public IGameObject
	{

	public:

		IGameCharacter() = default;

		virtual ~IGameCharacter() = default;

	protected:

		/// <summary>
		/// �W�����v
		/// </summary>
		void Jump();

		/// <summary>
		/// �d��
		/// </summary>
		void UpdatePhysics();

	protected:

		// �X�s�[�h
		YMath::Speed speed_;

		// �W�����v�J�E���^�[
		unsigned int jumpCounter_ = 0;
		
		// �ő�W�����v��
		unsigned int maxJumpCount_ = 0;

		// ���n�t���O
		bool isLanding_ = false;

		// �L�����N�^�[�X�e�[�^�X
		CharacterStatus status_;
	};
}
