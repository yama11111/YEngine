#pragma once
#include "IGameObject.h"
#include "CharacterStatus.h"
#include "MapChipCollider.h"
#include "Speed.h"

namespace YGame
{
	class IGameCharacter :
		public IGameObject,
		public MapChipCollider
	{

	public:

		/// <summary>
		/// �X�V
		/// </summary>
		virtual void Update() override;
	
	public:

		/// <summary>
		/// �����t���O
		/// </summary>
		/// <returns></returns>
		bool IsAlive() const;

		/// <summary>
		/// �ʒu�擾 (�Q��)
		/// </summary>
		/// <returns></returns>
		YMath::Vector3& PosRef() override;
		
		/// <summary>
		/// �X�s�[�h�擾 (�Q��)
		/// </summary>
		/// <returns></returns>
		YMath::Vector3& SpeedRef() override;

	public:

		IGameCharacter() = default;

		virtual ~IGameCharacter() = default;

	protected:
		
		/// <summary>
		/// ������
		/// </summary>
		/// <param name="type"> : ���</param>
		/// <param name="status"> : �X�e�[�^�X</param>
		/// <param name="radius"> : ���a</param>
		/// <param name="acceleration"></param>
		/// <param name="max"></param>
		/// <param name="maxJumpCount"></param>
		/// <param name="hp"></param>
		/// <param name="attack"></param>
		void Initialize(
			const Type type,
			const Transform::Status& status, 
			const float radius,
			const YMath::Vector3& acceleration, const YMath::Vector3& max,
			const uint16_t maxJumpCount,
			const uint32_t hp, const uint32_t attack);

		/// <summary>
		/// �W�����v
		/// </summary>
		void Jump();

	protected:

		// �ړ�����
		YMath::Vector3 moveDirection_;

		// �X�s�[�h
		YMath::Speed speed_;

		// �W�����v�J�E���^�[
		uint16_t jumpCounter_ = 0;

		// �ő�W�����v��
		uint16_t maxJumpCount_ = 0;

		// ���n�t���O
		bool isLanding_ = false;

		// �L�����N�^�[�X�e�[�^�X
		CharacterStatus status_;
	};
}
