#pragma once
#include "IGameObject.h"
#include "CharacterStatus.h"
#include "Speed.h"
#include "MapChipCollider.h"
#include "BaseCollider.h"

namespace YGame
{
	class IGameCharacter :
		public IGameObject,
		public BaseCollider,
		public MapChipCollider
	{

	public:

		/// <summary>
		/// ������
		/// </summary>
		/// <param name="type"> : ���</param>
		/// <param name="status"> : �X�e�[�^�X</param>
		/// <param name="radius"> : ���a</param>
		/// <param name="acceleration"> : �����x</param>
		/// <param name="maxSpeed"> : �ő呬�x</param>
		/// <param name="maxJumpCount"> : </param>
		/// <param name="hp"> : HP</param>
		/// <param name="attack"> : �U����</param>
		/// <param name="invincibleTime"> : ���G����</param>
		/// <param name="drawer"> : �`��N���X</param>
		/// <param name="location"> : �`��ʒu</param>
		void Initialize(
			const uint32_t attribute, const uint32_t mask,
			const Transform::Status& status, 
			const float radius,
			const YMath::Vector3& acceleration, const YMath::Vector3& maxSpeed,
			const uint32_t hp, const uint32_t attack, const uint32_t invincibleTime,
			IDrawer* drawer, const DrawLocation location);

		/// <summary>
		/// �X�V
		/// </summary>
		virtual void Update() override;

		/// <summary>
		/// �Փ˔���
		/// </summary>
		/// <param name="pPair"> : ����̃L�����N�^�[�|�C���^</param>
		virtual void OnCollision(IGameCharacter* pPair) = 0;
	
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

		IGameCharacter() = default;

		virtual ~IGameCharacter() = default;

	protected:

		// �ړ�����
		YMath::Vector3 moveDirection_;

		// �X�s�[�h
		YMath::Speed speed_;

		// �L�����N�^�[�X�e�[�^�X
		CharacterStatus status_;
	};
}
