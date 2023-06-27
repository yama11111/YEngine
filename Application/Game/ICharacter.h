#pragma once
#include "GameObject.h"
#include "CharacterStatus.h"
#include "Speed.h"
#include "MapChipCollider.h"
#include "CollisionInfo.h"

namespace YGame
{
	class ICharacter :
		public GameObject,
		public MapChipCollider
	{

	public:

		/// <summary>
		/// ������
		/// </summary>
		/// <param name="status"> : �X�e�[�^�X</param>
		/// <param name="acceleration"> : �����x</param>
		/// <param name="maxSpeed"> : �ő呬�x</param>
		/// <param name="hp"> : HP</param>
		/// <param name="attack"> : �U����</param>
		/// <param name="invincibleTime"> : ���G����</param>
		/// <param name="collider"> : �R���C�_�[</param>
		/// <param name="drawer"> : �`��N���X</param>
		void Initialize(
			const Transform::Status& status,
			const YMath::Vector3& acceleration, const YMath::Vector3& maxSpeed,
			const uint32_t hp, const uint32_t attack, const uint32_t invincibleTime,
			BaseCollider* collider, BaseDrawer* drawer);

		/// <summary>
		/// �X�V
		/// </summary>
		virtual void Update() override;

		/// <summary>
		/// �Փ˔���
		/// </summary>
		/// <param name="info"> : �Փˎ����</param>
		virtual void OnCollision(const CollisionInfo& info) = 0;
	
	public:

		/// <summary>
		/// �����t���O
		/// </summary>
		/// <returns></returns>
		bool IsAlive() const;

		/// <summary>
		/// �L�����X�e�[�^�X�擾
		/// </summary>
		/// <returns>�L�����X�e�[�^�X</returns>
		CharacterStatus Status() const;

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

		ICharacter() = default;

		virtual ~ICharacter() = default;

	protected:

		// �ړ�����
		YMath::Vector3 moveDirection_;

		// �X�s�[�h
		YMath::Speed speed_;

		// �L�����N�^�[�X�e�[�^�X
		CharacterStatus status_;
	};
}
