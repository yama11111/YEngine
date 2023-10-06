#pragma once
#include "BaseDrawer.h"
#include "SlimeActor.h"
#include "HitActor.h"

namespace YGame
{
	class SlimeDrawer final :
		public BaseDrawer
	{

	public:

		// �A�j���[�V����
		enum class AnimationType : uint16_t
		{
			// ����
			eIdle	 = 0b1,

			// ���n
			eLanding = 0b1 << 2,

			// ��e
			eHit	 = 0b1 << 3,

			// ���S
			eDead	 = 0b1 << 4,
		};

	public:

		/// <summary>
		/// ����
		/// </summary>
		/// <param name="pParent"> : �e�|�C���^</param>
		/// <param name="drawPriority"> : �`��D��x</param>
		/// <returns>�v���C���[�`��N���X�|�C���^ (���I�C���X�^���X)</returns>
		static SlimeDrawer* Create(Transform* pParent, const size_t drawPriority);

		/// <summary>
		/// �ÓI������
		/// </summary>
		static void LoadResource();

	public:

		/// <summary>
		/// ������
		/// </summary>
		/// <param name="pParent"> : �e�|�C���^</param>
		/// <param name="drawPriority"> : �`��D��x</param>
		void Initialize(Transform* pParent, const size_t drawPriority) override;

		/// <summary>
		/// �`��
		/// </summary>
		void Draw() override;

	public:

		SlimeDrawer() = default;

		~SlimeDrawer() = default;

	private:

		// �X���C��
		SlimeActor slimeActor_;

		// ��e
		HitActor hitActor_;

		// ���f���|�C���^
		static Model* spModel_;

	private:

		/// <summary>
		/// �A�j���[�V�����^�C�}�[�}��
		/// </summary>
		void InsertAnimationTimers() override;

		/// <summary>
		/// �T�u�A�j���[�V�����Đ�
		/// </summary>
		/// <param name="index"> : �A�j���[�V�����ԍ�</param>
		/// <param name="frame"> : �Đ��t���[��</param>
		void PlaySubAnimation(const uint16_t index, const uint32_t frame) override;

		/// <summary>
		/// �A�j���[�V�����X�V
		/// </summary>
		void UpdateAnimation() override;
	};
}