#pragma once
#include "GameObject.h"
#include "CharacterStatus.h"
#include "Speed.h"
#include "MapChipCollider.h"

namespace YGame
{
	class BaseCharacter :
		public GameObject,
		public MapChipCollider
	{
	
	public:

		/// <summary>
		/// ������
		/// </summary>
		/// <param name="name"> : ���O</param>
		/// <param name="status"> : �X�e�[�^�X</param>
		/// <param name="direction"> : ����</param>
		/// <param name="acceleration"> : �����x</param>
		/// <param name="maxSpeed"> : �ő呬�x</param>
		/// <param name="hp"> : HP</param>
		/// <param name="attack"> : �U����</param>
		/// <param name="invincibleTime"> : ���G����</param>
		/// <param name="collider"> : �R���C�_�[</param>
		/// <param name="drawer"> : �`��N���X</param>
		void Initialize(
			const std::string& name,
			const Transform::Status& status,
			const YMath::Vector3& direction,
			const YMath::Vector3& acceleration, const YMath::Vector3& maxSpeed,
			const uint32_t hp, const uint32_t attack, const uint32_t invincibleTime,
			GameCollider* collider, BaseDrawer* drawer);

		/// <summary>
		/// �X�V
		/// </summary>
		/// <param name="isUpdate"> : �X�V���邩</param>
		virtual void Update(const bool isUpdate);

	public:

		// �Փˎ����\����
		struct CollisionInfo
		{
			// ����
			AttributeType attribute_ = AttributeType::eNone;

			// �ʒu
			YMath::Vector3 pos_;

			// ���a
			float radius_ = 0.0f;

			// �L�����X�e�[�^�X�|�C���^
			CharacterStatus* pStatus_ = nullptr;

			// �|�C���^
			BaseCharacter* pSelf_ = nullptr;
		};
		
		/// <summary>
		/// �Փ˔���
		/// </summary>
		/// <param name="info"> : �Փˎ����</param>
		virtual void OnCollision(const CollisionInfo& info) = 0;

		/// <summary>
		/// �Փˎ����擾
		/// </summary>
		/// <returns>�Փˎ����</returns>
		virtual CollisionInfo GetCollisionInfo() = 0;
	
	public:

		/// <summary>
		/// �����t���O
		/// </summary>
		/// <returns></returns>
		inline bool IsAlive() const { return status_.IsAlive(); }

		/// <summary>
		/// �L�����X�e�[�^�X�擾
		/// </summary>
		/// <returns>�L�����X�e�[�^�X</returns>
		inline CharacterStatus Status() const { return status_; }

		/// <summary>
		/// �ʒu�擾 (�Q��)
		/// </summary>
		/// <returns></returns>
		inline YMath::Vector3& PosRef() override { return transform_->pos_; }
		
		/// <summary>
		/// �X�s�[�h�擾 (�Q��)
		/// </summary>
		/// <returns></returns>
		inline YMath::Vector3& SpeedRef() override { return speed_.VelocityRef(); }

	public:

		BaseCharacter() = default;

		virtual ~BaseCharacter() = default;

	protected:

		// ����
		YMath::Vector3 direction_;

		// �ړ�����
		YMath::Vector3 moveDirection_;

		// �X�s�[�h
		YMath::Speed speed_;

		// �L�����N�^�[�X�e�[�^�X
		CharacterStatus status_;

	protected:

		/// <summary>
		/// �f�o�b�O�e�L�X�g�{��
		/// </summary>
		virtual void DrawDebugTextContent() override;

		/// <summary>
		/// ��ʊO����
		/// </summary>
		virtual void OffScreenProcess();
	};
}
